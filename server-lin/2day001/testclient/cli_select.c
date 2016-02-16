#include "net.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include </usr/local/include/json/json.h>
#define JSON

int main(int argc,char **argv)
{
      int sock_fd;
      struct sockaddr_in sin;

      if(argc != 3){
	    fprintf(stderr,"Usage:%s <port> <IP>\n",argv[0]);
	    exit(1);
      }
	  /*build socket*/
      if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
	    perror("socket");
	    exit(1);
      }
	  /*input ip and port*/
      bzero(&sin,sizeof(sin));
      sin.sin_family = AF_INET;
      sin.sin_port = htons(atoi(argv[1]));
      sin.sin_addr.s_addr = inet_addr(argv[2]);
      /*connect the server*/ 
      if((connect(sock_fd,(struct sockaddr*)&sin,sizeof(sin))) < 0){
	    perror("connect");
	    exit(1);
      }
	  /*write and read*/
      char buf[BUFSIZ];
      while(1){
	    bzero(buf,BUFSIZ);
	    fgets(buf,BUFSIZ,stdin);
	    if(write(sock_fd,buf,strlen(buf)) < 0){
		  perror("write");
		  exit(1);
	    }
	    if(strncmp(buf,"quit",4) == 0)
		  break;
	    if(read(sock_fd,buf,BUFSIZ) < 0){
		  perror("read");
		  exit(1);
	    }
		printf("read: %s",buf);
#ifdef JSON
		json_object *jiebao_json,*jiebao_name;
		jiebao_json=json_tokener_parse(buf);
		jiebao_name=json_object_object_get(jiebao_json,"name");
		const char *jiebao_str =json_object_get_string(jiebao_name);
		printf("read: %s",jiebao_str);
#endif
		bzero(buf,BUFSIZ);
      }
	  /*close socket*/
      close(sock_fd);

      return 0;
}
