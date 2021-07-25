#include"sysutil.h"
#include"session.h"

int main(int argc, char *argv[])
{
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

			//ftpЭ��״̬
			int is_ascii;

			//���ӽ���ͨ��
			int parent_fd;
			int child_fd;
		}session_t;
	*/

	//�Ự�ṹ
	session_t sess = 
	{
		//��������
		-1, -1, "", "", "",
		
		//��������
		NULL, -1, -1,

		//ftpЭ��״̬
		1,
		//���ӽ���ͨ��
		-1, -1
	};

	int listenfd = tcp_server("192.168.232.10",  9100);

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