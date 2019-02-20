1. 服务器设计模式：
    - tcp迭代服务器
    - tcp并发服务器，每个客户一个子进程
    - tcp预先派生子进程服务器，accpet无上锁保护
    - tcp预先派生子进程服务器，accept使用文件上锁保护
    - tcp预先派生子进程服务器，accept使用线程上锁保护
    - tcp预先派生子进程服务器，传递描述符
    - tcp并发服务器，每个客户一个线程
    - tcp预先创建线程服务器，每个线程各自accept
    - tcp预先创建线程服务器，主线程统一accept
2. tcp预先派生子进程服务器，accpet无上锁保护
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190218-222653@2x.png)
    - 惊群（thundering herd）现象: 尽管只有一个子进程将获得连接，所有N个子进程却都被唤醒了
    - 冲突(collision)现象：occurs when multiple processes call select on the same descriptor. If multiple processes are waiting for the same descriptor, the kernel must wake up all processes that are blocked in a call to select since it doesn't know which processes are affected by the descriptor that just became ready.
3. tcp预先派生子进程服务器，accept使用文件上锁保护
    - 在应用进程在accept前后安置某种形式的锁，这里使用文件锁
4. tcp预先派生子进程服务器，accept使用线程上锁保护
    - 由于文件上锁涉及文件系统，较为耗时。故改为线程上锁
    - 上锁要求：
        1. 互斥锁变量必须存放在由所有进程共享的内存中
            - 诸多方法可用于不同进程间共享内存空间，这里使用的是mmap函数和`/dev/zero`设备
        2. 必须告知线程函数库这是不同进程之间共享的互斥锁
5. tcp预先派生子进程服务器，传递描述符
    ![xx](https://github.com/tomming233/unplearning/raw/master/notes/images/WX20190219-112919@2x.png)
    - 比文件上锁和线程上锁都耗时
6. tcp并发服务器，每个客户一个线程
7. tcp预先创建线程服务器，每个线程各自accept
    - 创建一个线程池，并让每个线程各自调用accept。并互斥锁以保证任何时刻只有一个线程在调用accept
8. tcp预先创建线程服务器，主线程统一accept
9. 小结：
    - 进程池模式下，需要监视子进程个数，随着服务的客户数量动态增减
    - 让所有子进程或线程自行accept通常比让fu'jin'c或主线程独自调用accept并把描述符传递给子进程或线程更为简单且迅速
    - 由于select冲突，通常所有子进程或线程阻塞于同一accept比同一select调用中更可取