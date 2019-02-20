1. 网络通信概述：
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190220-133051@2x.png)
2. 协议层模型
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190220-133356@2x.png)
3. TCP/IP协议概况
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190220-133912@2x.png)
4. TCP
    - TCP提供了可靠性。向对端发送数据时，要求对端返回确认。若未收到确认则自动重传并等待更长时间。多次重试后，TCP才会放弃
    - TCP含有用于动态估算客户和服务器之间的往返时间(round-trip time, RTT)的算法
    - TCP通过给每个字节关联一个序列号对所发送的数据进行排序(sequencing)。从而在对端可实现重排序和去重
    - TCP提供流量控制(flow control): TCP always tells its peer exactly how many bytes of data it is willing to accept from the peer at any one time. This is called the advertised window.
    - TCP是全双工的(full-deplex): 意味着在一个给定的连接上应用可以在任何时刻在进出两个方向上发送和接收数据
5. TCP连接的建立
    - 首先，服务器必须准备好接收外来的连接，称为被动打开(passive open)
    - 客户通过调用`connect`发起主动打开(active open)。客户发送一个SYN(同步)分节（通常不携带数据），它告诉服务器客户将在连接中发送的数据的初始序列号
    - 服务器确认(ACK)客户的SYN, 同时自己也发送一个SYN, 它含有服务器将在同一连接中发送的数据的序列号(全双工嘛)。在单个分节中发送SYN和对客户SYN的ACK
    - 客户确认服务器的SYN
    - 上述过程至少需要3个分组，因而称为TCP的三路握手
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190220-142459@2x.png)
6. TCP连接的终止
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190220-143003@2x.png)
7. TCP状态转换图
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190220-143516@2x.png)
