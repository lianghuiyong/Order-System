/*************************************************************************
	> File Name: display.h
	> Author: 
	> Mail: 
	> Created Time: 2015年03月17日 星期二 19时13分33秒
 ************************************************************************/

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include </usr/local/include/json/json.h>
#include <stddef.h>

extern void    hello_display();
extern void    * recv_from_server();
extern void    * send_to_server();
extern int     IS_table_condition_0(int , json_object *);
extern int     IS_menu_ID(int ,char *);
extern void    TO_server_order_11(int );
extern void    TO_server_order_12(int );
extern void    TO_server_order_21(int );
extern void    TO_server_order_22(int );
extern void    TO_server_order_31(int );
extern void    TO_server_order_41(int );
extern void    TO_server_order_51(int );
extern void    TO_server_order_23(int );

const  char *buf_cli;
const  char *menu_bak;
static char buf[BUFSIZ];       

//标志位初始化，使之进入发送函数 11选项
volatile static int  recv_server_num=0;  //标志步骤
volatile static int  send_server_num=11; //接收步骤
volatile static char flag = 0;           //线程异步标志
volatile static int  reminder_flag=0;    //催单标志
struct json_object* cli_table_choice;    //客户保存的桌号
struct json_object* cli_menu_choice;     //客户保存的菜单
struct json_object* cli_add_menu;        //客户加菜的菜单
#endif
