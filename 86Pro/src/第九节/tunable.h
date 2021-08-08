#ifndef _TUNABLE_H_
#define _TUNABLE_H_


extern int tunable_pasv_enable; //是否开启被动模式
extern int tunable_port_enable;//是否开启主动模式
extern unsigned int tunable_listen_port;//FTP服务器端口
extern unsigned int tunable_max_clients; //最大连接数
extern unsigned int tunable_max_per_ip; //每ip最大连接数
extern unsigned int tunable_accept_timeout; //Accept超时间
extern unsigned int tunable_connect_timeout; //Connect超时间
extern unsigned int tunable_idle_session_timeout; //控制连接超时时间
extern unsigned int tunable_data_connection_timeout; //数据连接超时时间
extern unsigned int tunable_local_umask; //掩码
extern unsigned int tunable_upload_max_rate; //最大上传速度
extern unsigned int tunable_download_max_rate; // 最大下载速度
extern const char *tunable_listen_address;

#endif /* _TUNABLE_H_ */