1. 守护进程(daemon): 指在后台运行且不与任何控制终端关联的进程
    - 启动方法：
        1. 在系统启动阶段，许多守护进程由系统初始化脚本启动
        2. 许多网络服务器由inetd超级服务启动
        3. cron守护进程启动
        4. at命令用于指定将来某个时刻的程序执行
        5. 从用户终端或在前台或后台启动

2. syslogd守护进程： 启动一些脚本接收守护进程的消息日志
3. syslog: 守护进程通过调用登记日志消息记录
    ```c
    #include <syslog.h>
    void syslog(int priority, const char *message, ... );
    ```
4. daemon_init: 把一个普通进程转变为守护进程(重要)
5. inetd守护进程：管理众多的守护进程服务器(server)（例如FTP,Telnet等）
    - 通过由inetd处理普通守护进程的大部分启动细节以简化守护进程的编写。这么一来
    每个服务器就不再有调用daemon_init的必要了
    - 单个进程(inetd)就能为多个服务等待外来的客户请求，以此取代每个服务一个进程的做法
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190126-095511@2x.png)
6. daemon_initd: 为错误处理函数设置daemon_proc标志，以及调用openlog
