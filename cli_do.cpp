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
			{
				int oflag=O_WRONLY|O_APPEND|O_CREAT;
				mode_t mode=S_IRUSR|S_IWUSR;
				int outfd=open("output_his.file",oflag,mode);
				write(outfd,buf,n);
				write(fileno(stdout),buf,n);
			}
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
			{
				int oflag=O_WRONLY|O_APPEND|O_CREAT;
				mode_t mode=S_IRUSR|S_IWUSR;
				int infd=open("input_his.file",oflag,mode);	
				write(infd,buf,n);
 				write(sockfd,buf,n);
			}
		}
	}
}
