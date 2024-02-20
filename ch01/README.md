## 练习1.1

## 练习1.2
在我的系统返回的错误标识是255。为啥？

### 拓展知识

#### 程序执行原理
在bash shell上执行一个程序，其实是由bash进程fork了一个子进程进行运行
然后子进程退出将退出码返回给父进程。

#### 程序退出码
1. 在main函数执行return即表示退出进程，等同于调用exit
2. 在非main函数想直接退出进程则需要显示调用exit
exit是C库函数，直接调用_exit系统调用

那子进程的退出码是啥呢？就是 status & 0xFF的结果，其中status是return后面的值（或者传入exit函数的参数值）
这个操作也决定了进程退出码的取值范围是0~255，C库函数strerror可以将错误码转换成可读的字符串。
> The value status & 0xFF is returned to the parent process as the process's exit status
参考:
- https://www.man7.org/linux/man-pages/man2/exit.2.html
- https://blog.csdn.net/GRrtx/article/details/131949852
因为 -1 & 0xFF的结果是255，且bash进程将子进程的退出码存放在$?变量中，所以echo $?的结果是255