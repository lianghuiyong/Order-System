#include "server.h"
#define JSNUM 100
/*cli pthread:deal the client data*/
void *fun(void *arg)
{
	char buf_fun[BUFSIZ];
	bzero(buf_fun,BUFSIZ);
	memcpy(buf_fun,(char *)arg,BUFSIZ);
#if DEBUG
	printf("thread :%s\n",buf_fun);
#endif
#if JSON
	/*decording json*/
	json_object *jiebao, *jiebao_cmd, *jiebao_flag;
	jiebao= json_tokener_parse(buf_fun);

	const char *pstr;
	jiebao_cmd=json_object_array_get_idx(jiebao,0);
	jiebao_flag=json_object_object_get(jiebao_cmd,"fla");
	pstr =json_object_get_string(jiebao_flag);
	switch(atoi(pstr)){
		/*search for seat*/
	case 11:
		{
			int re;	
			char **result;
			int nrow = 0;
			int ncolumn = 0;
			char *errmsg;

			if(pthread_mutex_lock(&mutex)){
				printf("database lock failed!\n");
				pthread_exit(NULL);
			}
			/*search db*/
			re=sqlite3_get_table(db,"select * from tbmenu",&result,&nrow,&ncolumn,&errmsg);
			if(re != SQLITE_OK){
				printf("%s\n",errmsg);
				exit(-1);
			}
			pthread_mutex_unlock(&mutex);

			int x = 0,y = 0,index = 0;
			index = ncolumn;
			/*pakage json*/
			struct json_object *my_json[nrow];

			for( x=0; x<nrow; x++){
				my_json[x]=json_object_new_object();
			}

			for( x=0; x<nrow; x++){
				for( y=0; y<ncolumn; y++){
					//printf("%s\t",result[index++]);
					json_object_object_add(my_json[x],result[y],json_object_new_string(result[index++]));
				}
			}

			sqlite3_free_table(result);

			struct json_object *json_shuzu;
			json_shuzu=json_object_new_array();
			for( x=0; x<nrow; x++){
				json_object_array_add(json_shuzu,my_json[x]);
			}

			const char * buf_cst =json_object_to_json_string(json_shuzu);


			write(cli_fd,buf_cst,strlen(buf_cst));
#if DEBUG
			printf("jiebao:%s\n",buf_cst);
#endif

		}break;
	case 12:
		{
			int json_length = json_object_array_length(jiebao);
			if(json_length == 1){
				char *buf_no= "NO";
				write(cli_fd,buf_fun,strlen(buf_no));
				break;
			}
			json_object *json_seat[json_length],*json_seat_tmp;
			int i;
			for(i=1; i<json_length; i++){
				json_seat[i]= json_object_array_get_idx(jiebao,i);
				//json_seat_tmp = json_object_object_get(json_seat[i],result[j]);
			}
			/*json_cmd is the first object*/
			const char *ppstr;
			ppstr =json_object_get_string(json_seat[i]);

		}break;
	case 21:
		{
			int re;	
			char **result;
			int nrow = 0;
			int ncolumn = 0;
			char *errmsg;

			if(pthread_mutex_lock(&mutex)){
				printf("database lock failed!\n");
				pthread_exit(NULL);
			}
			/*search db*/
			re=sqlite3_get_table(db,"select * from fdmenu",&result,&nrow,&ncolumn,&errmsg);
			if(re != SQLITE_OK){
				printf("%s\n",errmsg);
				exit(-1);
			}
			pthread_mutex_unlock(&mutex);

			int x = 0,y = 0,index = 0;
			index = ncolumn;

			/*pakage json*/
			struct json_object *my_json[nrow];

			for( x=0; x<nrow; x++){
				my_json[x]=json_object_new_object();
			}

			for( x=0; x<nrow; x++){
				for( y=0; y<ncolumn; y++){
					//printf("%s\t",result[index++]);
					json_object_object_add(my_json[x],result[y],json_object_new_string(result[index++]));
				}
			}

			sqlite3_free_table(result);

			struct json_object *json_shuzu;
			json_shuzu=json_object_new_array();
			for( x=0; x<nrow; x++){
				json_object_array_add(json_shuzu,my_json[x]);
			}

			const char * buf_cst =json_object_to_json_string(json_shuzu);


			write(cli_fd,buf_cst,strlen(buf_cst));
#if DEBUG
			printf("jiebao:%s\n",buf_cst);
#endif

		}break;
	case 22:;
	case 31:;
	case 32:;
	default:break;
	}

#else	
	/*write to cli*/
	write(cli_fd,buf_fun,strlen(buf_fun));
#endif
	pthread_exit(0);
}

/*cook pthread*/
void *cook_fun(void *arg)
{
	struct message msg;
	int pid;
	int rvmsg;
	pid = init_msg(&msg);
	while(1){
		/*waiting to cook*/
		if((rvmsg = msgrcv(pid, (void*)&msg, BUFSIZ, 1, 0)) < 0)
			handle_error("msgrcv");
		sleep(5);
		printf("cook done %s\n",msg.msg_text);
		/*check if there has client urging*/
		if((rvmsg = msgrcv(pid, (void*)&msg, BUFSIZ, 2, IPC_NOWAIT)) < 0)
			handle_error("msgrcv");
		/*has client urging*/
		else if(rvmsg != 0)
		{
			printf("%d people is waiting!! come on, good cooker...",atoi(msg.msg_text));
			goto con;
		}

con:	continue;
	}
	pthread_exit(0);
}


