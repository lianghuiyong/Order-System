#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <error.h>
#define _DEBUG_

int main(void){
	sqlite3 *db = NULL;
	char *errmsg = 0;
	int rc;
	if((rc = sqlite3_open("foodmenu.db",&db))){
		perror("sqlite3_open");
		sqlite3_close(db);
		exit(1);
	}
	else printf("hello,you are succeed!\n");
	char *sql = "create table fdmenu(id1 integer primary key,varities text,foodname text,prices int);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(1,'甜品类','蛋糕',50);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(2,'甜品类','南瓜饼',60);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql	= "INSERT INTO fdmenu VALUES(3,'甜品类','糯米丸子',40);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(4,'火锅类','狗肉',88);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(5,'火锅类','羊肉',99);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(6,'火锅类','牛肉',98);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(7,'炒菜类','酸辣土豆丝',30);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(8,'炒菜类','青椒炒肉',40);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(9,'炒菜类','小白菜',25);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(10,'凉拌类','凉拌黄瓜',20);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(11,'凉拌类','花菜',22);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(12,'凉拌类','豆皮',25);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(13,'汤类','紫菜蛋汤',26);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(14,'汤类','排骨汤',50);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(15,'汤类','三鲜汤',33);";
	sqlite3_exec(db,sql,0,0,&errmsg);

	int nrow = 0;
	int ncolumn = 0;
	char **result;

	//sql = "select * from fdmenu where id2=2";
	int re;	
	re=sqlite3_get_table(db,"select * from fdmenu where varities like '汤类' ",&result,&nrow,&ncolumn,&errmsg);
	if(re != SQLITE_OK){
	 perror("sqlite3_get_table");
	 sqlite3_close(db);
	 exit(1);
	}
	int i =0;
	printf("row:%d\tcolumn:%d\n",nrow,ncolumn);
	printf("\nThe result of querying is :\n");
#if 1
	for(i=0;i<(nrow+1)*ncolumn;i++){
	if((i+1)%5 != 0){
			printf("%s\t",result[i]);
	}
	else
		printf("%s\n",result[i]);}
#endif
	sqlite3_free_table(result);

#ifndef _DEBUG_
	printf("errmsg=%s\n",errmsg);
#endif
	sqlite3_close(db);
	return 0;
}
