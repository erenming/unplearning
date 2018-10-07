- IPv4结构
```c
struct in_addr {
    in_addr_t s_addr; // 32位IPv4地址，uint32_t(32位无符号整数)
                      // network byte ordered
};

struct sockaddr_in {
    uint8_t        sin_len; // 结构长度
    sa_family_t    sin_family; // AF_INET
    in_port_t      sin_port; // 16-bit TCP or UDP port number
    struct in_addr sin_addr; // 32-bit IPv4 address
                             // network byte ordered
    char           sin_zero[8]; // unused
};
```
- inet_pton: 点分str -> 32bit
- inet_ntop: 32bit  -> 点分str
- readn, writen readline: 循环读取字节流、循环写入字节流
- socket:
```c
/*
family: 协议族，常数。eg, AF_INET
type: 套接字类型，常数。eg, SOCK_STREAM 
protocol: 协议类型, 常数。eg, 0(由系统根据family, type的组合分配))
-> return: sockfd(socket descriptor)
*/
int socket(int family, int type, int protocol);
```
- connect: TCP客户用来建立与TCP服务器的连接
```c
/*
sockfd: socket descriptor
sockaddr: 套接字结构的指针
addrlen: 结构大小
-> return: 0(success) or -1(error)
*/
int connect(int sockfd, const struct sockaddr *servadd, socklen_t addrlen);
```
- bind: 把一个本地协议地址赋予给一个套接字
    1. 绑定端口, cli选择临时端口, srv必须指定端口
    2. 绑定ip, cli相当于给将发送的IP数据报指定了源IP, srv相当于只接收目的地为绑定IP的客户连接
```c
/*
sockfd: socket descriptor
myaddr: 特定于协议的地址结构的指针
addrlen: 地址结构的长度
-> return: 0 or -1
*/
int bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
```
- listen: 
```c
/*
sockfd: socket descriptor, 未连接sockfd -> 被动sockfd(指示内核应该接收指向该套接字的连接请求)
backlog: 略大于 未完成连接队列(等待完成三路握手) + 已完成队列(已完成三路握手，等待accpet调用)
-> return: 0 or -1
*/
int listen(int sockfd, int backlog);
```
- accept: TCP服务器调用，从已完成连接队列头返回下一个已完成连接
```c
/*
sockfd: 监听套接字描述符
cliaddr: 客户的套接字地址
addrlen: value: cliaddr所指的套接字地址结构的长度， result: 内核存放该套接字地址结构的确切字节数
-> return: 非负描述符 or -1
*/
int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
```
- fork: 派生新的进程， 一次调用两次返回
    1. 父进程中返回子进程的ID号
    2. 子进程中返回0, 可通过getppid回去父进程ID
    3. 两种典型用法:
        - 并发，创建副本，每个副本与其他副本同时处理各自的某个操作
        - 进程执行另一个程序，创建副本后，调用exec系列函数将当前进程替换成新的程序
```c
pid_t fork(void);
```
- exec: 让存放在硬盘上的可执行程序文件被Unix执行
- close: 把套接字标记为已关闭，描述符引用计数减一。而TCP会尝试发送已排队的等待发送到对端的任何数据，然后才是正常的TCP的FIN分节
- getsockname: 获取与某个套接字关联的本地协议地址
```c
int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);
```
- getpeername: 获取与某个套接字关联的外地(客户)协议地址
```c
int getpeername(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen);
```
- wait, waitpid: 处理已终止的子进程
```c
/*
pid: 要等待的进程ID, -1代表等待第一个终止的子进程
statloc: 子进程的终止状态的指针
options: 附加选项，WNOHANG用以告知内核没有已终止子进程时不要阻塞
*/
pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *statloc, int options);
```
