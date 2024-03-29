#include<iostream>
#include<sys/types.h> //数据类型定义 mode_t
#include<netinet/in.h> //struct sockaddr_in 
#include<sys/socket.h>  //socket bind listen accept connect ...
#include<sys/wait.h> //wait waitpid
#include<signal.h> //signal
#include<arpa/inet.h> //地址转换
#include<string.h> //bzero
#include<errno.h> //errno
#include<unistd.h> //read write..
#include<sys/select.h> //select
#include<stdlib.h> //exit
#include<stdio.h> //stdin stdout fileno
#include<fcntl.h> //open
#include<sys/stat.h> //S_IWUSR
#define SERV_PORT 9877
#define MAXLINE 4096	
#define LISTENQ 1024
void sig_chld(int);
void serv_do(int);
void cli_do(int);
