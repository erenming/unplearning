
- I/O复用(I/O multiplexing)：一种预先告知内核的能力，它使得内核一旦发现进程指定的一个或多个I/O条件就绪(也就是说输入已准备好被读取，或者描述符已能承受更多的输出)，就通知进程。

- 一个输入操作包括以下两步：
    1. 等待数据准备好(常涉及等待数据从网络中到达，当分组到达时，它就被复制到内核的缓存区)
    2. 从内核向进程复制数据(copy this data from kernel's buffer into our application buffer)
- 阻塞式I/O模型:

![](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20181220-140649@2x.png)

- 非阻塞式I/O模型:
    1. When an application sits in a loop calling recvfrom on a nonblocking descriptor like this, it is called polling
    2. The application is continually polling the kernel to see if some operation is ready

![](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20181220-142205@2x.png)

- I/O复用模型：
    1. we call select or poll and block in one of these two system calls, instead of blocking in the actual I/O system call

![](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20181220-142824@2x.png)


- 信号驱动式I/O模型：
    1. We can also use signals, telling the kernel to notify us with the SIGIO signal when the descriptor is ready

![](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20181220-143455@2x.png)

- 异步I/O模型：
    1. In general, these functions work by telling the kernel to start the operation and to notify us when the entire operation (including the copy of the data from the kernel to our buffer) is complete

![](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20181220-144754@2x.png)


- 模型比较:

    1. 同步I/O操作(synchronous I/O operation): causes the requesting process to be blocked until that I/O operation completes
    2. 异步I/O操作(asynchronous I/O operation): does not cause the requesting process to be blocked.
    3. 前四种均为同步I/O模型，只有异步I/O模型才是异步I/O模型

![](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20181220-145153@2x.png)

---

- select: 允许进程指示内核等待多个事件中的一个发生，并且只有在一个或多个事件发生或经历了一段指定的时间后才唤醒该进程

    ```c
    #include <sys/select.h>
    #include <sys/time.h>

    int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout);

    Returns: positive count of ready descriptors, 0 on timeout, –1 on error
    ```

    1. 参数说明
        -  `timeval`: tells the kernel how long to wait for one of the specified descriptors to become ready
            1. Wait forever： set as a null pointer
            2. Wait up to a fixed amount of time
            3. Do not wait at all: set to 0
        - `readset`, `writeset`, and `exceptset`, specify the descriptors that we want the kernel to test for reading, writing, and exception conditions.
        - fd_set 结构: 描述符集，通常为一个整数数组，其中每个整数中的每一位对应一个描述符。例如32位整数，第一个元素对应于描述符0~31
            ```c
            fd_set rset;
            FD_ZERO(&rset);   /* initialize the set: all bits off */
            FD_SET(1, &rset); /* turn on bit for fd 1 */
            FD_SET(4, &rset); /* turn on bit for fd 4 */
            FD_SET(5, &rset); /* turn on bit for fd 5 */
            ```
        - maxfdp1: 指定待测试的描述符个数，通常为待测的最大描述符+1
    2. 描述符就绪条件
        - A socket is ready for reading：
            1. The number of bytes of data in the socket receive buffer is greater than or equal to the current size of the low-water mark for the socket receive buffer.
            2. The read half of the connection is closed(i.e.,a TCP connection that has received a FIN).
            3. The socket is a listening socket and the number of completed connections is nonzero.
            4. A socket error is pending
        - A socket is ready for writing：
            1. The number of bytes of available space in the socket send buffer is greater than or equal to the current size of the low-water mark for the socket send buffer and either: (i) the socket is connected, or (ii) the socket does not require a connection (e.g., UDP).
            2. The write half of the connection is closed.
            3. A socket using a non-blocking connect has completed the connection, or the connect has failed.
            4. A socket error is pending.
        - 接受和发送低水位标记的目的： give the application control over how much data must be available for reading or how much space must be available for writing before select returns a readable or writable status
        - 总结：
            ![1](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20181221-103415@2x.png)
    3. 缺点
        - 每次调用select，都需要把fd集合从用户态拷贝到内核态，这个开销在fd很多时会很大
        - 同时每次调用select都需要在内核遍历传递进来的所有fd，这个开销在fd很多时也很大
        - select支持的文件描述符数量太小了，默认是1024
- shutdown: 在应用中，发送给对端一个FIN，告诉它我们已经完成了数据发送，但是仍然保持套接字描述符打开以便读取
    ```c
    #include <sys/socket.h>
    int shutdown(int sockfd, int howto);

    Returns: 0 if OK, –1 on error
    ```
    1. TCP Half-Close: TCP provides the ability for one end of a connection to terminate its output, while still receiving data from the other end. This is called a half-close.
    2. 参数说明：
        - howto:
            1. SHUT_RD: The read half of the connection is closed
            2. SHUT_WR: The write half of the connection is closed
            3. SHUT_RDWR: The read half and the write half of the connection are both closed, This is equivalent to calling shutdown twice

- 拒绝服务型攻击：当一个服务器在处理多个客户时，绝对不能阻塞于只于单个客户相关的某个函数调用。否则可能导致服务器被挂起，
                拒绝为所有其他客户提供服务。

- epoll:  解决了select的三个缺点
    1. `int epoll_create1(int flags);`: 创建epoll实例
        ![1](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190301-092941@2x.png)
        - flags
            1. 0
            2. EPOLL_CLOEXEC：any child process forked by the current process will close the epoll descriptor before it execs, so the child process won’t have access to the epoll instance anymore.
    2. `int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);`: add file descriptors it wants monitored to the epoll instance
        ![1](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190301-094103@2x.png)
        - interest list: All the file descriptors registered with an epoll instance
        - ready list: any of the file descriptors registered become ready for I/O
        - epfd: the file descriptor returned by epoll_create which identifies the epoll instance in the kernel.
        - fd: is the file descriptor we want to add to the epoll list/interest list.
        - op: refers to the operation to be performed on the file descriptor fd. In general, three operations are supported:
        - event: a pointer to a structure called epoll_event which stores the event we actually want to monitor fd for。例如EPOLLIN事件，代表socker buffer中有数据到达
    3. `epoll_wait`: A thread can be notified of events that happened on the epoll set/interest set of an epoll instance by calling the epoll_wait system call, which blocks until any of the descriptors being monitored becomes ready for I/O.
    4. Why is faster than select/poll
        - select/poll 是O(N), 当N很大时(比如web场景下，成千上万的连接)，耗时自然大
        - epoll只关心`ready list`，当I/O事件准备好时，内核只需将`ready list`里的返回给用户进程
    5. 性能总结：The cost of epoll is O(number of events that have occurred) and not O(number of descriptors being monitored) as was the case with select/poll.
    6. 水平触发(level-triggered): 例如只要有数据可以读(处于可读的状态)，不管怎样都会通知。select也是这种
    7. 边缘触发(edge-triggered): 只有状态发生变化时才会通知。适用于高性能要求，例如`Nginx`就使用了边缘触发