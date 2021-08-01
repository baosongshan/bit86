#include"parseconf.h"
#include"tunable.h"
#include"str.h"


//bool型配置项
static struct parseconf_bool_setting
{
	const char *p_setting_name; //配置项的名字
	int        *p_variable;     //配置项的值
}
parseconf_bool_array[] = 
{
	{"pasv_enable", &tunable_pasv_enable},
	{"port_enable", &tunable_port_enable},
	{NULL, NULL}
};

//int配置项
static struct parseconf_uint_setting
{
	const char   *p_setting_name;
	unsigned int *p_variable;
}
parseconf_uint_array[] = 
{
	{"listen_port", &tunable_listen_port},
	{"max_clients", &tunable_max_clients},
	{"max_per_ip" , &tunable_max_per_ip},
	{"accept_timeout", &tunable_accept_timeout},
	{"connect_timeout", &tunable_connect_timeout},
	{"idle_session_timeout", &tunable_idle_session_timeout},
	{"data_connection_timeout", &tunable_data_connection_timeout},
	{"local_umask", &tunable_local_umask},
	{"upload_max_rate", &tunable_upload_max_rate},
	{"download_mas_rate", &tunable_download_mas_rate},
	{NULL, NULL}
};


//str配置项
static struct parseconf_str_setting
{
	const char *p_setting_name;
	const char **p_variable;
}
parseconf_str_array[] = 
{
	{"listen_address", &tunable_listen_address},
	{NULL, NULL}
};


void parseconf_load_file(const char *path)
{
	FILE *fp = fopen(path, "r");
	if(NULL == fp)
		ERR_EXIT("parseconf_load_file");

	char setting_line[MAX_SETTING_LINE_SIZE] = {0};
	while(fgets(setting_line, MAX_SETTING_LINE_SIZE, fp) != NULL)
	{
		if(setting_line[0]=='\0' || setting_line[0]=='#')
			continue;
		str_trim_crlf(setting_line);

		//解析配置行
		parseconf_load_setting(setting_line);

		memset(setting_line, 0, MAX_SETTING_LINE_SIZE);
	}

	fclose(fp);
}

//listen_port=9100
void parseconf_load_setting(const char *setting)
{
	char key[MAX_KEY_SIZE] = {0};
	char value[MAX_VALUE_SIZE] = {0};
	str_split(setting, key, value, '=');

	//查询str配置项
	const struct parseconf_str_setting *p_str_setting = parseconf_str_array;
	while(p_str_setting->p_setting_name != NULL)
	{
		if(strcmp(key, p_str_setting->p_setting_name) == 0)
		{
			const char **p_cur_setting = p_str_setting->p_variable;
			if(*p_cur_setting)
				free((char *)*p_cur_setting);
			*p_cur_setting = strdup(value);//malloc
			return;
		}
		p_str_setting++;
	}

	//查询bool配置项
	const struct parseconf_bool_setting *p_bool_setting = parseconf_bool_array;
	while(p_bool_setting->p_setting_name != NULL)
	{
		if(strcmp(key, p_bool_setting->p_setting_name) == 0)
		{
			str_upper(value);
			int *p_cur_setting = p_bool_setting->p_variable;
			if(strcmp(value, "YES") == 0)
				*p_cur_setting = 1;
			else if(strcmp(value, "NO") == 0)
				*p_cur_setting = 0;
			else
				ERR_EXIT("parseconf_load_setting");
			return;
		}
		p_bool_setting++;
	}

	//查询int配置项
	const struct parseconf_uint_setting *p_uint_setting = parseconf_uint_array;
	while(p_uint_setting->p_setting_name != NULL)
	{
		if(strcmp(key, p_uint_setting->p_setting_name) == 0)
		{
			unsigned int *p_cur_setting = p_uint_setting->p_variable;
			*p_cur_setting = atoi(value);
			return;
		}
		p_uint_setting++;
	}
}