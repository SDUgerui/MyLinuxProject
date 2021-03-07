#include "PthreadPool.h"

int tasks = 0, done = 0;
pthread_mutex_t lock;

void dummy_task(void *arg)   //任务函数
{
    usleep(100000);
    pthread_mutex_lock(&lock);
    /* 记录成功完成的任务数 */
    cout << "Tid:" << pthread_self() << "  " << done++ << endl;
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv)
{
    /* 初始化互斥锁 */
    pthread_mutex_init(&lock, NULL);

    PthreadPool pool;
    pool.Init(4);   //创建四个线程

    /* 只要任务队列还没满，就一直添加任务到任务队列中 */
    while (pool.AddTask(&dummy_task, NULL) == 0)
    {
        pthread_mutex_lock(&lock);
        tasks++;
        pthread_mutex_unlock(&lock);
        // cout << tasks << endl;
        if (tasks == 100)     //添加100个任务到任务队列中
            break;
    }

    cout << "add  tasks:" << done << endl;
    pool.Destory();   //摧毁线程池
    cout << "Did  tasks:" << done << endl;

    return 0;
}