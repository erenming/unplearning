## 定义与术语
1. MSL: maximum segment lifetime, 最长分节生命周期
2. MTU: maximum transmission unit, 最大传输单元
3. MSS: maximum segment size, 最大分节大小
4. POSIX: 
    - Portable Operating System Interface,是由IEEE开发的一系列标准，是涵盖了大量c语言编程接口的规范
5. 分节:
    - SYN: 同步分节，1 byte, 同一连接中发送的数据的初始序列号
    - FIN: 结束分节，1 byte, 结束分节
    - ACK: 确认分节，是发送端所期待的下一个序列号
    - RST: 复位分节，服务器在我们指定的端口上无进程在等待连接，TCP想取消一个已有连接
---

## 笔记
1. Unix errno值:
    - 只要一个unix函数中有错误发生，全局变量errno就会被设置为一个指明该错误类型的正值，函数本身则通常返回-1
2. 端口号:
    - 0~1023: IANA控制并分配
    - 1024~49151: IANA已登记端口
    - 49152~65535: 私用端口
3. 并发情况: 通过对来自客户端ip:port, fork子进程，形成已连接套接字
    - 监听套接字: `{*:80, *:*}`
    - 已连接套接字: `{*:80, cli_ip:cli_port1}`, `{*:80, cli_ip:cli_port2}`
4. socket pair: 套接字对，四元组，`(local ip, local tcp port, remote ip, remote tcp port)`
5. socket: 套接字，二元组`(ip, port)`
6. TCP TIME_WAIT 状态
    - 2 * MSL(最长分节生命周期)
    - 作用: 
        1. 可靠地实现TCP全双工连接的终止
        2. 允许老的重复分节在网络中消逝
7. 内存中字节值的存储方式
    - 小端字节序, little-endian: 低序字节存储在起始位置
    - 大端字节序, big-endian: 高序字节存储在起始位置
8. value-result 参数
    - 函数调用时，参数大小为一个值
    - 函数返回时，参数大小为一个结果
    - 可以被函数修改
9. 信号(signal): 一个用于告知某个进程发生了某个事件的通知，并有一个与之关联的处置(行为)
    - 由一个进程发给另一个进程（自身）
    - 由内核发给某个进程
    - 信号处理函数: 当特定信号发生时被调用的函数。这种行为成为捕获信号
    - 信号可以被处置为SIG_IGN(忽略)用来忽略它 或 SIG_DFL(默认)来启用它的默认处置
    - 注意点:
        1. 当fork子进程时，必须捕获SIGCHLD信号，否则子进程会僵死
        2. 当捕获信号时，必须处理被中断的系统调用
        3. SIGCHLD的信号处理必须正确，应使用waitpid函数以避免留下僵死进程，因为Unix信号不排队
10. 跨越套接字传输二进制数据
    - 问题：由于位数、大端小端等原因会导致错误
    - 解决:
        1. 把数据作为文本串传输
        2. 显示定义所支持数据类型的二进制格式（位数、大端或小端字节序），并以此格式在客户与服务器间传递数据
11. Unix domain socket: A Unix domain socket or IPC socket (inter-process communication socket) is a data communications endpoint for exchanging data between processes executing on the same host operating system.