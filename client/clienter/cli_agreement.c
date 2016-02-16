/*************************************************************************
	> File Name: order_to_server.c
	> Author: 
	> Mail: 
	> Created Time: 2015年03月19日 星期四 11时44分32秒
 ************************************************************************/

#include "head.h"

//发送
/*-----------------------------------------------------------
*   相关协议：两位数，第一位表示功能：
*   1：选座     2：菜谱     3：催单    4：结账
*  
*   第二位表示功能：
*   选座1： 1：查询   2：订座   3：换位
*   菜谱2： 1：查询   2：下单   
*   催单3： 1：催单
*   结账4： 1：申请结账
*
------------------------------------------------------------*/
void TO_server_order_11(int cli_fd2){
    //发送协议查询桌位情况
    struct json_object *json_obj;
    struct json_object *json_shuzhu;

    json_obj=json_object_new_object();
    json_object_object_add(json_obj,"fla",json_object_new_int(11));

    json_shuzhu=json_object_new_array();
    json_object_array_add(json_shuzhu,json_obj);
    buf_cli=json_object_to_json_string(json_shuzhu);
    if(send(cli_fd2, buf_cli, strlen(buf_cli), 0) < 0){
        perror("send");
        exit(-1);
    }
    json_object_put(json_obj);
    json_object_put(json_shuzhu);


}
void TO_server_order_12(int cli_fd2){
    //-----------------------------(1)发送订座信号
    //发送协议查询桌位情况
    struct json_object *json_table;
    struct json_object *json_table_shuzhu;
    json_table=json_object_new_object();
    json_object_object_add(json_table,"fla",json_object_new_int(12));
   //将命令12与选好的桌号发送给服务器
    //将cli_table_choice和json_table对象放进 json_table_shuzhu里
    json_table_shuzhu=json_object_new_array();
    json_object_array_add(json_table_shuzhu,json_table);
    json_object_array_add(json_table_shuzhu,cli_table_choice);
    buf_cli=json_object_to_json_string(json_table_shuzhu);
  if(send(cli_fd2, buf_cli, strlen(buf_cli), 0) < 0){
        perror("send");
        exit(-1);
    }
  
    //释放json对象
    json_object_put(json_table);
    json_object_put(json_table_shuzhu);
}

void TO_server_order_21(int cli_fd2){
    //发送协议查询桌位情况
    struct json_object *json_obj;
    struct json_object *json_shuzhu;

    json_obj=json_object_new_object();
    json_object_object_add(json_obj,"fla",json_object_new_int(21));

    json_shuzhu=json_object_new_array();
    json_object_array_add(json_shuzhu,json_obj);
    buf_cli=json_object_to_json_string(json_shuzhu);
   if(send(cli_fd2, buf_cli, strlen(buf_cli), 0) < 0){
        perror("send");
        exit(-1);
    }
    json_object_put(json_obj);
    json_object_put(json_shuzhu);

}
void TO_server_order_22(int cli_fd2){
    //-----------------------------(1)发送订座信号
    //发送协议查询桌位情况
    static int i;
    struct json_object *json_menu;
    struct json_object *json_menu_shuzhu;
    json_menu=json_object_new_object();
    json_object_object_add(json_menu,"fla",json_object_new_int(22));
    
    //将命令12与选好的桌号发送给服务器
    //将cli_table_choice和json_table对象放进 json_table_shuzhu里
    json_menu_shuzhu=json_object_new_array();
    json_object_array_add(json_menu_shuzhu,json_menu);
    for(i=0;i<json_object_array_length(cli_menu_choice);i++){
        json_object_array_add(json_menu_shuzhu,json_object_array_get_idx(cli_menu_choice,i));
    }
    buf_cli=json_object_to_json_string(json_menu_shuzhu);
    if(send(cli_fd2, buf_cli, strlen(buf_cli), 0) < 0){
        perror("send");
        exit(-1);
    }
    
    system("clear");
    printf("\n\n\n\t\t\t已向服务台提交菜单，片刻就好!\n");
    sleep(1);
    //释放json对象
    json_object_put(json_menu);
    json_object_put(json_menu_shuzhu);
}

void TO_server_order_23(int cli_fd2){
    //-----------------------------(1)发送订座信号
    //发送协议查询桌位情况
    static int i;
    struct json_object *json_menu;
    struct json_object *json_menu_shuzhu;
    json_menu=json_object_new_object();
    json_object_object_add(json_menu,"fla",json_object_new_int(23));
    
    //将命令12与选好的桌号发送给服务器
    //将cli_table_choice和json_table对象放进 json_table_shuzhu里
    json_menu_shuzhu=json_object_new_array();
    json_object_array_add(json_menu_shuzhu,json_menu);
    for(i=0;i<json_object_array_length(cli_add_menu);i++){
        json_object_array_add(json_menu_shuzhu,json_object_array_get_idx(cli_add_menu,i));
    }
    buf_cli=json_object_to_json_string(json_menu_shuzhu);
    if(send(cli_fd2, buf_cli, strlen(buf_cli), 0) < 0){
        perror("send");
        exit(-1);
    }
    
    system("clear");
    printf("\n\n\n\t\t\t已向服务台提交新增菜单，片刻就好!\n\n\n");
    sleep(1);
    //释放json对象
    json_object_put(json_menu);
    json_object_put(json_menu_shuzhu);
}

void TO_server_order_31(int cli_fd2){
    //发送协议查询桌位情况
    struct json_object *json_obj;
    struct json_object *json_shuzhu;

    json_obj=json_object_new_object();
    json_object_object_add(json_obj,"fla",json_object_new_int(31));

    json_shuzhu=json_object_new_array();
    json_object_array_add(json_shuzhu,json_obj);
    buf_cli=json_object_to_json_string(json_shuzhu); 
    send(cli_fd2, buf_cli, strlen(buf_cli), 0);

    system("clear");
    printf("\n\n\n\t\t已提交服务台，佳肴马上就好......\n\n\n");
    sleep(1);
    json_object_put(json_obj);
    json_object_put(json_shuzhu);

}
void TO_server_order_41(int cli_fd2){
    static int   i, all_prices=0, prices=0;

//1、获取总价
    //字符流解包成json对象
    json_object *jiebao_prices1,*jiebao_menu_bak;
    json_object *jiebao_cost_prices;
    jiebao_prices1 = json_object_new_object();
    
    //解包
    jiebao_menu_bak = json_tokener_parse(menu_bak);


    for(i=0; i<json_object_array_length(jiebao_menu_bak); i++){
        jiebao_prices1 = json_object_array_get_idx(jiebao_menu_bak,i);
        jiebao_cost_prices   = json_object_object_get(jiebao_prices1,"prices");      
                    prices   = json_object_get_int(jiebao_cost_prices);      
                all_prices   = all_prices+prices;
    }
//2、发送结账协议
    //发送协议查询桌位情况
    struct json_object *json_obj;
    struct json_object *json_shuzhu;
    struct json_object *json_prices;

    json_obj=json_object_new_object();
    json_prices=json_object_new_object();
    json_object_object_add(json_obj,"fla",json_object_new_int(41));
    json_object_object_add(json_prices,"prices",json_object_new_int(all_prices));

    json_shuzhu=json_object_new_array();
    json_object_array_add(json_shuzhu,json_obj);
    json_object_array_add(json_shuzhu,json_prices);
    buf_cli=json_object_to_json_string(json_shuzhu); 
    send(cli_fd2, buf_cli, strlen(buf_cli), 0);

    printf("\n\n\n\t\t已申请结账，服务员马上就到！\n\n\n");
    json_object_put(json_obj);
    json_object_put(json_shuzhu);
    json_object_put(json_prices);

}
void TO_server_order_51(int cli_fd2){
    //发送协议查询桌位情况
    struct json_object *json_obj;
    struct json_object *json_shuzhu;

    json_obj=json_object_new_object();
    json_object_object_add(json_obj,"fla",json_object_new_int(51));

    json_shuzhu=json_object_new_array();
    json_object_array_add(json_shuzhu,json_obj);
    buf_cli=json_object_to_json_string(json_shuzhu); 
    send(cli_fd2, buf_cli, strlen(buf_cli), 0);

    json_object_put(json_obj);
    json_object_put(json_shuzhu);

}

