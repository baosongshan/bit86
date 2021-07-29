#ifndef _SESSION_H_
#define _SESSION_H_

#include"common.h"

//�Ự�ṹ
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
	char *rnfr_name;
	int is_ascii;

	//���ӽ���ͨ��
	int parent_fd;
	int child_fd;
}session_t;

void begin_session(session_t *sess);

#endif /* _SESSION_H_ */