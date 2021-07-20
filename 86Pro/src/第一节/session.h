#ifndef _SESSION_H_
#define _SESSION_H_

#include"common.h"

//会话结构
typedef struct session
{
	//控制连接
	int ctrl_fd;

}session_t;

void begin_session(session_t *sess);

#endif /* _SESSION_H_ */