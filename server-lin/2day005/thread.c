#include "server.h"

/*cli pthread:deal the client data*/
void *fun(void *arg)
{
	int re;	
	char **result;
	int nrow = 0;
	int ncolumn = 0;
	char *errmsg;
	int rc;
	sqlite3 *db;
	if((rc = sqlite3_open("foodmenu.db",&db))){
		perror("sqlite3_open");
		sqlite3_close(db);
		exit(1);
	}

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

	int i = json_object_array_length(jiebao);
	int ii = i;
	const char *pstr;
	for(;i>0;){
		if(i == ii)
		{
			jiebao_cmd=json_object_array_get_idx(jiebao,--i);
			jiebao_flag=json_object_object_get(jiebao_cmd,"fla");
			pstr =json_object_get_string(jiebao_flag);
		}
		switch(atoi(pstr)){
			/*search for seat*/
		case 11:
			{

				re=sqlite3_get_table(db,"select * from fdmenu where id1 = 10 ",&result,&nrow,&ncolumn,&errmsg);
				if(re == SQLITE_OK){
					printf("success");
									}
				else{
					printf("%s\n",errmsg);
					exit(-1);
				}
				int x = 0,y = 0;
				for( x=1; x<=nrow; x++){
					for( y=1; y<=ncolumn; y++){
						printf("%s\n",result[x*(y-1)]);
					}
				}
				printf("x = %d,y = %d\n",x,y);
				sqlite3_free_table(result);
				sqlite3_close(db);


				write(cli_fd,pstr,strlen(pstr));
#if DEBUG
				printf("jiebao:%d\n",atoi(pstr));
#endif
				break;
			}
		case 12:;
		case 21:;
		case 22:;
		case 31:;
		case 32:;
		default:goto end;
		}
end:	break;
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


