
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
