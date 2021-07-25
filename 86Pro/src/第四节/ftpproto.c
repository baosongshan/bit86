#include"ftpproto.h"
#include"session.h"
#include"str.h"
#include"ftpcodes.h"
#include"sysutil.h"
#include"privsock.h"

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
static void do_pasv(session_t *sess);
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
	{"PASV", do_pasv},
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

/////////////////////////////////////////////////////////////////////
//数据协商

static void do_port(session_t *sess)
{
	//PORT 192,168,232,1,34,173
	unsigned int v[6] = {0};
	sscanf(sess->arg, "%u,%u,%u,%u,%u,%u", &v[0],&v[1],&v[2],&v[3],&v[4],&v[5]);

	sess->port_addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr));

	//填充协议家族
	sess->port_addr->sin_family = AF_INET;

	//填充port
	unsigned char *p = (unsigned char *)&(sess->port_addr->sin_port);
	p[0] = v[4];
	p[1] = v[5];

	//填充ip
	p = (unsigned char *)&(sess->port_addr->sin_addr);
	p[0] = v[0];
	p[1] = v[1];
	p[2] = v[2];
	p[3] = v[3];

	// 200 PORT command successful. Consider using PASV.
	ftp_reply(sess, FTP_PROTOK, "PORT command successful. Consider using PASV.");
}

static void do_pasv(session_t *sess)
{
	priv_sock_send_cmd(sess->child_fd, PRIV_SOCK_PASV_LISTEN);
	char ip[16] = {0};

	//接收ip
	int len = priv_sock_get_int(sess->child_fd);
	priv_sock_recv_buf(sess->child_fd, ip, len);
	//接收port
	unsigned short port = (unsigned short)priv_sock_get_int(sess->child_fd);

	//////////////////////////////////////////////////////////

	unsigned v[4] = {0};
	sscanf(ip, "%u.%u.%u.%u", &v[0], &v[1], &v[2], &v[3]);
	char text[MAX_BUFFER_SIZE] = {0};
	sprintf(text, "Entering Passive Mode (%u,%u,%u,%u,%u,%u).",
		v[0],v[1],v[2],v[3], port>>8, port&0x00ff);

	//227 Entering Passive Mode (192,168,232,10,248,159).
	ftp_reply(sess, FTP_PASVOK, text);
}

////////////////////////////////////////////////////////////////////////
//数据连接
int pasv_active(session_t *sess);
int port_active(session_t *sess)
{
	if(sess->port_addr != NULL)
	{
		if(pasv_active(sess))
			ERR_EXIT("both port an pasv are active");
		return 1;
	}
	return 0;
}

int pasv_active(session_t *sess)
{
	priv_sock_send_cmd(sess->child_fd, PRIV_SOCK_PASV_ACTIVE);
	int active = priv_sock_get_int(sess->child_fd);
	if(active != -1)
	{
		if(port_active(sess))
			ERR_EXIT("both port an pasv are active");
		return 1;
	}
	return 0;
}

int get_port_fd(session_t *sess)
{
	priv_sock_send_cmd(sess->child_fd, PRIV_SOCK_GET_DATA_SOCK);
	
	//发送ip
	char *ip = inet_ntoa(sess->port_addr->sin_addr);
	priv_sock_send_int(sess->child_fd, strlen(ip));
	priv_sock_send_buf(sess->child_fd, ip, strlen(ip));

	//发送port
	unsigned short port = ntohs(sess->port_addr->sin_port);
	priv_sock_send_int(sess->child_fd, (int)port);

	char res = priv_sock_get_result(sess->child_fd);
	if(res == PRIV_SOCK_RESULT_BAD)
		return -1;

	sess->data_fd = priv_sock_recv_fd(sess->child_fd);
	return 0;
}

int get_pasv_fd(session_t *sess)
{
	priv_sock_send_cmd(sess->child_fd, PRIV_SOCK_PASV_ACCEPT);
	char res = priv_sock_get_result(sess->child_fd);
	if(res == PRIV_SOCK_RESULT_BAD)
		return -1;

	sess->data_fd = priv_sock_recv_fd(sess->child_fd);
	return 0;
}

static int get_transfer_fd(session_t *sess)
{
	if(!port_active(sess) && !pasv_active(sess))
	{
		//425 Use PORT or PASV first.
		ftp_reply(sess, FTP_BADSENDCONN, "Use PORT or PASV first.");
		return -1;
	}

	if(port_active(sess))
	{
		if(get_port_fd(sess) != 0)
			return -1;
	}
	if(pasv_active(sess))
	{
		if(get_pasv_fd(sess) != 0)
			return -1;
	}

	if(sess->port_addr)
	{
		free(sess->port_addr);
		sess->port_addr = NULL;
	}
	return 0;
}

//drwxrwxr-x    2 1000     1000          114 Dec 05  2020 93
void list_common(session_t *sess)
{
	DIR *dir = opendir(".");
	if(dir == NULL)
		ERR_EXIT("opendir");

	struct stat sbuf;
	char   buf[MAX_BUFFER_SIZE] = {0};
	unsigned int offset = 0;

	struct dirent *dt;
	while((dt = readdir(dir)))
	{
		if(stat(dt->d_name,  &sbuf)<0)
			ERR_EXIT("stat");

		if(dt->d_name[0] == '.')
			continue;
		
		const char *perms = statbuf_get_perms(&sbuf);
		offset = sprintf(buf, "%s", perms);

		offset += sprintf(buf+offset, "%3d %-8d %-8d %8u ", 
			(int)sbuf.st_nlink, sbuf.st_uid, sbuf.st_gid, (unsigned int)sbuf.st_size);

		const char *pdate = statbuf_get_date(&sbuf);
		offset += sprintf(buf+offset, "%s ", pdate);

		sprintf(buf+offset, "%s\r\n", dt->d_name);
		//buf drwxrwxr-x    2 1000     1000          114 Dec 05  2020 93

		send(sess->data_fd, buf, strlen(buf), 0);
	}

	closedir(dir);
}

static void do_list(session_t *sess)
{
	//1 创建数据连接
	if(get_transfer_fd(sess) != 0)
		return;

	//2 150
	ftp_reply(sess, FTP_DATACONN, "Here comes the directory listing.");

	//3 传输列表
	list_common(sess);

	//4 226
	ftp_reply(sess, FTP_TRANSFEROK, "Directory send OK.");

	//关闭数据连接
	close(sess->data_fd);
	sess->data_fd = -1;
}