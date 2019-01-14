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
5. gethostbyname:
    ```c
    #include <netdb.h>
    struct hostent *gethostbyname (const char *hostname);

    // Returns: non-null pointer if OK,NULL on error with h_errno set
    ```
    