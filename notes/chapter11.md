1. DNS(Domain Name System, DNS): 主要用于主机名字与IP地址之间的映射
2. 资源记录(RR): 
    - A: 把一个主机名映射成一个32位的IPv4地址
    - AAAA: 把一个主机名映射成一个128位的IPv6地址
    - PTR: 指针记录(PTR), 把IP地址映射成主机名
    - CNAME: 规范名字(canonial name), 为常见的服务（例如ftp和www）指派CNAME记录
3. 解析器与名字解析器
    - 名字服务器（name server）
    - 解析器(resolver)：用以调用DNS服务器
    - 关系图：
        ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190114-231029@2x.png)
4. DNS替代方法：静态主机文件(例如/etc/hosts)，网络信息系统以及轻权目录访问协议（Lightweight Directory Access Protocol, LDAP）
5. gethostbyname: 根据名字获取IP地址
    ```c
    #include <netdb.h>
    struct hostent *gethostbyname (const char *hostname);

    // Returns: non-null pointer if OK,NULL on error with h_errno set
    ```
6. gethostbyaddr: 根据IP地址获取名字
    ```c
    #include <netdb.h>
    struct hostent *gethostbyaddr (const char *addr, socklen_t len, int family);

    // Returns: non-null pointer if OK, NULL on error with h_errno set
    ```
7. getservbyname: 根据名字获取服务
    ```c
    #include <netdb.h>
    struct servent *getservbyname (const char *servname, const char *protoname);
    // Returns: non-null pointer if OK, NULL on error

    struct servent {
        char *s_name; /* official service name */
        char **s_aliases; /* alias list */
        int s-port; /* port number, network-byte order */ char *s_proto; /* protocol to use */
    };
    ```
8. gerservbyport: 根据给定端口号和可选协议查找相应服务
    ```c
    #include <netdb.h>
    struct servent *getservbyport (int port, const char *protoname);
    // Returns: non-null pointer if OK, NULL on error
    ```
9. getaddrinfo: 处理名字到地址以及服务到端口两种转换，返回的是一个sockaddr结构(sockaddr结构可由套接字函数直接使用)
    ```c
    #include <netdb.h>
    int getaddrinfo (const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result);
    // Returns: 0 if OK, nonzero on error

    struct addrinfo {
        int ai_flags;   /* AI_PASSIVE, AI_CANONNAME */
        int ai_family;   /* AF_xxx */
        int ai_socktype;   /* SOCK_xxx */
        int ai_protocol;   /* 0 or IPPROTO_xxx for IPv4 and IPv6 */
        socklen_t ai_addrlen;    /* length of ai_addr */
        char *ai_canonname;    /* ptr to canonical name for host */
        struct sockaddr *ai_addr;   /* ptr to socket address structure */
        struct addrinfo *ai_next; /* ptr to next structure in linked list */
    };
    ```
10. 可重入(Reentrancy): In computing, a computer program or subroutine is called reentrant if it can be interrupted     in the middle of its execution and then safely be called again ("re-entered") before its previous invocations      complete execution.
11. 总结：
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190116-224623@2x.png)

