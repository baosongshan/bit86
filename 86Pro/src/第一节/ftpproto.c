#include"ftpproto.h"

//ftp �������
void handle_child(session_t *sess)
{
	send(sess->ctrl_fd, "220 (miniftp 1.0.1)\r\n", strlen("220 (miniftp 1.0.1)\r\n"), 0);
	while(1)
	{
		//��ͣ�ĵȴ��ͻ��˵������������
	}

}