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
		//ftp 服务进程
		handle_child(sess);
	}
	else
	{
		//nobody 进程

		//更改nobody进程
		struct passwd *pwd = getpwnam("nobody"); //lyx
		if(pwd == NULL)
			ERR_EXIT("getpwnam");
		if(setegid(pwd->pw_gid) < 0)
			ERR_EXIT("setegid");
		if(seteuid(pwd->pw_uid) < 0)
			ERR_EXIT("seteuid");

		handle_parent(sess);
	}
}