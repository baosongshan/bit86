#include"session.h"
#include"ftpproto.h"
#include"privparent.h"
#include"privsock.h"

void begin_session(session_t *sess)
{
	priv_sock_init(sess);

	pid_t pid = fork();
	if(pid == -1)
		ERR_EXIT("session fork");

	if(pid == 0)
	{
		//ftp 服务进程
		priv_sock_set_child_context(sess);
		handle_child(sess);
	}
	else
	{
		//nobody 进程
		priv_sock_set_parent_context(sess);
		handle_parent(sess);
	}
}