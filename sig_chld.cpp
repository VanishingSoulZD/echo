#include"echo.h"
void sig_chld(int signo)
{
	int stat;
	pid_t pid;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		std::cout<<"child "<<pid<<" terminated\n";
}
