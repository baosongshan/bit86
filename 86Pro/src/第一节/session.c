#include"session.h"
#include"ftpproto.h"
#include"privparent.h"

void begin_session(session_t *sess)
{
	pid_t pid = fork();
	if(pid == -1)
		ERR_EXIT("session fork");

	if(pid == 0)
	{
		//ftp �������
		handle_child(sess);
	}
	else
	{
		//nobody ����
		handle_parent(sess);
	}
}