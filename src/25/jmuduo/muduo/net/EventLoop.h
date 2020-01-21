// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

//TCP网络编程 核心 处理 三个半事件
//1 连接建立  客户端主动connect发起连接  服务器accept被动接受连接
//2 连接断开  主动断开close shutdown 被动断开read = 0
//3 消息到达  文件描述符可读
//3.5 消息发送完毕 对于低流量的服务,可以不必关心,
//这里的发送完毕是指数据写入操作系统(内核)缓冲区, 将由TCP协议栈负责数据的发送和重传
//不代表对方已经接收到数据





#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include <boost/noncopyable.hpp>

#include <muduo/base/CurrentThread.h>
#include <muduo/base/Thread.h>

namespace muduo
{
namespace net
{

///
/// Reactor, at most one per thread.
///
/// This is an interface class, so don't expose too much details.
class EventLoop : boost::noncopyable
{
 public:
  EventLoop();
  ~EventLoop();  // force out-line dtor, for scoped_ptr members.

  ///
  /// Loops forever.
  ///
  /// Must be called in the same thread as creation of the object.
  ///
  void loop();

  void assertInLoopThread()
  {
    if (!isInLoopThread())
    {
      abortNotInLoopThread();
    }
  }
  bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

  static EventLoop* getEventLoopOfCurrentThread();

 private:
  void abortNotInLoopThread();
  
  bool looping_; /* atomic */
  const pid_t threadId_;		// 当前对象所属线程ID
};

}
}
#endif  // MUDUO_NET_EVENTLOOP_H
