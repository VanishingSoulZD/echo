#include"echo.h"
void cli_do(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];
	int maxfdp1,stdineof=0;
	fd_set rset;

	FD_ZERO(&rset);
	for(;;)
	{
		if(stdineof==0)
			FD_SET(fileno(stdin),&rset);
		FD_SET(sockfd,&rset);
		maxfdp1=std::max(sockfd,fileno(stdin))+1;
		select(maxfdp1,&rset,NULL,NULL,NULL);

		if(FD_ISSET(sockfd,&rset))
		{
			if((n=read(sockfd,buf,MAXLINE))==0)
			{
				if(stdineof==1)
					return;
				else
				{
					std::cout<<"server terminated prematurely\n";
					exit(1);
				}
			}
			write(fileno(stdout),buf,n);
		}
		if(FD_ISSET(fileno(stdin),&rset))
		{
			if((n=read(fileno(stdin),buf,MAXLINE))==0)
			{
				stdineof=1;
				shutdown(sockfd,SHUT_WR);
				FD_CLR(fileno(stdin),&rset);
				continue;
			}
			write(sockfd,buf,n);
		}
	}
}
