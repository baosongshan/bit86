#include"tunable.h"

int tunable_pasv_enable = 1; //�Ƿ�������ģʽ
int tunable_port_enable = 1; //�Ƿ�������ģʽ
unsigned int tunable_listen_port = 21; //FTP�������˿�
unsigned int tunable_max_clients = 2000; //���������
unsigned int tunable_max_per_ip = 50; //ÿip���������
unsigned int tunable_accept_timeout = 60; //Accept��ʱ��
unsigned int tunable_connect_timeout = 60; //Connect��ʱ��
unsigned int tunable_idle_session_timeout=300; //�������ӳ�ʱʱ��
unsigned int tunable_data_connection_timeout=300; //�������ӳ�ʱʱ��
unsigned int tunable_local_umask = 077; //����
unsigned int tunable_upload_max_rate = 0; //����ϴ��ٶ�
unsigned int tunable_download_mas_rate=0; // ��������ٶ�
const char *tunable_listen_address;