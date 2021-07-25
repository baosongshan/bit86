#ifndef _SYSUTIL_H_
#define _SYSUTIL_H_

#include"common.h"

int tcp_server(const char *host, unsigned short port);
int tcp_client();

char* statbuf_get_perms(struct stat *sbuf);
char* statbuf_get_date(struct stat *sbuf);
#endif /* _SYSUTIL_H_ */