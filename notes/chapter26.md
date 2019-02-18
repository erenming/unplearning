1. 线程
    - 又称为轻权进程(lightweight process)， 创建速度为进程的10~100倍
    - 同一进程内的所有线程共享相同的全局内存，便于共享信息的时候带来了**同步**问题
    - 共享的信息：进程指令，大多数数据，打开的文件（描述符），信号处理函数和信号处置，当前工作目录，用户ID和组ID
    - 特有的信息：线程ID，寄存机集合（包括程序计数器和栈指针），栈（用于存放局部变量和返回地址），errno，信号掩码，优先级
2. pthread_create:
    ```c
    #include <pthread.h>
    int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*func) (void *), void *arg);
    // Returns: 0 if OK, positive Exxx value on error
    ```
    - 当一个程序由exec启动后，称为初始线程（initial thread）或主线程（main thread）的单个线程就创建了。其余的线程由pthread_create创建
    - 参数说明：
        1. tid: 线程ID
        2. *attr: 属性指针，属性包括：优先级，初始栈大小，是否为一个守护线程等等
        3. func: 由该线程执行的函数
        4. arg: 函数所需的参数
3. pthread_join：用以等待一个给定线程终止
    ```c
    #include <pthread.h>
    int pthread_join (pthread_t tid, void ** status);
    // Returns: 0 if OK, positive Exxx value on error
    ```
    - 参数说明：
        1. tid: 要等待的线程ID
        2. status: 若status指针为空，则我们所等待的线程的返回值将存入status指向的位置
4. pthread_self: 获取自身线程ID
5. pthread_detach: 将指定的线程转变为脱离状态
    ```c
    #include <pthread.h>
    int pthread_detach(pthread_t tid);
    // Returns: 0 if OK, positive Exxx value on error
    ```
    - 可汇合的(joinable, 默认)：当一个可汇合的线程终止时，它的线程ID和退出状态将留存，直到另一个对它调用了pthread_join
    - 脱离的（detached）：终止时，所有相关的资源都被释放，我们不能等待它终止
6. pthread_exit: 让一个线程终止
    ```c
    #include <pthread.h>
    void pthread_exit (void *status);
    // Does not return to caller
    ```
    - status不能指向对于调用线程是局部的对象，因为线程终止时这样的对象同时也消失
7. 现场特定数据
    - 动机：A function that keeps state in a private buffer, or one that returns a result in the form of a pointer to a static buffer, is not thread-safe because multiple threads cannot use the buffer to hold different things at the same time
    - 解决方案：
        1. 使用线程特定数据（常用）
        2. 改变调用顺序，那么调用者可将所有参数打包进一个结构中
        3. 改变接口的结构，避免使用静态变量
    - 每个系统支持有限数量的线程特定数据：
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190214-113629@2x.png)
8. 互斥锁(mutex)：
    - 动机：多个线程更改一个共享变量会导致错误
    - 线程访问变量的前提是持有该互斥锁
9. 条件变量：
    - 动机：we need something else to let us go to sleep waiting for some condition to occur
    - 解决方案：
        1. 互斥锁结合条件变量：可以让主循环进入睡眠，直到某个线程通知它有事可做才醒来