// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include <muduo/base/Condition.h>

#include <errno.h>

// returns true if time out, false otherwise.
bool muduo::Condition::waitForSeconds(int seconds)
{
  struct timespec abstime;
  clock_gettime(CLOCK_REALTIME, &abstime);
  abstime.tv_sec += seconds;
  return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.getPthreadMutex(), &abstime);
}

//条件变量 condition 配合mutex
//线程1
//锁住mutex
//   while(条件)
//         等待   做了三件事:(1,解锁 2, 等待条件变量 3,返回时加锁 )
//解锁mutex
//
//线程2
//锁住mutex
//    更改条件
//    signal或broadcast 不用保护, 可以移到外面
//解锁mutex
//
//        signal或broadcast

