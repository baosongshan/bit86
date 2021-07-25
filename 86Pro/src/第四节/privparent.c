#include"privparent.h"
#include"session.h"
#include"sysutil.h"
#include"privsock.h"

//��ȡ���������׽���
static void privop_pasv_get_data_sock(session_t *sess);
//�ж�����ģʽ�Ƿ񱻼���
static void privop_pasv_active(session_t *sess);
//��������ģʽ�ļ����׽���
static void privop_pasv_listen(session_t *sess);
//����ģʽ�½�������
static void privop_pasv_accept(session_t *sess);

//nobody �������
void handle_parent(session_t *sess)
{
	//����nobody����
	struct passwd *pwd = getpwnam("nobody"); //lyx
	if(pwd == NULL)
		ERR_EXIT("getpwnam");
	if(setegid(pwd->pw_gid) < 0)
		ERR_EXIT("setegid");
	if(seteuid(pwd->pw_uid) < 0)
		ERR_EXIT("seteuid");

	char cmd;
	while(1)
	{
		//��ͣ�ĵȴ�ftp������̵���Ϣ
		cmd = priv_sock_get_cmd(sess->parent_fd);
		switch(cmd)
		{
		case PRIV_SOCK_GET_DATA_SOCK:
			privop_pasv_get_data_sock(sess);
			break;
		case PRIV_SOCK_PASV_ACTIVE:
			privop_pasv_active(sess);
			break;
		case PRIV_SOCK_PASV_LISTEN:
			privop_pasv_listen(sess);
			break;
		case PRIV_SOCK_PASV_ACCEPT:
			privop_pasv_accept(sess);
			break;
		}
	}
}

static void privop_pasv_get_data_sock(session_t *sess)
{
	//ip
	char ip[16] = {0};
	int len = priv_sock_get_int(sess->parent_fd);
	priv_sock_recv_buf(sess->parent_fd, ip, len);

	//port
	unsigned short port = (unsigned short)priv_sock_get_int(sess->parent_fd);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	int sock = tcp_client();
	socklen_t addrlen = sizeof(struct sockaddr);
	if(connect(sock, (struct sockaddr*)&addr, addrlen) < 0)
	{
		priv_sock_send_result(sess->parent_fd, PRIV_SOCK_RESULT_BAD);
		return;
	}

	priv_sock_send_result(sess->parent_fd, PRIV_SOCK_RESULT_OK);
	priv_sock_send_fd(sess->parent_fd, sock);

	close(sock);
}


static void privop_pasv_active(session_t *sess)
{
	int active = -1; //δ����
	if(sess->pasv_listen_fd != -1)
		active = 1; //����
	priv_sock_send_int(sess->parent_fd, active);
}

static void privop_pasv_listen(session_t *sess)
{
	char ip[16] = "192.168.232.10";
	unsigned int v[4] = {0};
	sscanf(ip, "%u.%u.%u.%u", &v[0], &v[1], &v[2], &v[3]);

	//0��������Ĭ�϶˿ں�
	int sockfd = tcp_server(ip, 0);

	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(struct sockaddr);
	if(getsockname(sockfd,	(struct sockaddr*)&addr, &addrlen) < 0)
		ERR_EXIT("getsockname");

	unsigned short port = ntohs(addr.sin_port);

	sess->pasv_listen_fd = sockfd;

	//����ip
	priv_sock_send_int(sess->parent_fd, strlen(ip));
	priv_sock_send_buf(sess->parent_fd, ip, strlen(ip));
	//����port
	priv_sock_send_int(sess->parent_fd, (int)port);
}

static void privop_pasv_accept(session_t *sess)
{
	int sockConn;
	struct sockaddr_in addr;
	socklen_t addrlen;
	if((sockConn = accept(sess->pasv_listen_fd, (struct sockaddr*)&addr, &addrlen)) < 0)
	{
		priv_sock_send_result(sess->parent_fd, PRIV_SOCK_RESULT_BAD);
		return;
	}
	priv_sock_send_result(sess->parent_fd, PRIV_SOCK_RESULT_OK);

	priv_sock_send_fd(sess->parent_fd, sockConn);
	
	close(sess->pasv_listen_fd);
	sess->pasv_listen_fd = -1;
	close(sockConn);
}