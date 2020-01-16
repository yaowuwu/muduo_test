//面向对象的线程类
//Thread 抽象类
//+threadId_: pthread_t
//+Start(): void
//+Join(): void
//-ThreadRoutine(void* argc): void* 线程的入口函数 静态成员函数
//-Run(): void 执行体  纯虚函数
//  TestThread 具体类

#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
class Thread{
public:
    Thread();
    virtual ~Thread();//作为多态的基类,必须用纯虚析构函数, 不然导致派生类资源释放不完全,
                      //若不作为多态的基类,可以不用纯虚

    void Start();
    void Join();
private:
    void Run() = 0;
    pthread_t pthreadId_;
};


#endif //_THREAD_H_
