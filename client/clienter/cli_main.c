/*************************************************************************
> File Name: 点菜系统主函数main
> Author: 梁惠涌
> Mail: 
> Created Time: 2015年03月17日 星期二 15时51分18秒
************************************************************************/

#include "head.h"

int main(int argc, char *argv[]){

    int cli_fd;                              //socket返回值
    struct sockaddr_in servaddr;
    cli_menu_choice  = json_object_new_array();
    
    if( argc != 2 ){
        printf("\t usage: %s <server_IP>\n", argv[0]);
        exit(-1);
    }

    //创建套接字
    if((cli_fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
        perror("socket");
        exit(-1);
    }

    //填充IP和端口号
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    //调用connect函数，与服务器连接
    if(connect(cli_fd,(struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ){
        printf("连接失败！\n");
        exit(-1);
    }

/*--------------------(1)欢迎界面4秒显示------------------*/
    hello_display();

/*--------------------(2)创建线程1-------------------------*/
    static pthread_t thread_tid1, thread_tid2;              //定义线程标识符
    
    //创建线程接收服务器数据并处理
    if(pthread_create(&thread_tid1, NULL, recv_from_server, (void *)&cli_fd) < 0){
        perror("pthread_tid1");
        exit(-1);
 }
   
/*--------------------(3)创建线程2-------------------------*/
   //创建线程发送数据到服务器并处理
    if(pthread_create(&thread_tid2, NULL, send_to_server, (void *)&cli_fd)  < 0){
        perror("pthread_tid2");
        exit(-1);
    }
   
    pthread_join(thread_tid1, NULL);
    pthread_join(thread_tid2, NULL);

    return 0;
}

