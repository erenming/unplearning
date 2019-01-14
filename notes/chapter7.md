1. getsocketopt 和 setsocketopt 函数： 用于获取与设置影响套接字的选项
2. 通用套接字选项：
    - SO_BROADCAST: 开启或禁止进程发送广播消息的能力
    - SO_DEBUG: 开启时，内核将为TCP在该套接字发送和接受的所有分组保留详细跟踪信息
    - SO_DONTROUTE: 外出的分组将绕过底层协议的正常路由机制
    - SO_ERROR: socket发生错误时，so_error被设置，称为待处理错误(pending error)
    - SO_KEEPLIVE: 设置后，若2小时内在该套接字的任一方向上都没有数据交换，TCP就会给对端发送一个保持存活探测分节(keep-alive probe)
        1. 对端以ACK响应
        2. 对端以RST响应，告知本TCP：对端已崩溃且已重新启动
        3. 对端没有响应。TCP另外发送8个分节，试图得到响应（另一种，超时后发送第二个探测分节，超时值加倍）
    - SO_LINGER：用于指定close函数对面向连接的协议要如何操作。默认是close立即返回，但如果有数据残留在套接字发送缓冲区中，系统
        将试着把这些数据发送给对端
    - SO_RCVBUF：设置接收缓冲区的大小
    - SO_SNDBUF：设置发送缓冲区的大小
    - SO_RCVLOWAT: 设置接收低水位，让select返回“可读”时套接字接受缓冲区中所需要的数据量
    - SO_SNDLOWAT: 设置发送低水位，让select返回“可写”时套接字接受缓冲区中所需要的数据量
    - SO_REUSEADDR和SO_REUSEPORT:
        1. SO_REUSEADDR允许启动一个监听服务器并捆绑其众所周知的端口，即使以前建立的将该端口用作它们的本地端口的连接仍存在
        2. SO_REUSEADDR允许在同一个端口上启动同一服务器的多个实例，只要每个实例捆绑一个不同的本地IP地址即可
        3. SO_REUSEADDR允许单个进程捆绑同一端口到多个套接字上，只要每次捆绑指定不同的本地IP即可
        4. SO_REUSEADDR允许完全重复的捆绑，当一个IP和端口已绑定到某个套接字上时，如果传输协议支持，同样的IP和端口还可以绑定到
            另一个套接字上（一般只支持UDP）
