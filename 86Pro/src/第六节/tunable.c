#include"tunable.h"

int tunable_pasv_enable = 1; //是否开启被动模式
int tunable_port_enable = 1; //是否开启主动模式
unsigned int tunable_listen_port = 21; //FTP服务器端口
unsigned int tunable_max_clients = 2000; //最大连接数
unsigned int tunable_max_per_ip = 50; //每ip最大连接数
unsigned int tunable_accept_timeout = 60; //Accept超时间
unsigned int tunable_connect_timeout = 60; //Connect超时间
unsigned int tunable_idle_session_timeout=300; //控制连接超时时间
unsigned int tunable_data_connection_timeout=300; //数据连接超时时间
unsigned int tunable_local_umask = 077; //掩码
unsigned int tunable_upload_max_rate = 0; //最大上传速度
unsigned int tunable_download_mas_rate=0; // 最大下载速度
const char *tunable_listen_address;