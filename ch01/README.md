## 练习1.1
GCC编译器参考: http://labor-liber.org/en/gnu-linux/development/index.php?diapo=extensions

目前主流项目使用.cpp或.cc作为源码后缀，.hpp作为头文件后缀。
编译器其实不在意后缀，反而是其他一些IDE工具会根据后缀来识别文件做相应的语法高亮等处理。

## 练习1.2
在我的系统返回的错误标识是255。为啥？

### 拓展知识

#### 程序执行原理
在bash shell上执行一个程序，其实是由bash进程fork了一个子进程进行运行
然后子进程退出将退出码返回给父进程。

参考：https://blog.csdn.net/GRrtx/article/details/131949852

#### 程序退出码
1. 在main函数执行return即表示退出进程，等同于调用exit
2. 在非main函数想直接退出进程则需要显示调用exit
exit是C库函数，直接调用_exit系统调用

那子进程的退出码是啥呢？就是 status & 0xFF的结果，其中status是return后面的值（或者传入exit函数的参数值）
这个操作也决定了进程退出码的取值范围是0~255，C库函数strerror可以将错误码转换成可读的字符串。
> The value status & 0xFF is returned to the parent process as the process's exit status

参考：https://www.man7.org/linux/man-pages/man2/exit.2.html


因为 -1 & 0xFF的结果是255，且bash进程将子进程的退出码存放在$?变量中，所以echo $?的结果是255

## 练习 1.3

``` c++
#include <iostream>

int main()
{
    std:cout << "Hello, World" << std::endl;
    
    return 0;
}
```



## 练习 1.4

``` c++
#include <iostream>

int main()
{
	std::cout << "Enter two numbers:" << std::endl;
	int v1 = 0, v2 = 0;
	std::cin >> v1 >> v2;
	std::cout << "The product of " << v1 << " and " << v2
		  << " is " << v1 * v2 << std::endl;
}
```

## 练习1.5
[[code](./ex1-4.cc)]

## 练习1.6
程序不合法，第一行的分号导致后面的 “<<” 左侧没有运算对象，是一个不完整的表达式。
编译器会报如下错误：

```
  ex1-4.cc: In function ‘int main()’:
  ex1-4.cc:8:41: error: expected primary-expression before ‘<<’ token
      8 |   std::cout << "The product of " << v1; << " and " << v2;
        |                                         ^~
  ex1-4.cc:9:3: error: expected primary-expression before ‘<<’ token
      9 |   << " is " << v1 * v2 << std::endl;
        |   ^~
```
两种改法：
1. 去掉中间的分号
2. 在后面两行的第一个 “<<” 之前补上 std::cout，使表达式完整

        
		

		
## 练习1.7

```
ex1-8.cc:4:14: error: extended character 。 is not valid in an identifier
    4 | * 注释对/* */不能嵌套。
      |              ^
ex1-8.cc:4:14: error: ‘不能嵌套。’ does not name a type
    4 | * 注释对/* */不能嵌套。
      |              ^~~~~~~~~~

```

## 练习1.8
    ` std::cout << "/*"; ` 预测合法，实测编译通过。
    
	` std::cout << "*/"; ` 预测合法，实测编译通过。
	
`    std::cout << /* "*/" */; ` 预测不合法，实测编译不通过。
>
```ex1-8.cc:8:24: warning: missing terminating " character
    8 |     std::cout << /* "*/" */;
      |                        ^
ex1-8.cc:8:24: error: missing terminating " character
    8 |     std::cout << /* "*/" */;
      |                        ^~~~~
ex1-8.cc: In function ‘int main()’:
ex1-8.cc:11:5: error: expected primary-expression before ‘return’
   11 |     return 0;
      |     ^~~~~~


```


`  std::cout << /* "*/" /* "/*" */; ` 预测不合法，实测编译通过。

记住两点：
1. 以/*开头，中间可以包含任意内容，包括双引号，都视为注释内容一部分，直至遇到 */ 为止
2. 如果双引号开头，里面的任意字符，包括/* 或 */都作为字符串的一部分，直至遇到匹配的双引号为止


