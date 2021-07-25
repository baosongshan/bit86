#include"sysutil.h"

int tcp_server(const char *host, unsigned short port)
{
	int listenfd;
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in addrSer;
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(port);
	addrSer.sin_addr.s_addr = inet_addr(host);

	//设置地址重用
	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ERR_EXIT("setsockopt");

	if(bind(listenfd, (struct sockaddr*)&addrSer, sizeof(addrSer)) < 0)
		ERR_EXIT("bind");

	if(listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");

	return listenfd;
}

int tcp_client()
{
	int sock;
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERR_EXIT("socket");
	return sock;
}

char* statbuf_get_perms(struct stat *sbuf)
{
	static char perms[] = "----------";
	mode_t mode = sbuf->st_mode;

	switch(mode & S_IFMT)
	{
	case S_IFREG:
		perms[0] = '-';
		break;
	case S_IFDIR:
		perms[0] = 'd';
		break;
	case S_IFCHR:
		perms[0] = 'c';
		break;
	case S_IFIFO:
		perms[0] = 'p';
		break;
	case S_IFBLK:
		perms[0] = 'b';
		break;
	case S_IFLNK:
		perms[0] = 'l';
		break;
	}

    if(mode & S_IRUSR)
		perms[1] = 'r';
	if(mode & S_IWUSR)
		perms[2] = 'w';
	if(mode & S_IXUSR)
		perms[3] = 'x';

	if(mode & S_IRGRP)
		perms[4] = 'r';
	if(mode & S_IWGRP)
		perms[5] = 'w';
	if(mode & S_IXGRP)
		perms[6] = 'x';

	if(mode & S_IROTH)
		perms[7] = 'r';
	if(mode & S_IWOTH)
		perms[8] = 'w';
	if(mode & S_IXOTH)
		perms[9] = 'x';
    
	return perms;
}

char* statbuf_get_date(struct stat *sbuf)
{
	static char date[64] = {0};
	struct tm *ptm = localtime(&sbuf->st_mtime);
	strftime(date, 64, "%b %e %H:%M", ptm);
	return date;
}