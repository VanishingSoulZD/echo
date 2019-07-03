#include"echo.h"
void serv_do(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];
again:
	while((n=read(sockfd,buf,MAXLINE))>0)
		write(sockfd,buf,n);
	if(n<0&&errno==EINTR)
		goto again;
	else if(n<0)
	{
		std::cout<<"serv_do: read error\n";
		exit(1);
	}
}
