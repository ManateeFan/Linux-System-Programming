# Simple-Cgi-server
使用进程池+epoll方式实现的简单cgi服务器。父程序创建进程池，并监听客户端连接。父进程与子进程池之间利用管道进行通信，父进程将连接请求通知子进程处理。