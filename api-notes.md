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
- inet_ntop: 32bit  -> 电分str
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
sockfd: socket descriptor, 未连接sockfd -> 被动sockfd
backlog: 略大于 未完成连接队列(等待完成三路握手) + 已完成队列(已完成三路握手，等待accpet调用)
-> return: 0 or -1
*/
int listen(int sockfd, int backlog);
```
- accept
