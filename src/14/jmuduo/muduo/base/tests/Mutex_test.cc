//#include <muduo/base/CountDownLatch.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/Thread.h>
#include <muduo/base/Timestamp.h>

#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>
#include <stdio.h>

using namespace muduo;
using namespace std;

MutexLock g_mutex;
vector<int> g_vec;
const int kCount = 10*1000*1000;

void threadFunc()
{
  for (int i = 0; i < kCount; ++i)
  {
    MutexLockGuard lock(g_mutex);//在构造函数中加锁,在析构函数中解锁
    g_vec.push_back(i);
  }
}

int main()
{
  const int kMaxThreads = 8;
  g_vec.reserve(kMaxThreads * kCount);//8000万个字节数,有300多M,

  Timestamp start(Timestamp::now());
  for (int i = 0; i < kCount; ++i)
  {
    g_vec.push_back(i);
  }

  printf("single thread without lock %f\n", timeDifference(Timestamp::now(), start));

  start = Timestamp::now();
  threadFunc();
  printf("single thread with lock %f\n", timeDifference(Timestamp::now(), start));

  for (int nthreads = 1; nthreads < kMaxThreads; ++nthreads)
  {
    boost::ptr_vector<Thread> threads;
    g_vec.clear();
    start = Timestamp::now();
    for (int i = 0; i < nthreads; ++i)
    {
      threads.push_back(new Thread(&threadFunc));
      threads.back().start();
    }
    for (int i = 0; i < nthreads; ++i)
    {
      threads[i].join();
    }
    printf("%d thread(s) with lock %f\n", nthreads, timeDifference(Timestamp::now(), start));
  }
}
//1, 2,3,4,5,6,7个线程共同争锁所用时间消耗.
