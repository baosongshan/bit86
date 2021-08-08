#ifndef _SYSUTIL_H_
#define _SYSUTIL_H_

#include"common.h"

void getlocalip(char *ip);
int tcp_server(const char *host, unsigned short port);
int tcp_client(int port);

char* statbuf_get_perms(struct stat *sbuf);
char* statbuf_get_date(struct stat *sbuf);

void send_fd(int sock_fd, int fd);
int  recv_fd(const int sock_fd);

unsigned long long get_time_sec();
unsigned long long get_time_usec();
void nano_sleep(double sleep_time);
#endif /* _SYSUTIL_H_ */