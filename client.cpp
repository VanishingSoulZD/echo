#include"echo.h"
int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc!=2)
	{
		std::cout<<"usage: ./client <IPaddress>\n";
		exit(1);
	}

	sockfd=socket(AF_INET,SOCK_STREAM,0);
		
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERV_PORT);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	cli_do(sockfd);

	exit(0);
}
