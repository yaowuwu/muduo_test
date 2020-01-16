#include <muduo/base/Timestamp.h>
#include <vector>
#include <stdio.h>

using muduo::Timestamp;

void passByConstReference(const Timestamp& x)
{
  printf("%s\n", x.toString().c_str());
}

void passByValue(Timestamp x)
{
  printf("%s\n", x.toString().c_str());
}

void benchmark()
{
  const int kNumber = 1000*1000;

  std::vector<Timestamp> stamps;
  stamps.reserve(kNumber);//先预留1000万个空间, 这样在push_back的时候就没有时间消耗了
  for (int i = 0; i < kNumber; ++i)
  {
    stamps.push_back(Timestamp::now());
  }
  printf("%s\n", stamps.front().toString().c_str());
  printf("%s\n", stamps.back().toString().c_str());
  printf("%f\n", timeDifference(stamps.back(), stamps.front()));
//消耗1000000 时间的总值


// 循环找出相邻两个时间差, 并统计< 100ms > 100的个数
  int increments[100] = { 0 };
  int64_t start = stamps.front().microSecondsSinceEpoch();
  for (int i = 1; i < kNumber; ++i)
  {
    int64_t next = stamps[i].microSecondsSinceEpoch();
    int64_t inc = next - start;
    start = next;// 前后相邻两个时间之间的差值
    if (inc < 0)
    {
      printf("reverse!\n");
    }
    else if (inc < 100)//小于100的差 的分别(1,2,3,4,5,6...100)个数
    {
      ++increments[inc];
    }
    else
    {
      printf("big gap %d\n", static_cast<int>(inc));
    }
  }

  for (int i = 0; i < 100; ++i)
  {
    printf("%2d: %d\n", i, increments[i]);
  }
}

int main()
{
  Timestamp now(Timestamp::now());//将一个没有名称的对象通过拷贝构造给now对象
   // Timestamp now = Timestamp::now(); //等价写法
  printf("%s\n", now.toString().c_str());
  passByValue(now);
  passByConstReference(now);
  benchmark();
}

