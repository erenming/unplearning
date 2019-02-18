1. 服务器设计模式：
    - tcp迭代服务器
    - tcp并发服务器，每个客户一个子进程
    - tcp预先派生子进程服务器，accpet无上锁保护
    - tcp预先派生子进程服务器，accept使用文件上锁保护
    - tcp预先派生子进程服务器，accept使用线程上搜保护
    - tcp预先派生子进程服务器，传递描述符
    - tcp并发服务器，每个客户一个线程
    - tcp预先创建线程服务器，每个线程各自accept
    - tcp预先创建线程服务器，主线程统一accept
2. tcp预先派生子进程服务器，accpet无上锁保护
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190218-222653@2x.png)
    - 惊群（thundering herd）: 尽管只有一个子进程将获得连接，所有N个子进程却都被唤醒了