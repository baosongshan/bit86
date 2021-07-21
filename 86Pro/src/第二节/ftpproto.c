#include"ftpproto.h"
#include"session.h"
#include"str.h"
#include"ftpcodes.h"

static void ftp_reply(session_t *sess, unsigned int code, const char *text)
{
	char buffer[MAX_BUFFER_SIZE] = {0};
	sprintf(buffer, "%d %s\r\n", code, text);
	send(sess->ctrl_fd, buffer, strlen(buffer), 0);
}

static void do_user(session_t *sess);
static void do_pass(session_t *sess);
static void do_syst(session_t *sess);
static void do_feat(session_t *sess);
static void do_pwd(session_t *sess);
static void do_type(session_t *sess);
static void do_port(session_t *sess);
static void do_list(session_t *sess);

//命令映射
typedef struct ftpcmd
{
	const char *cmd; // 命令
	void(*cmd_handler)(session_t *sess); //命令处理方法
}ftpcmd_t;

ftpcmd_t ctrl_cmds[] = 
{
	{"USER", do_user},
	{"PASS", do_pass},
	{"SYST", do_syst},
	{"FEAT", do_feat},
	{"PWD" , do_pwd },
	{"TYPE", do_type},
	{"PORT", do_port},
	{"LIST", do_list}
};

//ftp 服务进程
void handle_child(session_t *sess)
{
	//send(sess->ctrl_fd, "220 (miniftp 1.0.1)\r\n", strlen("220 (miniftp 1.0.1)\r\n"), 0);
	ftp_reply(sess, FTP_GREET, "(bit86 miniftp 1.0.1)");
	while(1)
	{
		//不停的等待客户端的命令并做出处理
		memset(sess->cmdline, 0, MAX_COMMOND_LINE_SIZE);
		memset(sess->cmd, 0, MAX_CMD_SIZE);
		memset(sess->arg, 0, MAX_ARG_SIZE);

		int ret = recv(sess->ctrl_fd, sess->cmdline, MAX_COMMOND_LINE_SIZE, 0);
		if(ret < 0)
			ERR_EXIT("recv");
		if(ret == 0)
			exit(EXIT_SUCCESS);
		
		str_trim_crlf(sess->cmdline);
		str_split(sess->cmdline, sess->cmd, sess->arg, ' ');

		//printf("cmdline = %s\n", sess->cmdline);
		//printf("cmd = %s\n", sess->cmd);
		//printf("arg = %s\n", sess->arg);

		//命令映射
		int table_size = sizeof(ctrl_cmds) / sizeof(ctrl_cmds[0]);
		int i;
		for(i=0; i<table_size; ++i)
		{
			if(strcmp(sess->cmd, ctrl_cmds[i].cmd) == 0)
			{
				if(ctrl_cmds[i].cmd_handler)
					ctrl_cmds[i].cmd_handler(sess);
				else
					ftp_reply(sess, FTP_COMMANDNOTIMPL, "Unimplement command.");
				break;
			}
		}
		if(i >= table_size)
			ftp_reply(sess, FTP_BADCMD, "Unknown command.");
	}

}

static void do_user(session_t *sess)
{
	struct passwd *pwd = getpwnam(sess->arg);
	if(pwd != NULL)
		sess->uid = pwd->pw_uid; //保存用户ID即uid
	ftp_reply(sess, FTP_GIVEPWORD, "Please specify the password");
}

static void do_pass(session_t *sess)
{
	//鉴权登录
	struct passwd *pwd = getpwuid(sess->uid);
	if(pwd == NULL)
	{
		//用户不存在
		ftp_reply(sess, FTP_LOGINERR, "Login incorrect.");
		return;
	}
	struct spwd *spd = getspnam(pwd->pw_name);
	if(spd == NULL)
	{
		//用户不存在
		ftp_reply(sess, FTP_LOGINERR, "Login incorrect.");
		return;
	}

	char *encrypted_pw = crypt(sess->arg, spd->sp_pwdp);
	if(strcmp(encrypted_pw, spd->sp_pwdp) != 0)
	{
		//密码错误
		ftp_reply(sess, FTP_LOGINERR, "Login incorrect.");
		return;
	}

	//更改ftp服务进程
	setegid(pwd->pw_gid);
	seteuid(pwd->pw_uid);
	chdir(pwd->pw_dir);

	ftp_reply(sess, FTP_LOGINOK, "Login successful.");
}

static void do_syst(session_t *sess)
{
	ftp_reply(sess, FTP_SYSTOK, "Linux Type: L8");
}

static void do_feat(session_t *sess)
{
	send(sess->ctrl_fd, "211-Features:\r\n", strlen("211-Features:\r\n"), 0);
	send(sess->ctrl_fd, " EPRT\r\n", strlen(" EPRT\r\n"), 0);
	send(sess->ctrl_fd, " EPSV\r\n", strlen(" EPSV\r\n"), 0);
	send(sess->ctrl_fd, " MDTM\r\n", strlen(" MDTM\r\n"), 0);
	send(sess->ctrl_fd, " PASV\r\n", strlen(" PASV\r\n"), 0);
	send(sess->ctrl_fd, " REST STREAM\r\n", strlen(" REST STREAM\r\n"), 0);
	send(sess->ctrl_fd, " SIZE\r\n", strlen(" SIZE\r\n"), 0);
	send(sess->ctrl_fd, " TVFS\r\n", strlen(" TVFS\r\n"), 0);
	send(sess->ctrl_fd, " UTF8\r\n", strlen(" UTF8\r\n"), 0);
	send(sess->ctrl_fd, "211 End\r\n", strlen("211 End\r\n"), 0);
}

static void do_pwd(session_t *sess)
{
	char cwd[MAX_CWD_SIZE] = {0};
	getcwd(cwd, MAX_CWD_SIZE);
	char text[MAX_BUFFER_SIZE] = {0};
	sprintf(text, "\"%s\"", cwd);
	ftp_reply(sess, FTP_MKDIROK, text);
}

static void do_type(session_t *sess)
{
	if(strcmp(sess->arg,"A")==0 || strcmp(sess->arg,"a")==0)
	{
		sess->is_ascii = 1;
		ftp_reply(sess, FTP_TYPEOK, "Switching to ASCII mode.");
	}
	else if(strcmp(sess->arg,"I")==0 || strcmp(sess->arg,"i")==0)
	{
		sess->is_ascii = 0;
		ftp_reply(sess, FTP_TYPEOK, "Switching to Binary mode.");
	}
	else
	{
		//500 Unrecognised TYPE command.
		ftp_reply(sess, FTP_BADCMD, "Unrecognised TYPE command.");
	}
}

static void do_port(session_t *sess)
{
	//
}

static void do_list(session_t *sess)
{
	//1 创建数据连接

	//2 150

	//3 传输列表

	//4 226
}