#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* doit(void* arg)
{
	printf("pid = %d begin doit ...\n",static_cast<int>(getpid()));
	pthread_mutex_lock(&mutex);
	struct timespec ts = {2, 0};
	nanosleep(&ts, NULL);
	pthread_mutex_unlock(&mutex);
	printf("pid = %d end doit ...\n",static_cast<int>(getpid()));

	return NULL;
}

//#include<pthread.h>
//int pthread_atfork(void(*prepare)(void), void(*parent)(void), void(*child)(void);
//调用fork时,内部创建子进程前  在父进程中会调用prepare,
//内部创建子进程成功后, 父进程会调用parent,子进程会调用child

void prepare(void)
{
	pthread_mutex_unlock(&mutex);
}

void parent(void)
{
	pthread_mutex_lock(&mutex);
}

int main(void)
{
	pthread_atfork(prepare, parent, NULL);
	printf("pid = %d Entering main ...\n", static_cast<int>(getpid()));
	pthread_t tid;
	pthread_create(&tid, NULL, doit, NULL);
	struct timespec ts = {1, 0};
	nanosleep(&ts, NULL);
	if (fork() == 0)//在fork之前父进程会调用prepare, prepare调用了解锁1,
	                //fork下来之后子进程当然也属于解锁状态
	                //此时子进程再调用doit, 加锁解锁各一次 fork() == 0, 完美退出
	                //此时父进程所在的线程也做了 doit ,先加锁1, 在prepare里解锁1, 再doit再多一次不必要的解锁
	                 //创建成功之后,再调用parent,又加锁1,再doit加锁1,死锁, 再解锁1,
	{
		doit(NULL);
	}
	pthread_join(tid, NULL);
	printf("pid = %d Exiting main ...\n",static_cast<int>(getpid()));

	return 0;
}
