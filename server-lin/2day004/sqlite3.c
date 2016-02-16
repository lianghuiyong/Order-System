#include "server.h"

void init_sql(sqlite3 **dbfrom)
{
	sqlite3 *db = *dbfrom;
	char *errmsg = 0;
	int rc;
	if((rc = sqlite3_open("foodmenu.db",&db))){
		perror("sqlite3_open");
		sqlite3_close(db);
		exit(1);
	}
	char *sql = "create table fdmenu(id1 integer primary key,varities text,foodname text,prices int);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(1,'��Ʒ��','����',50);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(2,'��Ʒ��','�Ϲϱ�',60);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql	= "INSERT INTO fdmenu VALUES(3,'��Ʒ��','Ŵ������',40);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(4,'�����','����',88);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(5,'�����','����',99);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(6,'�����','ţ��,98);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(7,'������',��������˿',30);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(8,'������','�ཷ����',40);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(9,'������','С�ײ�',25);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(10,'������','����ƹ�',20);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(11,'������','����',22);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(12,'������','��Ƥ',25);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(13,'����','�ϲ˵���',26);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(14,'����','�Ź���',50);";
	sqlite3_exec(db,sql,0,0,&errmsg);
	sql = "INSERT INTO fdmenu VALUES(15,'����','������',33);";
	sqlite3_exec(db,sql,0,0,&errmsg);
}
