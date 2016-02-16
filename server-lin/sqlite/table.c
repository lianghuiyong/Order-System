#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <error.h>
#define _DEBUG_

int main(void){
	sqlite3 *db = NULL;
	char *errmsg = 0;
	int rc;
	if((rc = sqlite3_open("foodmenu.db",&db)))
	{
		perror("sqlite3_open");
		sqlite3_close(db);
		exit(1);
	}
	else printf("hello,you are succeed!\n");
	char *sql = "create table tbmenu(id1 integer primary key,varities text,site text,condition int);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(1,'四人座','一楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(2,'四人座','一楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(3,'四人座','一楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(4,'六人座','一楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(5,'六人座','一楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(6,'六人座','一楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(7,'二人座','二楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(8,'二人座','二楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(9,'十人座','二楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "insert into tbmenu values(10,'十人座','二楼',0);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	return 0;
}
