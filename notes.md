1. Unix errno值:
    - 只要一个unix函数中有错误发生，全局变量errno就会被设置为一个指明该错误类型的正值，函数本身则通常返回-1
2. POSIX: 
    - Portable Operating System Interface,是由IEEE开发的一系列标准，是涵盖了大量c语言编程接口的规范
3. 端口号:
    - 0~1023: IANA控制并分配
    - 1024~49151: IANA已登记端口
    - 49152~65535: 私用端口
3. 并发情况: 通过对来自客户端ip:port, fork子进程，形成已连接套接字
    - 监听套接字: `{*:80, *:*}`
    - 已连接套接字: `{*:80, cli_ip:cli_port1}`, `{*:80, cli_ip:cli_port2}`
4. socket pair: 套接字对，四元组，`(local ip, local tcp port, remote ip, remote tcp port)`
5. socket: 套接字，二元组`(ip, port)`