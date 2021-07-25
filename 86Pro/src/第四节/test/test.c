#include<stdio.h>
#include<unistd.h>
#include<shadow.h>
#include<crypt.h>
#include<pwd.h>

int main()
{

	struct spwd * spd = getspnam("bss");
	if(spd == NULL)
	{
		printf("2 user name error.\n");
		return -1;
	}

	char *encrypted_pw = crypt("letmein", spd->sp_pwdp);
	printf("%s\n", encrypted_pw);

	return 0;
}
