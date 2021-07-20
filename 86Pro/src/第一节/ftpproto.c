#include"ftpproto.h"

//ftp 服务进程
void handle_child(session_t *sess)
{
	send(sess->ctrl_fd, "220 (miniftp 1.0.1)\r\n", strlen("220 (miniftp 1.0.1)\r\n"), 0);
	while(1)
	{
		//不停的等待客户端的命令并做出处理
	}

}