#include"sysutil.h"
#include"session.h"
#include"tunable.h"
#include"parseconf.h"

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

//全局会话结构指针
session_t *p_sess;

int main(int argc, char *argv[])
{
	//加载配置文件
	parseconf_load_file("miniftp.conf");


	//判断是否为root用户启动
	if(getuid() != 0)
	{
		printf("miniftp : must be started as root.\n");
		exit(EXIT_FAILURE);
	}

	/*
		typedef struct session
		{
			//控制连接
			uid_t uid;
			int ctrl_fd;
			char cmdline[MAX_COMMOND_LINE_SIZE];
			char cmd[MAX_CMD_SIZE];
			char arg[MAX_ARG_SIZE];

			//数据连接
			struct sockaddr_in *port_addr;
			int    data_fd;
			int    pasv_listen_fd;
			int    data_process;

			//ftp协议状态
			char *rnfr_name;
			int is_ascii;
			unsigned long long restart_pos;

			//父子进程通道
			int parent_fd;
			int child_fd;

			//限速
			unsigned long long transfer_start_sec;
			unsigned long long transfer_start_usec;

		}session_t;
	*/

	//会话结构
	session_t sess = 
	{
		//控制连接
		-1, -1, "", "", "",
		
		//数据连接
		NULL, -1, -1, 0,

		//ftp协议状态
		NULL, 1, 0, 

		//父子进程通道
		-1, -1,
		
		//限速
		0, 0
	};

	p_sess = &sess;

	printf("ip = %s\n", tunable_listen_address);
	printf("port = %d\n", tunable_listen_port);
	int listenfd = tcp_server(tunable_listen_address,  tunable_listen_port);

	int sockConn;
	struct sockaddr_in addrCli;
	socklen_t addrlen;
	while(1)
	{
		sockConn = accept(listenfd, (struct sockaddr*)&addrCli, &addrlen);
		if(sockConn < 0)
		{
			perror("accept");
			continue;
		}

		pid_t pid = fork();
		if(pid == -1)
			ERR_EXIT("fork");

		if(pid == 0)
		{
			//Child Process
			close(listenfd);
			sess.ctrl_fd = sockConn;
			begin_session(&sess);
			exit(EXIT_SUCCESS);
		}
		else
		{
			//Parent Process
			close(sockConn);
		}
	}
	
	close(listenfd);
	return 0;
}