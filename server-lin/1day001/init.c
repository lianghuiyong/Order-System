#include "server.h"

void init_sock(int *sock_fd,struct sockaddr_in *sin, char *ip)
{
	/*create sock*/
	if((*sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		handle_error("socket");
	/*input addr*/
	bzero(sin,sizeof(struct sockaddr_in));
	(*sin).sin_family = AF_INET;
	(*sin).sin_port = htons(atoi(SERVER_PORT));
	(*sin).sin_addr.s_addr = inet_addr(ip);
	/*bind*/
	if(bind(*sock_fd,(struct sockaddr*)sin,sizeof(struct sockaddr_in)) < 0)
		handle_error("sock_fd");
	/*listen*/
	if(listen(*sock_fd,LISTEN_NUM) < 0)
		handle_error("listen");
}
