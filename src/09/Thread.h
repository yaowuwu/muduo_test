#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <boost/function.hpp>

class Thread
{
public:
	typedef boost::function<void ()> ThreadFunc;
	explicit Thread(const ThreadFunc& func);

	void Start();
	void Join();

	void SetAutoDelete(bool autoDelete);

private:
	static void* ThreadRoutine(void* arg);
	void Run();
	ThreadFunc func_;
	pthread_t threadId_;
	bool autoDelete_;
};

#endif // _THREAD_H_


//面向对象的编程风格
//reactor 模式实现的网络库
/*客户端  Client


服务器端
TcpServer  EventLoop (poll epoll)   父类 提供三个虚函数 OnConnection
                                                       OnMessage
                                                       OnClose

EchoServer  继承至TcpServer      子类 实现 虚函数的 具体方法

客户端发来的请求 到达 TCPServer 父类指针 调用 子类 方法  将三个虚函数的 业务逻辑 写在 EchoServer的类里面
 */

//基于对象的编程风格
/*
class EchoServer
{
public:
    EchoServer()
    {
        server.SetConnectionCallback(boost::bind(OnConnection));
        server.SetConnectionCallback(boost::bind(OnMessage));
        server.SetConnectionCallback(boost::bind(OnClose));
    }
    void OnConnecion() {...业务逻辑}
    void OnMessage()
    void OnClose()

    TcpServer server;
};
EchoServer不再 是继承TCPServer , 而是包含TCPServer 的一个对象
*/

/*
面向对象风格, 用一个EchoServer继承TCPServer(抽象类), 实现三个接口OnConnecion, OnMessage, Onclose
C风格, 三个接口不再是成员函数, 而是 全局函数,  EchoServer 不用 bind注册 而是提供三个指针,
       注册三个全局函数到网络库, 网络库通过函数指针来回调\
基于对象风格, 用一个EchoServer包含一个TCPServer(具体类)对象, 在构造函数里用 boost::bind 来注册,三个成员函数
*/























