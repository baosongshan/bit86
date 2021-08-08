#include"sysutil.h"
#include"session.h"
#include"tunable.h"
#include"parseconf.h"
#include"ftpproto.h"
#include"ftpcodes.h"
#include"hash.h"

void Test_Parseconf()
{
	parseconf_load_file("miniftp.conf");

	printf("tunable_pasv_enable = %d\n",  tunable_pasv_enable); 
	printf("tunable_port_enable = %d\n",  tunable_port_enable);
	printf("tunable_listen_port = %d\n",  tunable_listen_port);
	printf("tunable_max_clients = %d\n",  tunable_max_clients);
	printf("tunable_max_per_ip = %d\n",  tunable_max_per_ip);
	printf("tunable_accept_timeout = %d\n",  tunable_accept_timeout);
	printf("tunable_connect_timeout = %d\n",  tunable_connect_timeout);
	printf("tunable_idle_session_timeout = %d\n",  tunable_idle_session_timeout);
	printf("tunable_data_connection_timeout = %d\n",  tunable_data_connection_timeout);
	printf("tunable_local_umask = %d\n",  tunable_local_umask);
	printf("tunable_upload_max_rate = %d\n",  tunable_upload_max_rate);
	printf("tunable_download_mas_rate = %d\n",  tunable_download_max_rate);
	printf("tunable_listen_address = %s\n",  tunable_listen_address);
}

//ȫ�ֻỰ�ṹָ��
session_t *p_sess;

//�������������
static unsigned int s_children_nums = 0;
static struct hash *s_ip_count_hash;
static struct hash *s_pid_ip_hash;

static void check_limit(session_t *sess);
static void handle_sigchld(int sig);

unsigned int hash_func(unsigned int buket_size, void *key);
unsigned int handle_ip_count(void *ip);
void drop_ip_count(unsigned int *ip);

int main(int argc, char *argv[])
{
	//���������ļ�
	parseconf_load_file("miniftp.conf");

	//�����̨��
	//daemon(0, 0); //dev/null

	//�ж��Ƿ�Ϊroot�û�����
	if(getuid() != 0)
	{
		printf("miniftp : must be started as root.\n");
		exit(EXIT_FAILURE);
	}

	/*
		typedef struct session
		{
			//��������
			uid_t uid;
			int ctrl_fd;
			char cmdline[MAX_COMMOND_LINE_SIZE];
			char cmd[MAX_CMD_SIZE];
			char arg[MAX_ARG_SIZE];

			//��������
			struct sockaddr_in *port_addr;
			int    data_fd;
			int    pasv_listen_fd;
			int    data_process;

			//ftpЭ��״̬
			char *rnfr_name;
			int is_ascii;
			unsigned long long restart_pos;
			unsigned int  max_clients;
			unsigned int  max_per_ip;

			//���ӽ���ͨ��
			int parent_fd;
			int child_fd;

			//����
			unsigned long long transfer_start_sec;
			unsigned long long transfer_start_usec;

		}session_t;
	*/

	//�Ự�ṹ
	session_t sess = 
	{
		//��������
		-1, -1, "", "", "",
		
		//��������
		NULL, -1, -1, 0,

		//ftpЭ��״̬
		NULL, 1, 0, 0, 0,

		//���ӽ���ͨ��
		-1, -1,
		
		//����
		0, 0
	};

	p_sess = &sess;

	//��װ�ӽ����˳��ź�
	signal(SIGCHLD, handle_sigchld);

	//����hash��
	s_ip_count_hash = hash_alloc(MAX_BUCKET_SIZE, hash_func);
	s_pid_ip_hash = hash_alloc(MAX_BUCKET_SIZE, hash_func);

	//printf("ip = %s\n", tunable_listen_address);
	//printf("port = %d\n", tunable_listen_port);
	int listenfd = tcp_server(tunable_listen_address,  tunable_listen_port);

	int sockConn;
	struct sockaddr_in addrCli;
	socklen_t addrlen = sizeof(struct sockaddr);
	while(1)
	{
		sockConn = accept(listenfd, (struct sockaddr*)&addrCli, &addrlen);
		if(sockConn < 0)
		{
			perror("accept");
			continue;
		}

		//���������
		s_children_nums++;
		sess.max_clients = s_children_nums;
		
		//ÿIP������
		unsigned int ip = addrCli.sin_addr.s_addr;
		sess.max_per_ip = handle_ip_count(&ip);

		pid_t pid = fork();  //pthread_create ?
		if(pid == -1)
		{
			s_children_nums--;
			ERR_EXIT("fork");
		}

		if(pid == 0)
		{
			//Child Process
			close(listenfd);
			sess.ctrl_fd = sockConn;

			//��������
			check_limit(&sess);

			begin_session(&sess);
			exit(EXIT_SUCCESS);
		}
		else
		{
			//Parent Process
			//����pid��ip��ӳ��
			hash_add_entry(s_pid_ip_hash, &pid, sizeof(pid), &ip, sizeof(ip));

			close(sockConn);
		}
	}
	
	close(listenfd);
	return 0;
}

static void check_limit(session_t *sess)
{
	if(tunable_max_clients!=0 && sess->max_clients>tunable_max_clients)
	{
		//421 There are too many connected users, please try later.
		ftp_reply(sess, FTP_TOO_MANY_USERS, "There are too many connected users, please try later.");
		exit(EXIT_FAILURE);
	}

	if(tunable_max_per_ip!=0 && sess->max_per_ip>tunable_max_per_ip)
	{
		// 421 There are too many connections from your internet address.
		ftp_reply(sess, FTP_IP_LIMIT, "There are too many connections from your internet address.");
		exit(EXIT_FAILURE);
	}
}

static void handle_sigchld(int sig)
{
	//�������������
	s_children_nums--;

	//����ÿip��������
	pid_t pid;
	while((pid = waitpid(-1, NULL, WNOHANG)) > 0)
	{
		unsigned int *ip = (unsigned int *)hash_lookup_entry(s_pid_ip_hash, &pid, sizeof(pid));
		if(ip == NULL)
			continue;
		drop_ip_count(ip);
		hash_free_entry(s_pid_ip_hash, &pid, sizeof(pid));
	}
}

unsigned int hash_func(unsigned int buket_size, void *key)
{
	return (*(unsigned int*)key) % buket_size;
}

unsigned int handle_ip_count(void *ip)
{
	unsigned int *p_count = (unsigned int *)hash_lookup_entry(s_ip_count_hash, ip, sizeof(unsigned int));
	if(p_count == NULL)
	{
		unsigned int count = 1;
		hash_add_entry(s_ip_count_hash, ip, sizeof(unsigned int), &count, sizeof(unsigned int));
		return count;
	}

	(*p_count)++;
	return *p_count;
}

void drop_ip_count(unsigned int *ip)
{
	unsigned int *p_count = (unsigned int*)hash_lookup_entry(s_ip_count_hash, ip, sizeof(unsigned int));
	if(p_count == NULL)
		return;
	(*p_count)--;
	if(*p_count == 0)
		hash_free_entry(s_ip_count_hash, ip, sizeof(unsigned int));
}