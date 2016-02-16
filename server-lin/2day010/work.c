#include "server.h"
#define WELCOME 0
#define WORK 1
#define ENDING 2
#define STDIN 0


void display_detail(char **result,int nrow,int ncolumn)
{
	system("clear");
	int x = 0,y = 0,index = 0;
	index = ncolumn;
	/*pakage json*/
	struct json_object *my_json[nrow];

	for( x=0; x<ncolumn; x++){
		printf("%s\t",result[x]);
	}
	printf("\n");
	for( x=0; x<nrow; x++){
		for( y=0; y<ncolumn; y++){
			printf("%s\t",result[index++]);
		}
		printf("\n");
	}
	printf("%s",buf_cook);
}
void displey_normal(int nrow)
{
	system("clear");
	printf("------total clients today:%6d-----------------------\n",total_client);
	printf("------total money:%6d-------------------------------\n",total_money);
	printf("------waiting people:%6d----------------------------\n",nrow);
	printf("------click (Enter Key) to show waiting detail---------\n");
	printf("------click (p Key + Enter Key) to show protocol-------\n");
	printf("%s",buf_cook);
}
void display_wel(void)
{
	system("clear");
	printf("-------------------------------------------------\n");
	printf("------------------Welcome to work----------------\n");
	printf("-------------Happy working Happy day-------------\n");
	printf("-------------------------------------------------\n");
}
void display_protocol()
{
	system("clear");
	printf("\
------------------server protocol----------------------\n\
all data is using json to package----------------------\n\
get [{'fla':'cmd'}], server do as the cmd--------------\n\
cmd == 11 : query seat---------------------------------\n\
cmd == 12 : choose seat--------------------------------\n\
cmd == 21 : query food tab-----------------------------\n\
cmd == 22 : hand up the food tab-----------------------\n\
cmd == 23 : add food to food tab-----------------------\n\
cmd == 31 : urging for faster--------------------------\n\
cmd == 41 : apply for meney----------------------------\n\
cmd == 51 : off line soon------------------------------\n\
-------------------------------------------------------\n\
click Enter to show waiting detail---------------------\n");
}

void display_wrk(void)
{
	int re;	
	char **result;
	int nrow = 0;
	int ncolumn = 0;
	char *errmsg;
	char cust_name[100];
	int i ;
	struct timeval tv;
	char buf[BUFSIZ];
	fd_set readfd;
	int re_se;
	int itime = 0,ptime=0;
	while(1){
		tv.tv_sec = 2;
		tv.tv_usec = 0;
		FD_ZERO(&readfd);
		FD_SET(STDIN, &readfd); 
		if((re_se = select(STDIN+ 1,&readfd,NULL,NULL,&tv)) == -1){
			printf("select error\n");
		}
		else if(re_se == 0&&itime ==0&&ptime==0){
			if(pthread_mutex_lock(&mutex)){
				printf("database lock failed!\n");
				pthread_exit(NULL);
			}

			re=sqlite3_get_table(db,"select condition from tbmenu where condition = 1",&result,&nrow,&ncolumn,&errmsg);
			if(re != SQLITE_OK){
				printf("%s\n",errmsg);
				exit(-1);
			}
			pthread_mutex_unlock(&mutex);
			sqlite3_free_table(result);
			displey_normal(nrow);

		}
		else if(FD_ISSET(STDIN,&readfd)){
			fgets(buf,BUFSIZ,stdin);
			if(!strncmp(buf,"\n",1)){

				if(pthread_mutex_lock(&mutex)){
					printf("database lock failed!\n");
					pthread_exit(NULL);
				}
				re=sqlite3_get_table(db,"select * from tbmenu",&result,&nrow,&ncolumn,&errmsg);
				if(re != SQLITE_OK){
					printf("%s\n",errmsg);
				}
				pthread_mutex_unlock(&mutex);
				sqlite3_free_table(result);
				display_detail(result,nrow,ncolumn);
				itime = 2;
				ptime = 0;
			}
			else if(!strncmp(buf,"p\n",2))
			{
				display_protocol();
				itime = 0;
				ptime = 10;
			}
		}
		if(itime!=0){

			if(pthread_mutex_lock(&mutex)){
				printf("database lock failed!\n");
				pthread_exit(NULL);
			}
			re=sqlite3_get_table(db,"select * from tbmenu",&result,&nrow,&ncolumn,&errmsg);
			if(re != SQLITE_OK){
				printf("%s\n",errmsg);
			}
			pthread_mutex_unlock(&mutex);
			sqlite3_free_table(result);
			display_detail(result,nrow,ncolumn);

			itime--;
		}
		if(ptime!=0){
			ptime--;
			display_protocol();
		}
		/*get data*/
		/*
		   re=sqlite3_get_table(db,"select * from tbmenu",&result,&nrow,&ncolumn,&errmsg);
		   if(re != SQLITE_OK){
		   printf("%s\n",errmsg);
		   }
		   sqlite3_free_table(result);
		   display_detail(result,nrow,ncolumn);


		   re=sqlite3_get_table(db,"select condition from tbmenu where condition = 1",&result,&nrow,&ncolumn,&errmsg);
		   if(re != SQLITE_OK){
		   printf("%s\n",errmsg);
		   exit(-1);
		   }
		   sqlite3_free_table(result);
		   displey_normal(nrow);
		   */
	}
}


void display_end(void)
{
	printf("-------------------------------------------------\n");
	printf("------------------Thanks for work----------------\n");
	printf("-----------------Have a good night---------------\n");
	printf("-------------------------------------------------\n");
}


void display(int worksds)
{
	switch(worksds){
	case WELCOME:display_wel();break;
	case WORK:display_wrk();break;
	case ENDING:display_end();break;
	}
}
/*worker thread*/
void *work_fun(void *arg)
{
	display(WELCOME);
	//sleep(1);
	display(WORK);
	display(ENDING);
	pthread_exit(0);
}


