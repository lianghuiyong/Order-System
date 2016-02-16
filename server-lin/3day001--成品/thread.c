#include "server.h"
#define JSNUM 100
/*cli pthread:deal the client data*/
void *fun(void *arg)
{
	int cli_fd_t = cli_fd;
	char buf_fun[BUFSIZ];
	bzero(buf_fun,BUFSIZ);
	memcpy(buf_fun,(char *)arg,BUFSIZ);
	/*pose sem let main function continue*/
	sem_post(&sem);
#if DEBUG
	printf("thread original data :---------------------------------\n%s\n",buf_fun);
	printf("strlen of buf_fun :---------------------------------%d\n",strlen(buf_fun));
#endif
	//if(strncmp(buf_fun,"\n",1) == 0)
	//	pthread_exit(0);
	if(strlen(buf_fun) <= 9)
		pthread_exit(0);

	/*decording json*/
	json_object *jiebao, *jiebao_cmd, *jiebao_flag;
	jiebao= json_tokener_parse(buf_fun);

	const char *pstr;
	jiebao_cmd=json_object_array_get_idx(jiebao,0);
	jiebao_flag=json_object_object_get(jiebao_cmd,"fla");
	pstr =json_object_get_string(jiebao_flag);
	int int_pstr = atoi(pstr);
	switch(int_pstr){
#if DEBUG
		printf("pstr == %s\n",pstr);
#endif
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
			//pthread_mutex_unlock(&mutex);
			/*search db*/
			re=sqlite3_get_table(db,"select * from tbmenu",&result,&nrow,&ncolumn,&errmsg);
			if(re != SQLITE_OK){
				printf("%s\n",errmsg);
				//exit(-1);
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
			write(cli_fd_t,buf_cst,strlen(buf_cst));
#if DEBUG
			printf("return seat json:--------------------------------\n%s\n",buf_cst);
#endif
		}break;
		/*choose one table*/
	case 12:
		{
			int json_length = json_object_array_length(jiebao);
			if(json_length != 2){
				char *buf_no= "NO";
				//write(cli_fd_t,buf_no,strlen(buf_no));
				//break;
				pthread_exit(0);
			}
			else {
				char *buf_ok="OK";
				//write(cli_fd_t,buf_ok,strlen(buf_ok));
			}
			json_object *json_seat,*json_seat_tmp;
			json_seat = json_object_array_get_idx(jiebao,1);
			int tb_id;
			char cust_name[30];
			const char *ppstr;
			json_seat_tmp = json_object_object_get(json_seat,"id1");
			ppstr =json_object_get_string(json_seat_tmp);
			tb_id = atoi(ppstr);
			sprintf(cust_name,"cli_id_%d",cli_fd_t);

			if(pthread_mutex_lock(&mutex)){
				printf("database lock failed!\n");
				pthread_exit(NULL);
			}
			cust(tb_id,cust_name);
			pthread_mutex_unlock(&mutex);
#if DEBUG
			printf("booking seat OK!--------------------------------------\n");
#endif
		}break;
		/*search for food*/
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


			write(cli_fd_t,buf_cst,strlen(buf_cst));
#if DEBUG
			printf("send food table to client:------------------------------------\n%s\n",buf_cst);
#endif
		}break;
		/*add food*/
	case 23:;
			/*hand up the food tab*/
	case 22:
			{
				int json_length = json_object_array_length(jiebao);

				if(json_length == 1){
					char *buf_no= "NO";
					//write(cli_fd_t,buf_no,strlen(buf_no));
					//break;
					pthread_exit(0);
				}
				else {
					char *buf_ok="OK";
					//write(cli_fd_t,buf_ok,strlen(buf_ok));
					if(int_pstr == 22)
						total_client++;
				}
				json_object *json_fd[json_length],*json_fd_tmp[3];
				int i;
				const char *ptmp[3];
				char cust_name22[30];
				sprintf(cust_name22,"cli_id_%d",cli_fd_t);
				//char tmpchar[20];
				for(i = 1; i < json_length; i++){
					json_fd[i]= json_object_array_get_idx(jiebao,i);
					json_fd_tmp[0] = json_object_object_get(json_fd[i],"id1");//fd_id
					json_fd_tmp[1] = json_object_object_get(json_fd[i],"foodname");//fd_name
					json_fd_tmp[2] = json_object_object_get(json_fd[i],"prices");//prices
					int n;
					for(n = 0; n < 3; n++){
						ptmp[n] = json_object_get_string(json_fd_tmp[n]);
					}
					//bzero(tmpchar,20);
					//strcpy(tmpchar,ptmp[1]);
					//insert_cust(cust_name22, atoi(ptmp[0]),tmpchar,atoi(ptmp[2]));
					if(pthread_mutex_lock(&mutex)){
						printf("database lock failed!\n");
						pthread_exit(NULL);
					}
					add(atoi(ptmp[0]),cust_name22);
					pthread_mutex_unlock(&mutex);
				}

				struct message msg;
				int pid;
				pid = init_msg(&msg);
				msg.msg_type = 1;
				strncpy(msg.msg_text,cust_name22,strlen(cust_name22));
				if(msgsnd(pid, &msg, strlen(msg.msg_text),0) == -1)
					handle_error("msgsnd");

#if DEBUG
				printf("got food table from client.----------------------------------\n");
				printf("it is waiting to be cook.----------------------------------\n");
#endif
			}break;

			/*ask for faster*/
	case 31:
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
				re=sqlite3_get_table(db,"select condition from tbmenu where condition = 1",&result,&nrow,&ncolumn,&errmsg);
				if(re != SQLITE_OK){
					printf("%s\n",errmsg);
					exit(-1);
				}
				pthread_mutex_unlock(&mutex);
				sqlite3_free_table(result);

#if DEBUG
				printf("get asking :%d pepeo---\n",nrow);
#endif
				struct message msg;
				int pid;
				pid = init_msg(&msg);
				msg.msg_type = 2;
				bzero(msg.msg_text,BUFSIZ);
				char buf[100];
				bzero(buf,100);
				sprintf(buf,"%d",nrow);
				strncpy(msg.msg_text,buf,strlen(buf));
#if DEBUG
				printf("msgsnd contain %s\n", msg.msg_text);
#endif
				if(msgsnd(pid, &msg, strlen(msg.msg_text),0) == -1)
					handle_error("msgsnd");
#if DEBUG
				printf("msgsnd ok\n");
#endif
			}break;
			/*apply for money*/
	case 41:
			{
#if DEBUG
				printf("come into 41: \n");
#endif
				int json_length = json_object_array_length(jiebao);
				if(json_length != 2){
					char *buf_no= "NO";
					//write(cli_fd_t,buf_no,strlen(buf_no));
					break;
				}
#if DEBUG
				printf("not break here: \n");
#endif
				json_object *json_moy,*json_moy_tmp;
				json_moy_tmp = json_object_array_get_idx(jiebao,1);
				json_moy = json_object_object_get(json_moy_tmp,"prices");	
				char cust_name31[30];
				sprintf(cust_name31,"cli_id_%d",cli_fd_t);
				const char *moy_tmp = json_object_get_string(json_moy);

				if(pthread_mutex_lock(&mutex)){
					printf("database lock failed!\n");
					pthread_exit(NULL);
				}
				insert_cust(cust_name31, 0,NULL,atoi(moy_tmp));//total money
				total_money += atoi(moy_tmp);
#if DEBUG
				printf("money is :%s\n",moy_tmp);
				printf("%d\n",total_money);
#endif
				pthread_mutex_unlock(&mutex);
#if DEBUG
				printf("client apply for money.---------------------------------------\n");
#endif
			}break;

			/*client off line or have applied the money*/
	case 51:
			{
				if(pthread_mutex_lock(&mutex)){
					printf("database lock failed!\n");
					pthread_exit(NULL);
				}
				char cust_name_delete[30];
				sprintf(cust_name_delete,"cli_id_%d",cli_fd_t);//delete the table of a client
				cust_delete(cust_name_delete);
				if(strlen(buf_cli) > (BUFSIZ-60))
					bzero(buf_cli,BUFSIZ);
				sprintf(buf_cli+strlen(buf_cli),"\n--------client %s apply for money----------\n",cust_name_delete);
				pthread_mutex_unlock(&mutex);
			}break;
	default:break;
	}
	pthread_exit(0);
}

/*cook pthread*/
void *cook_fun(void *arg)
{
	struct message msg;
	int pid;
	int rvmsg;
	int rvm;
	int i;
	pid = init_msg(&msg);
	bzero(buf_cook,BUFSIZ);
	sprintf(buf_cook,"*******************************************************\n**********************cooker state*********************\n*********************waiting for cooking***************\n*******************************************************\n");
	while(1){
		/*waiting to cook*/
		if((rvmsg = msgrcv(pid, (void*)&msg, BUFSIZ, 1, IPC_NOWAIT)) <= 0){
			//continue;
		}
		else if(rvmsg > 0)
		{
			if(pthread_mutex_lock(&mutex)){
				printf("database lock failed!\n");
				pthread_exit(NULL);
			}
			update_cust(msg.msg_text);
			pthread_mutex_unlock(&mutex);
			bzero(buf_cook,BUFSIZ);
			sprintf(buf_cook,"*******************************************************\n**********************cooker state*********************\n*********************begin to cooking******************\n*******************************************************\n");
			for(i = 0; i< 10; i++){
				sleep(1);
				/*check if there has client urging*/
				if((rvm = msgrcv(pid, (void*)&msg, BUFSIZ, 2, IPC_NOWAIT)) <= 0){
					//continue;
				}
				/*has client urging*/
				else if(rvm > 0)
				{
					char buf_ala[BUFSIZ];
					bzero(buf_ala,BUFSIZ);
					sprintf(buf_ala,"\ncome on, good cooker...\n");
					strncpy(buf_cook+strlen(buf_cook),buf_ala,strlen(buf_ala));
				}

			}
			bzero(buf_cook,BUFSIZ);
			sprintf(buf_cook,"*******************************************************\n***************client %3s's food is done**********\n*********************And waiting for cooking***********\n*******************************************************\n",msg.msg_text);
			sleep(2);
			bzero(msg.msg_text,BUFSIZ);
		}

	}
	pthread_exit(0);
}


