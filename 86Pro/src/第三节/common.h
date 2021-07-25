#ifndef _COMMON_H_
#define _COMMON_H_

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<pwd.h>
#include<shadow.h>
#include<crypt.h>

#include<dirent.h>
#include<sys/stat.h>

#include<time.h>

#define ERR_EXIT(msg)\
		do{\
			perror(msg);\
			exit(EXIT_FAILURE);\
		}while(0)

#define MAX_COMMOND_LINE_SIZE 1024
#define MAX_CMD_SIZE          128
#define MAX_ARG_SIZE          1024

#define MAX_BUFFER_SIZE       1024
#define MAX_CWD_SIZE          512

#endif /* _COMMON_H_ */