#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define COUNT 8 //车子装满货物的数量

static int int_conveying_number = 0; // 已经传送了多少货物
static int int_loading_number = 0;   // 已经装车了多少货物

pthread_mutex_t lock;
pthread_cond_t can_conveying; // 货物传送。
pthread_cond_t can_loading;   // 货物装车

void *loading(void *data)
{
    int n;
    while (1)
    {
        pthread_mutex_lock(&lock);
        if (int_conveying_number == int_loading_number)
        {
            pthread_cond_wait(&can_conveying, &lock); // 装完了，等传送带
        }
        if (int_conveying_number == -1)
        {
            printf("本次装车结束\n");
        }
        else
        {
            int_loading_number++;
            printf("正在装车第 (%d) 个货物\n", int_loading_number);
        }
        sleep(1);
        pthread_cond_signal(&can_loading); //通知装车货物
        pthread_mutex_unlock(&lock);
        if (int_conveying_number == -1)
            break;
    };
    return NULL;
}

void *conveying(void *data)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        if (int_conveying_number > int_loading_number)
        {
            pthread_cond_wait(&can_loading, &lock); // 等待装车
        }

        if (int_conveying_number >= COUNT)
        {                              // 检查是否装满车
            int_conveying_number = -1; // 没有货物
            printf("本次传送结束 \n");
        }
        else
        {
            int_conveying_number++;
            printf("正在传送第 (%d) 个货物 \n", int_conveying_number);
        }
        pthread_cond_signal(&can_conveying); // 通知传送
        pthread_mutex_unlock(&lock);
        if (int_conveying_number == -1)
            break;
    }
    return NULL;
}

int main(void)
{
    pthread_t th_conveyor, th_worker;
    void *retval;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&can_conveying, NULL);
    pthread_cond_init(&can_loading, NULL);

    pthread_create(&th_conveyor, NULL, conveying, 0);
    pthread_create(&th_worker, NULL, loading, 0);

    /* 等待装车完成，结束*/
    pthread_join(th_conveyor, &retval);
    pthread_join(th_worker, &retval);
    return 0;
}