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

		/*-----------------encording json------------------------*/
		/*encording one record of database table*/
		struct json_object *my_json;
		my_json=json_object_new_object();

		json_object_object_add(my_json,"fla",json_object_new_int(11));
		//json_object_object_add(my_json,"name",json_object_new_string("猪肉炒牛肉"));

		/*encording one record of database table*/
		/*
		struct json_object *my_json2;
		my_json2=json_object_new_object();

		json_object_object_add(my_json2,"id",json_object_new_int(2));
		json_object_object_add(my_json2,"name",json_object_new_string("猪肉炒青菜"));
		*/

		/*encording one database table*/
		struct json_object *json_shuzu;
		json_shuzu=json_object_new_array();
		json_object_array_add(json_shuzu,my_json);
		//json_object_array_add(json_shuzu,my_json2);

		/*encording to char* */
		const char * buf_cst =json_object_to_json_string(json_shuzu);
		//write(cli_fd,buf_cst,strlen(buf_cst));

		if(write(sock_fd,buf_cst,strlen(buf_cst)) < 0){
		//if(write(sock_fd,buf,strlen(buf)) < 0){
			perror("write");
			exit(1);
		}
		if(strncmp(buf,"quit",4) == 0)
			break;
		bzero(buf,BUFSIZ);
		if(read(sock_fd,buf,BUFSIZ) < 0){
			perror("read");
			exit(1);
		}
		printf("read: %s",buf);
#ifdef JSON
		/*encording one table*/
		/*
		json_object *jiebao_json2, *jiebao_json3,*jiebao_name2;
		jiebao_json2=json_tokener_parse(buf);

		int i = json_object_array_length(jiebao_json2);
		printf("%d\n",i);
		const char *jiebao_str2;
		int ii = i;
		for(;i>0;){
			jiebao_json3=json_object_array_get_idx(jiebao_json2,--ii);
			jiebao_name2=json_object_object_get(jiebao_json3,"name");
			jiebao_str2 =json_object_get_string(jiebao_name2);
			*/

			/*encording one record of database table*/
			/*
			   json_object *jiebao_json,*jiebao_name;
			   jiebao_json=json_tokener_parse(jiebao_str2);
			   jiebao_name=json_object_object_get(jiebao_json,"name");
			   const char *jiebao_str =json_object_get_string(jiebao_name);
			   */
			//printf("read: %s\n",jiebao_str2);
			//i--;
		//}
#endif
		bzero(buf,BUFSIZ);
	}
	/*close socket*/
	close(sock_fd);

	return 0;
}
