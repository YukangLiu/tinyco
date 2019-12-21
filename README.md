# tinyco协程库
<br>
<br>
1、介绍：<br>
	netco协程库是一个极轻量，纯c++11实现的对称协程库。<br>
	上下文切换封装的是glibc的ucontext。<br>
<br>
<br>
2、使用：<br>
	netco只有两个接口，非常容易使用，分别是co_go(func)用于运行一个新的协程，co_yield()用于暂停当前协程。示例如下：<br>
```
int main()
{
	co_go(
		[]
		{
			std::cout << "111" << std::endl;
			co_go(
				[]
				{
					std::cout << "222" << std::endl;
					co_yield();
					std::cout << "222222" << std::endl;
				}
				);
			std::cout << "111111" << std::endl;
		}
	);
	return 0;
}
```
<br>
<br>
3、编译：<br>
	进入src文件夹make即可,因为有main.cc示例程序，所以make出来的为可执行文件。<br>
<br>
<br>
附：有什么需求或者bug，建议，问题，都可以邮件 390161495@qq.com 讨论交流，谢谢。<br>
