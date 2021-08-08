#ifndef _FTPPROTO_H_
#define _FTPPROTO_H_

#include"common.h"
#include"session.h"

void handle_child(session_t *sess);
void ftp_reply(session_t *sess, unsigned int code, const char *text);

#endif /* _FTPPROTO_H_ */