#include"echo.h"
#define MAXN 5
void cli_do(int);
int main(int argc,char **argv)
{
	int sockfd[MAXN];
	struct sockaddr_in servaddr;

	if(argc!=2)
	{
		std::cout<<"usage: ./client <IPaddress>\n";
		exit(1);
	}

	for(int i=0;i<MAXN;i++)
	{
		sockfd[i]=socket(AF_INET,SOCK_STREAM,0);
		
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family=AF_INET;
		servaddr.sin_port=htons(SERV_PORT);
		inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

		connect(sockfd[i],(struct sockaddr *)&servaddr,sizeof(servaddr));
	}
	cli_do(sockfd[0]);
	exit(0);
}
