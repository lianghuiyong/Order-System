#include "server.h"

#define DEBUG 1
#define THREADNUM 100
#define JSON
int cli_fd;

void *fun(void *arg)
{
	char buf_fun[BUFSIZ];
	bzero(buf_fun,BUFSIZ);
	memcpy(buf_fun,(char *)arg,BUFSIZ);
#ifdef DEBUG
	printf("thread :%s\n",buf_fun);
#endif
#ifdef JSON
	/*-----------------cording json------------------------*/
	/*cording one record of database table*/
	struct json_object *my_json;
	my_json=json_object_new_object();

	json_object_object_add(my_json,"id",json_object_new_int(1));
	json_object_object_add(my_json,"name",json_object_new_string("猪肉炒牛肉"));

/*cording one record of database table*/
	struct json_object *my_json2;
	my_json2=json_object_new_object();

	json_object_object_add(my_json2,"id",json_object_new_int(2));
	json_object_object_add(my_json2,"name",json_object_new_string("猪肉炒青菜"));

/*cording one table*/
struct json_object *json_shuzu;
json_shuzu=json_object_new_array();
json_object_array_add(json_shuzu,my_json);
	json_object_array_add(json_shuzu,my_json2);

	/*cording to char* */
	const char * buf_cst =json_object_to_json_string(json_shuzu);
	printf("%s\n",buf_cst);	
/*
	json_object *jiebao_json,*jiebao_name;
	jiebao_json=json_tokener_parse(buf_cst);
	jiebao_name=json_object_object_get(jiebao_json,"name");
	const char *jiebao_str =json_object_get_string(jiebao_name);
	printf("encording: %s\n",jiebao_str);
	*/

#endif
	/*write to cli*/
	write(cli_fd,buf_cst,strlen(buf_cst));
	pthread_exit(0);
}
int main(int argc, char **argv)
{
	if(argc != 2){
		fprintf(stderr,"Usage: %s <ip>",argv[0]);
		exit(1);
	}
	/*-------------init system-----------------*/
	int sock_fd,clisock_fd;
	struct sockaddr_in sin,cin;
	init_sock(&sock_fd,&sin,argv[1]);


	/*create database*/
	/*------------select-----------------------*/

	/*init list*/
	struct kool_list mylist;
	struct kool_list *tmp;
	struct list_head *pos, *q;
	INIT_LIST_HEAD(&mylist.list);

	int	maxfd;
	fd_set  readfds;
	int rv;
	struct timeval tv;
	pthread_t thread[THREADNUM] = {'\0'}; 
	while(1){
		maxfd = 0;
		FD_ZERO(&readfds); 
		FD_SET(sock_fd,&readfds);  
		maxfd = sock_fd;
		/*input the list number to readfds*/
		if(!list_empty(&mylist.list)){
			list_for_each_safe (pos, q, &mylist.list) {
				tmp = list_entry (pos, struct kool_list, list); 
#if DEBUG
				printf ("freeing item to= %d from= %d\n", tmp->to, tmp->from);
#endif
				FD_SET(tmp->from,&readfds);
				if(maxfd < tmp->from)
					maxfd = tmp->from;
#if DEBUG
				if(FD_ISSET(tmp->from,&readfds)){
					printf ("FD_ISSET success 1  to= %d from= %d\n", tmp->to, tmp->from);
				}
#endif
			}	  
		}

		tv.tv_sec = 5;
		tv.tv_usec = 0;
		if((rv = select(maxfd+1,&readfds,NULL,NULL,&tv)) <0)
			handle_error("select");

		if(rv == 0){
			printf("time out\n");
			continue;
		}else{
			/*sock_fd can read*/
			if(FD_ISSET(sock_fd,&readfds)){
				socklen_t len = sizeof(cin);
				bzero(&cin,sizeof(cin));

				if((clisock_fd = accept(sock_fd,(struct sockaddr*)&cin,&len)) < 0)
					handle_error("accept");
				/*add clisock_fd to list*/
				tmp = (struct kool_list *) malloc (sizeof (struct kool_list));
				tmp->from = clisock_fd;
				list_add(&(tmp->list),&(mylist.list));
#if DEBUG
				printf("client_IP:%s\n",inet_ntoa(cin.sin_addr));
#endif
			}
			/*clisock_fd can read*/
			if(!list_empty(&mylist.list)){
#if DEBUG
				printf ("!list_emptyi");
#endif
				list_for_each_safe (pos, q, &mylist.list) {
					tmp = list_entry (pos, struct kool_list, list); 
#if DEBUG
					printf ("into read module to= %d from= %d\n", tmp->to, tmp->from);
#endif
					if(FD_ISSET(tmp->from,&readfds)){
#if DEBUG
						printf ("FD_ISSET success to= %d from= %d\n", tmp->to, tmp->from);
#endif
						/*read from the clients*/
						char buf[BUFSIZ];
						int ret;
						bzero(buf,BUFSIZ);
						if((ret = read(tmp->from,buf,BUFSIZ)) < 0)
							handle_error("read");	
#if DEBUG
						printf("%s\n",buf);
#endif
						if(ret == 0){
							/*delete the clisock_fd from list*/
							list_del (pos);
							close(tmp->from);
							free (tmp);
#if DEBUG
							printf("one cli is offline\n");
#endif
						}
						else{
							cli_fd = tmp->from;
							if(pthread_create(&thread[tmp->from - 3],NULL,fun,(void*)buf) != 0)
								handle_error("pthread_create");
						}
					}
				}
			}
		}
	}
	return 0;
}
