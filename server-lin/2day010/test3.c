#include <stdio.h>
#include<stdlib.h>
#include"sqlite3.h"
#include <error.h>
#include<strings.h>
void sight(char *sql);
void cust(int tb_id,char *cust_name);
void add(int fd_id,char *cust_name);//实现加菜功能
void fd_del(int fd_id,char *cust_name);//实现去除订单功能
#if 1
int main(void)
{
	//char *sql = "select * from tbmenu;";
	char *cust_name = "mlz";
	//int tb_id = 3;
	cust(8,cust_name);
 	/*add(3,cust_name);//实现加菜功能
 	add(4,cust_name);//实现加菜功能
 	add(11,cust_name);//实现加菜功能
 	add(8,cust_name);//实现加菜功能*/
	fd_del(11,cust_name);
	fd_del(4,cust_name);
	return 0;
}
#endif
void sight(char *sql)//显示菜单和餐桌的函数
{
	sqlite3 *db = NULL;
	char *errmsg = 0;
	int rc,re;
	int nrow,ncolumn;
	char **result;
	if ((rc=sqlite3_open("foodmenu.db",&db)) == SQLITE_OK)
		printf("welcome to you!\n");
	else{
		printf("falied to open!\n");
		sqlite3_close(db);
		exit(1);
		}
	re = sqlite3_get_table(db,sql,&result,&nrow,&ncolumn,&errmsg);
	if(re == SQLITE_OK)
		{printf("很高兴为您服务！\n");}
	else{
		printf("falied to open2!\n");
		sqlite3_close(db);
		exit(1);}
	int i=0;
	printf("nrow:%d\t ncolumn:%d\n",nrow,ncolumn);
	for(i=0;i<(nrow+1)*ncolumn;i++){
		printf("%s\t",result[i]);
	}
}
void cust(int tb_id,char *cust_name)//给定桌子号和顾客姓名创建新的表格
{
	sqlite3 *db = NULL;
	char *errmsg = 0;
	int rc;
	if ((rc=sqlite3_open("foodmenu.db",&db)) == SQLITE_OK)
		printf("welcome to you!\n");
	else{
		printf("falied to open!\n");
		sqlite3_close(db);
		exit(1);
		}
	char sql[BUFSIZ];
	sprintf(sql,"create table %s(id1 integer primary key,tb_id1 int,cust_name1 text,fd_id int,fd_name text,prices int,cond int );",cust_name);
	sqlite3_exec(db,sql,0,0,&errmsg);
	bzero(sql,sizeof(BUFSIZ));
	sprintf(sql,"insert into %s values(0,%d,'%s',0,0,0,0);",cust_name,tb_id,cust_name);
	printf("%s\n",sql);
	sqlite3_exec(db,sql,0,0,&errmsg);
	sprintf(sql,"update tbmenu set condition = 1 where id1 = %d;",tb_id);
	sqlite3_exec(db,sql,0,0,&errmsg);
}

void add(int fd_id,char *cust_name)//实现加菜功能
{
	sqlite3 *db = NULL;
	char *errmsg = 0;
	int rc;
	if((rc = sqlite3_open("foodmenu.db",&db) != SQLITE_OK)){
		printf("failed to open foodmenu.db!\n");
		sqlite3_close(db);
		exit(1);
	}	
	char sql[BUFSIZ];
	sprintf(sql,"insert into %s(fd_id,fd_name,prices) select id1,foodname,prices from fdmenu where id1 = %d;",cust_name,fd_id);
	sqlite3_exec(db,sql,0,0,&errmsg);
	sprintf(sql,"update %s set cond = 0 where fd_id = %d;",cust_name,fd_id);
	sqlite3_exec(db,sql,0,0,&errmsg);

}

void fd_del(int fd_id,char *cust_name)
{
	sqlite3 *db = NULL;
	char *errmsg = 0;
	int rc;
	if((rc = sqlite3_open("foodmenu.db",&db)) != SQLITE_OK)
	{
		printf("failed to open!\n");
		sqlite3_close(db);
		exit(0);
	}
	char sql[BUFSIZ];
	sprintf(sql,"delete from %s where fd_id = %d and cond != 1;",cust_name,fd_id);
	sqlite3_exec(db,sql,0,0,&errmsg);
#if 0
	if(errmsg == 0) printf("success!\n");//本来想实现未成功删除报错，结果未实现
	else
	{	
		printf("failed to delete!\n");
		sqlite3_close(db);
		exit(0);
	}
#endif
}
