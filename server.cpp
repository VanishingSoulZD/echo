#include"echo.h"
void sig_chld(int);
void serv_do(int);
int main()
{
	int listenfd,connfd;
	pid_t childpid;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;

	listenfd=socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(SERV_PORT);
	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(listenfd,LISTENQ);
	
	signal(SIGCHLD,sig_chld);

	for(;;)
	{
		clilen=sizeof(cliaddr);
		if((connfd=accept(listenfd,(struct sockaddr *)&cliaddr,&clilen))<0)
		{
			if(errno==EINTR)
				continue;
			else
			{
				std::cout<<"server: accept error\n";
				exit(1);
			}
		}
		if((childpid=fork())==0)
		{
			close(listenfd);
			serv_do(connfd);
			exit(0);
		}
		close(connfd);
	}
}
