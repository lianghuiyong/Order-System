#include "server.h" 

#if 0
int main(void)
{
	//char *sql = "select * from tbmenu;";
	char *cust_name = "tablename";
	cust(3,cust_name);
	return 0;
}
#endif
/*create one table 
 * tb_id: == the id of desk the cli choose 
 * cust_name: == cli_id*/
void cust(int tb_id,char *cust_name)
{
	char *errmsg = 0;
	int rc,re;
	int nrow,ncolumn;
	char **result;
	/*
	if ((rc=sqlite3_open("foodmenu.db",&db)) == SQLITE_OK)
		printf("welcome to you!\n");
	else{
		printf("falied to open!\n");
		sqlite3_close(db);
		exit(1);
		}
		*/

	/*cond int : 
	 * can be return of goods
	 * 0 : can't
	 * 1 : can*/
	char sql[BUFSIZ];
	sprintf(sql,"create table %s(tb_id1 integer primary key,cust_name1 text,fd_id int,fd_name text,prices int,cond int );",cust_name);
	sqlite3_exec(db,sql,0,0,&errmsg);

	bzero(sql,sizeof(BUFSIZ));
	sprintf(sql,"insert into %s values(%d,%s,0,NULL,0,0);",cust_name,tb_id,cust_name);
	sqlite3_exec(db,sql,0,0,&errmsg);

	sprintf(sql,"update tbmenu set condition = 1 where id1 = %d;",tb_id);
	sqlite3_exec(db,sql,0,0,&errmsg);


}

/*insert one record to a table
 * the table must be create by cust() function*/
void insert_cust(char *cust_name,int fd_id, char *fd_name, int prices)
{
	char *errmsg = 0;
	int rc;
	/*
	if ((rc=sqlite3_open("foodmenu.db",&db)) == SQLITE_OK)
		printf("welcome to you!\n");
	else{
		printf("falied to open!\n");
		sqlite3_close(db);
		exit(1);
		}
		*/

	char sql[BUFSIZ];
	bzero(sql,sizeof(BUFSIZ));
	sprintf(sql,"insert into %s values(0,0,%d,%s,%d,0);",cust_name,fd_id,fd_name,prices);
	sqlite3_exec(db,sql,0,0,&errmsg);
}

/*init database 
 * create foodmenu
 * create two table on it*/
void table_init(void)
{
	//sqlite3 *db = NULL;
	char *errmsg = 0;
	int rc;
	if((rc = sqlite3_open("foodmenu.db",&db)))
	{
		perror("sqlite3_open");
		sqlite3_close(db);
		exit(1);
	}
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

	sql = "create table fdmenu(id1 integer primary key,varities text,foodname text,prices int);";
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

	sqlite3_close(db);
}
