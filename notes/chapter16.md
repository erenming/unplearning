1. 可能阻塞的套接字：
    - 输入操作
    - 输出操作
    - 接受外来连接
    - 发出外出连接
2. 非阻塞读写
3. 非阻塞connect: When a TCP socket is set to nonblocking and then connect is called, connect returns immediately   with an error of EINPROGRESS but the TCP three-way handshake continues. We then check for either a successful or unsuccessful completion of the connection's establishment using select.
4. 非阻塞connect用途：
    - 在3路握手期间处理其他工作
    - 可建立多个连接
    - 既然使用select等待连接的建立，我们可以给select指定一个时间限制，使得我们能够缩短connect的超时时间(
        存在调用select之前有可能连接已经建立并有来自对端的数据到达
    )
5. 非阻塞accept：
    - 缺陷：存在建立连接后，服务端来不及处理accept，而此时收到了一个RST, 从而导致阻塞的问题
    - 解决方案：
        1. 当使用select获悉某个监听套接字上有已完成连接准备好被accept时，总是把监听套接字设置为非阻塞
        2. 在后续的accept调用中忽略一下错误: EWOULDBLOCK, ECONNABORTED, EPROTO, EINTR
