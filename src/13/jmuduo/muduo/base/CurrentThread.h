// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

namespace muduo
{
namespace CurrentThread
{
  // internal
  extern __thread int t_cachedTid;
  extern __thread char t_tidString[32];
  extern __thread const char* t_threadName;
  void cacheTid();

  inline int tid()// CurrentThread::tid() 重点
  {
    if (t_cachedTid == 0)
    {
      cacheTid();
    }
    return t_cachedTid;
  }

  inline const char* tidString() // for logging
  {
    return t_tidString;
  }

  inline const char* name()
  {
    return t_threadName;
  }

  bool isMainThread();
}
}

#endif


//inline用于实现, 函数定义体之前 , 不要放在声明前, 对于频繁调用的小函数, 可以减少函数调用的开销,
//因此, 必须小, 不要带有循环之类的,那样毫无意义.

//inline int tid()                      2
//{
//    if(t_cachedTid() == 0)
//    {
//        cachedTid();
//    }
//    return t_cachedTid;
//}
//
//__thread int t_cachedTid = 0;
//
//pid_t gettid()                           4
//{
//    return static_cast<pid_t>(::syscall(SYS_gettid));//系统调用
//}
//
//void CurrentThread::cacheTid()//设置缓存   3
//{
//    if (t_cachedTid == 0)
//    {
//        t_cachedTid = detail::gettid(); //t_cachedTid就一个
//        int n = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
//        assert(n == 6); (void) n;
//    }
//}
//
//pid_t      tid_;
//tid_ = CurrentThread::tid();              1

