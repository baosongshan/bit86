#ifndef _SESSION_H_
#define _SESSION_H_

#include"common.h"

//会话结构
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

	//ftp协议状态
	int is_ascii;

	//父子进程通道
	int parent_fd;
	int child_fd;
}session_t;

void begin_session(session_t *sess);

#endif /* _SESSION_H_ */