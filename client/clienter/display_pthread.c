/*************************************************************************
> File Name: display.c
> Author: 
> Mail: 
> Created Time: 2015年03月17日 星期二 18时35分28秒
************************************************************************/
#include "head.h"

/*--------------------------(1)欢迎界面----------------------------------*/
void  hello_display(){
    system("clear");
    printf("       ***********************************************************\n");
    printf("       *                 欢迎光临 · 霸王餐                       *\n");
    printf("       *                                                         *\n");
    printf("       *                                                         *\n");
    printf("       *               用餐时间段： 早上8:00--凌晨               *\n");
    printf("       *    ————                                                 *\n");
    printf("       *  | 霸王 |    (1)确保点餐客户就席十分钟饭菜上桌          *\n");
    printf("       *  | 条款 |    (2)不采用赊账制度，现金、刷卡、支付宝      *\n");
    printf("       *    ————                                                 *\n");
    printf("       *                                                         *\n");
    printf("       *       打个小广告：本店《龙凤双脚》什么的最好吃了        *\n");
    printf("       ***********************************************************\n");
    sleep(2);
 
}

//-----------------------------显示桌位并选座函数------------------------------------
void table_display(char table_buf[]){
    static int i, j, table_flag1 = 0;
    const char *table_id1_str, *table_varities_str, *table_site_str, *table_condition_str;

    //字符流解包成json对象
    json_object *jiebao_table1, *jiebao_table_all;
    json_object *jiebao_table_id1, *jiebao_table_varities, *jiebao_table_site, *jiebao_table_condition;

    jiebao_table_all=json_tokener_parse(table_buf);

    //显示桌位
    system("clear");
    printf("       |---------------------------------------------------------|\n");
    printf("       |                  不为别的，我只为嘴强王者               |\n");
    printf("       |                       嘴·强·王·座                       |\n");

    for(i=0; i<json_object_array_length(jiebao_table_all);i++){
        jiebao_table1 = json_object_array_get_idx(jiebao_table_all,i);

        jiebao_table_id1 = json_object_object_get(jiebao_table1,"id1");      
        jiebao_table_varities = json_object_object_get(jiebao_table1,"varities");      
        jiebao_table_site = json_object_object_get(jiebao_table1,"site");      
        jiebao_table_condition = json_object_object_get(jiebao_table1,"condition");      

        table_id1_str=json_object_get_string(jiebao_table_id1);
        table_varities_str=json_object_get_string(jiebao_table_varities);
        table_site_str=json_object_get_string(jiebao_table_site);
        table_condition_str=json_object_get_string(jiebao_table_condition);

        if(!strcmp(table_condition_str,"0")){
            printf("       |          ID:%2s\t\t%s\t\t%s             |\n",table_id1_str,table_varities_str,table_site_str);
           table_flag1 = 1;
        }
    }
    printf("       |---------------------------------------------------------|\n");

    //选座部分
    //cli_table_choice保存选择好的桌位包
    if(table_flag1 == 0){
        printf("\n\n\n                 对不起，暂时满座！\n");
        exit(0);
    }
    while(table_flag1){
        printf("\n\n请选择桌位ID：\n");
        
        scanf("%d",&j);
        getchar();             //清除回车键
        if(IS_table_condition_0(j, jiebao_table_all) == 1){
            cli_table_choice = json_object_array_get_idx(jiebao_table_all, j-1);
            break;
        }else{
            printf("                  已被预定，请再选佳座！\n");
        }
    } 
}

//-------------------------------------------判断桌位是否为空
int IS_table_condition_0(int j, json_object *jiebao_table_all){
    const char *IS_table_condition_num;

    //字符流解包成json对象
    json_object *IS_table, *is_table_condition;

    IS_table = json_object_array_get_idx(jiebao_table_all,j-1);
    is_table_condition = json_object_object_get(IS_table,"condition");      
    IS_table_condition_num=json_object_get_string(is_table_condition);

    if(!strcmp(IS_table_condition_num , "0")){
        return 1;
    }else  
        return 0;
}

//-----------------------------显示主菜单函数------------------------------------
void menu_display(char menu_buf[]){
    static int i;
    const char *menu_id1_str, *menu_foodname_str, *menu_prices_str;

    //字符流解包成json对象
    json_object *jiebao_menu1, *jiebao_menu_all;
    json_object *jiebao_menu_id1, *jiebao_menu_foodname, *jiebao_menu_prices;

    jiebao_menu_all=json_tokener_parse(menu_buf);

    //显示菜单
    system("clear");
    printf("       |---------------------------------------------------------|\n");
    printf("       |                       嘴·强·菜·谱                       |\n");

    for(i=0; i<json_object_array_length(jiebao_menu_all);i++){
        jiebao_menu1 = json_object_array_get_idx(jiebao_menu_all,i);

        jiebao_menu_id1      = json_object_object_get(jiebao_menu1,"id1");      
        jiebao_menu_foodname = json_object_object_get(jiebao_menu1,"foodname");      
        jiebao_menu_prices   = json_object_object_get(jiebao_menu1,"prices");      

        menu_id1_str      =  json_object_get_string(jiebao_menu_id1);
        menu_foodname_str =  json_object_get_string(jiebao_menu_foodname);
        menu_prices_str   =  json_object_get_string(jiebao_menu_prices);

        printf("       |          ID:%-8s\t%-15s\t%-8s         |\n",menu_id1_str,menu_foodname_str,menu_prices_str);
    }
    printf("       |---------------------------------------------------------|\n");
    
    //点菜部分
    //cli_menu_choice保存选择好的菜单
    int menu_id;
    json_object *menu;
    struct json_object* json_menu_new;

    json_menu_new    = json_object_new_object();
    cli_menu_choice  = json_object_new_array();

    printf("       |     请输入一个ID后“回车”，输入  9999  提交点菜名单      |\n");
    printf("       |---------------------------------------------------------|\n");
    scanf("%d", &menu_id);
    while(menu_id != 9999){   
        if(IS_menu_ID(menu_id,menu_buf) && (menu_id > 0)){
            json_menu_new = json_object_array_get_idx(jiebao_menu_all ,menu_id-1);
            json_object_array_add(cli_menu_choice,json_menu_new);
        
            menu=json_object_object_get(json_menu_new,"foodname");
            printf("已点菜： %s \n",json_object_to_json_string(menu));
            scanf("%d", &menu_id);
            getchar();
        }else{
            printf("\t\t亲，新菜即将推出！\n");
            printf("重新输入ID：\n");
            scanf("%d",&menu_id);
            getchar();
            
        }
    }
    
    menu_bak = json_object_get_string(cli_menu_choice);
system("clear");
    printf("       |---------------------------------------------------------|\n");
    printf("       |                 正在提交菜单......                      |\n");
    printf("       |---------------------------------------------------------|\n");

    sleep(1);
}

//-------------------------------------------判断是否有菜
int IS_menu_ID(int j_menu,char menu_buf_id[]){
    //字符流解包成json对象
    json_object *is_menu_all, *is_menu_obj;

    is_menu_all = json_tokener_parse(menu_buf_id);
    is_menu_obj = json_object_array_get_idx(is_menu_all, j_menu-1);

    if(is_menu_obj != NULL){
        return 1;
    }else  
        return 0;
}

//-----------------------------显示订座成功信息函数------------------------------------
void table_OK_display(){
    //显示菜单
    system("clear");
    printf("       |---------------------------------------------------------|\n");
    printf("       |                  不为别的，我只为嘴强王者               |\n");
    printf("       |                                                         |\n");
    printf("       |                                                         |\n");
    printf("       |                                                         |\n");
    printf("       |                                                         |\n");
    printf("       |                    欢迎入座：订座成功                   |\n");
    printf("       |                                                         |\n");
    printf("       |                                                         |\n");
    printf("       |                                                         |\n");
    printf("       |                                                         |\n");
    printf("       |                                                         |\n");
    printf("       |                                                         |\n");
    printf("       |---------------------------------------------------------|\n");
    sleep(1);
}

void reminder_display(){
    system("clear");
    static int i_r, j_r=1; 
    printf("                                                             \n");
    printf("                                                             \n");
    printf("                               敬请用餐                      \n");
    printf("                                                             \n");
    printf("                               功能服务                      \n");
    printf("                                                             \n");
    printf("               1、催单          2、加菜        3、结账       \n");
    printf("                                                             \n");
    printf("                                                             \n");
sleep(1);
    while(j_r){
        scanf("%d",&i_r);
        getchar();
        switch(i_r){
            printf("wo jiao switch\n");
            case 1:{                          //进入发送线程 --催单（31）
                j_r=0; i_r=0;
                send_server_num = 31;
                flag  = 0;
                break;
            }
            case 2:{                          //进入接收线程 --加菜（也叫点菜）
                j_r=0; i_r=0;
                recv_server_num = 23;
                flag = 1;
                    break;
                   }
            case 3:{
                j_r=0; i_r=0;
                recv_server_num = 41;         //进入接收线程 --结账
                flag = 1;
                break;
            }
        }
    }
 j_r=1;
}
//-----------------------------结账函数------------------------------------
void cost_display(){
    static int   i;
    const  char  *cost_foodname_str;
    static int   cost, all_cost=0;

    //字符流解包成json对象
    json_object *jiebao_cost1,*jiebao_menu_bak;
    json_object *jiebao_cost_foodname, *jiebao_cost_prices;
    jiebao_cost1 = json_object_new_object();
    
    //解包
    jiebao_menu_bak = json_tokener_parse(menu_bak);

    //显示菜单
    system("clear");
    printf("       |---------------------------------------------------------|\n");
    printf("       |                  你确定你不是来吃霸王餐？？？           |\n");
    printf("       |                                                         |\n");

    for(i=0; i<json_object_array_length(jiebao_menu_bak); i++){
        jiebao_cost1 = json_object_array_get_idx(jiebao_menu_bak,i);
        jiebao_cost_foodname = json_object_object_get(jiebao_cost1,"foodname");      
        jiebao_cost_prices   = json_object_object_get(jiebao_cost1,"prices");      
                      cost   = json_object_get_int(jiebao_cost_prices);      
                  all_cost   = all_cost+cost;
           cost_foodname_str =  json_object_get_string(jiebao_cost_foodname);
        
    printf("       |          菜名  :%-15s\t     ￥：%-8d        |\n",cost_foodname_str, cost);
    }
    printf("       |          总价  :%-8d RMB                            |\n",all_cost);
    printf("       |---------------------------------------------------------|\n\n\n");
   // sleep(3);
}


void good_bye_display(){
    system("clear");
    printf("       |---------------------------------------------------------|\n");
    printf("       |                                                         |\n");
    printf("       |                     欢迎下次光临！                      |\n");
    printf("       |                                                         |\n");
    printf("       |---------------------------------------------------------|\n");

}

void add_menu_display(char add_menu_buf[]){
    static int i_menu;
    const char *add_menu_id1_str, *add_menu_foodname_str, *add_menu_prices_str;

    //定义json对象
    json_object *jiebao_add_menu1, *jiebao_add_menu_all;
    json_object *jiebao_add_menu_id1, *jiebao_add_menu_foodname, *jiebao_add_menu_prices;

    jiebao_add_menu_all=json_tokener_parse(add_menu_buf);

    //显示菜单
    system("clear");
    printf("       |---------------------------------------------------------|\n");
    printf("       |                    胃口好才是真的好                     |\n");

    for(i_menu= 0; i_menu<json_object_array_length(jiebao_add_menu_all); i_menu++){
        jiebao_add_menu1 = json_object_array_get_idx(jiebao_add_menu_all,i_menu);

        jiebao_add_menu_id1      = json_object_object_get(jiebao_add_menu1,"id1");      
        jiebao_add_menu_foodname = json_object_object_get(jiebao_add_menu1,"foodname");      
        jiebao_add_menu_prices   = json_object_object_get(jiebao_add_menu1,"prices");      

        add_menu_id1_str      =  json_object_get_string(jiebao_add_menu_id1);
        add_menu_foodname_str =  json_object_get_string(jiebao_add_menu_foodname);
        add_menu_prices_str   =  json_object_get_string(jiebao_add_menu_prices);

        printf("       |       ID:%-8s\t%-15s\t%-8s         |\n",add_menu_id1_str, add_menu_foodname_str,add_menu_prices_str);
    }
    printf("       |---------------------------------------------------------|\n");
    
    //加菜部分
    //cli_add_menu 保存增加的菜单
    int add_menu_id;
    json_object *add_menu;
    struct json_object* json_add_menu_new;

    json_add_menu_new    = json_object_new_object();
    cli_add_menu         = json_object_new_array();

    printf("       |     请输入一个ID后“回车”，输入  9999  提交加菜名单      |\n");
    printf("       |---------------------------------------------------------|\n");
    scanf("%d", &add_menu_id);
    while(add_menu_id != 9999){   
        if(IS_menu_ID(add_menu_id,add_menu_buf) && (add_menu_id > 0)){
            json_add_menu_new = json_object_array_get_idx(jiebao_add_menu_all ,add_menu_id-1);
            json_object_array_add(cli_add_menu,json_add_menu_new);
        
            add_menu=json_object_object_get(json_add_menu_new,"foodname");
            printf("已新加菜单： %s \n",json_object_to_json_string(add_menu));
            scanf("%d", &add_menu_id);
            getchar();
        }else{
            printf("\t\t亲，新菜即将推出！\n");
            printf("重新输入ID：\n");
            scanf("%d",&add_menu_id);
            getchar();
            
        }
    }
    
//将新增菜单加入用户菜单
    static int i_add;
    json_object *jiebao_new_menu1, *jiebao_menu_all_old;
    //(1)
    jiebao_new_menu1  = json_object_new_object();
    jiebao_menu_all_old=json_tokener_parse(menu_bak);    //之前选好的菜单
    //(2)
    //将新增的菜单放进jiebao_menu_all_old json数组
    for(i_add= 0; i_add<json_object_array_length(cli_add_menu); i_add++){
        jiebao_new_menu1 = json_object_array_get_idx(cli_add_menu,i_add);
        json_object_array_add(jiebao_menu_all_old,jiebao_new_menu1);
    }
    //(3)

    menu_bak = json_object_get_string(jiebao_menu_all_old);
    

    system("clear");
    printf("       |---------------------------------------------------------|\n");
    printf("       |                 正在提交菜单......                      |\n");
    printf("       |---------------------------------------------------------|\n");

    sleep(1);
}

/*--------------------------(2)接收数据线程调用函数--------------------------------*/
void *recv_from_server(void* arg1){
    int cli_fd1;
    cli_fd1 = *((int *)arg1);

    while(1){
        if(flag== 1){
            switch(recv_server_num){
                case 11:{                            
                    bzero(buf,sizeof(buf));
                    recv(cli_fd1, buf, sizeof(buf), 0);
                    table_display(buf);              //显示桌位、选座
                    send_server_num=12;              //进入发送端发送选座数据包
                    flag =0;break;                   //跳转发送数据端
                }
                case 12:{
                    table_OK_display();              //显示订座成功信息
                    send_server_num =21;             //进入发送端发送21命令
                    flag=0;
                    break;                  
                }
                case 21:{
                    bzero(buf,sizeof(buf));
                    recv(cli_fd1, buf, sizeof(buf), 0);
                    menu_display(buf);               //显示菜单信息
                    send_server_num =22;             //进入菜单数据包
                    flag =0;
                    break;
                }
                case 22:{
                    reminder_display();              //催单、加菜、结账界面
                    break;
                }
                case 23:{

                    add_menu_display(buf);          //加菜界面
                    send_server_num=23;
                    flag = 0;
                    break;
                }
                case 41:{
                    cost_display();              //结账界面
                    send_server_num = 41;
                    flag = 0;
                    break; 
                }
            }
        }
    }
    return NULL;
}

/*--------------------------(3)发送数据线程调用函数--------------------------------*/
void *send_to_server(void *arg2){
    int cli_fd2;
    cli_fd2 = *((int *)arg2);
    send_server_num = 11;
    while(1){   
        while(flag == 0){
            switch(send_server_num){
                case 11:{                          //发送 桌位--查询(信号)      
                    TO_server_order_11(cli_fd2); 
                    recv_server_num = 11;  
                    flag=1;break;
                }
                case 12:{                          //发送 桌位--订座(信号)
                    TO_server_order_12(cli_fd2);
                    recv_server_num = 12;
                    flag=1;break; 
                }
                case 21:{
                    TO_server_order_21(cli_fd2);   //发送 菜谱--查询(信号)
                    recv_server_num = 21;
                    flag=1;
                    break;
                }
                
                case 22:{                   
                    TO_server_order_22(cli_fd2);   //发送 菜谱--下单(信号)
                    recv_server_num = 22;
                    flag=1;break;
                }
                case 23:{                   
                    TO_server_order_23(cli_fd2);   //发送 菜谱--加菜(信号)
                    recv_server_num = 22;
                    flag=1;break;
                }
                
                case 31:{
                    TO_server_order_31(cli_fd2);   //催单（信号）
                    recv_server_num = 22;
                    flag=1;break;
                }
                case 41:{
                    TO_server_order_41(cli_fd2);   //结账 （信号）
                    sleep(1);
                    send_server_num = 51;
                    flag = 0;break;
                }
                case 51:{
                    sleep(0.5);
                    TO_server_order_51(cli_fd2);   //退出 （信号）
                    sleep(3);
                    good_bye_display();
                    
                    exit(0);
                }
            }
        }
    }
    return NULL;
}

 
