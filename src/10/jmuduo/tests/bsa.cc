#include <boost/static_assert.hpp>
//编译时断言
//而我们平时用的assert是运行时断言



class Timestamp
{
private:
	int64_t microSecondsSinceEpoch_;
};

BOOST_STATIC_ASSERT(sizeof(Timestamp) == sizeof(int64_t));
//BOOST_STATIC_ASSERT(sizeof(int) == sizeof(short));

int main(void)
{

    //assert(sizeof(int) == sizeof(short));运行时才能检测
	return 0;
}
