----------------------1day001--------------------------
基本框架
select
内核链表

----------------------1day002-------------------------
编译方式：gcc -o server init.c server.c -lpthread
select开线程
线程打算用于工作人员或者厨师

---------------------2day001---------------------------
直接跳过了1day002的代码，从1day001修改
read后开线程：处理json，回馈给client
编译方式：gcc -o server init.c server.c -lpthread -ljson

---------------------2day002---------------------------
实现了json数组网络打包和解包
以后全部实现数组方式网络传输

---------------------2day003---------------------------
实现利用json与客户端通信
gcc -o server server.c init.c  -lpthread -ljson -lsqlite3

---------------------2day004---------------------------
初始化数据库，创建一个菜单表格
gcc -o server server.c init.c sqlite3.c -lpthread -ljson -lsqlite3

---------------------2day005---------------------------
gcc -o server server.c init.c sqlite3.c thread.c -lpthread -ljson -lsqlite3

问题：init_sql()函数新建的数据库，表格乱码。
解决办法：外部建立数据库。

---------------------2day006---------------------------
gcc -o server server.c init.c sqlite3.c thread.c table.c -lpthread -ljson -lsqlite3

问题：init_sql()函数新建的数据库，表格乱码。
解决办法：外部建立数据库,或者在良明原始的文件上改动，不把代码拷贝到自己新建里的文件里。

---------------------2day007---------------------------
gcc -o server server.c init.c sqlite3.c thread.c table.c -lpthread -ljson -lsqlite3
完成基本的几个命令：11 12 21 22 31
完成对以上命令进行数据库操作
添加了完整的调试信息，如果不需要调试信息，改变对DEBUG的宏定义

---------------------2day008---------------------------
gcc -o server server.c init.c sqlite3.c thread.c table.c -lpthread -ljson -lsqlite3
对没有加锁的数据库操作加锁
逻辑进度：接收客户的订单
问题 ：1.数据库中，客户表的座位ID不正确。2.没有进入厨房线程。
---------------------2day009---------------------------
gcc -o server server.c init.c sqlite3.c thread.c table.c work.c -lpthread -ljson -lsqlite3
解决问题，添加离线和付钱后的数据库处理
增加厨房线程，可以接收催单或者排队消息

---------------------2day010---------------------------
gcc -o server server.c init.c sqlite3.c thread.c work.c table.c -lpthread -ljson -lsqlite3

解决命令错误时，线程出错，程序退出的问题
修改add()函数功能
增加显示功能
问题：催单和money统计未实现正确功能
work显示优化

---------------------3day001---------------------------
实现创建线程后的同步问题，避免了当大量用户同时链接服务器时的socket文件描述符和读取内存错误的现象发生。
用户数据表名custname的空间拓展到张30,可以容下20位整数的客户id
可以完全删除离开的客户的就餐表
问题统计问题出现在客户端发送的协议不正确，已经解决问题


