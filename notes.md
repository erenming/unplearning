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