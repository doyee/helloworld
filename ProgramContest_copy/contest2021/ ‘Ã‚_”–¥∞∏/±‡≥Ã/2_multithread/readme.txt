#Title: 多线程

一个货运装置，传送带会将一件货物传送过来，货物传送过来以后，装货员会将货物装上车
这件货物装车后，传送带会将下一件货物传送过来，然后装货员会再将物装装上车
装上8件物品后，车子装满，传送带会停止传送货物

利用多线程方式实现物品传送和装货的次序

根据给出的代码文件，阅读基本代码文件含义，实现空缺部分的代码
代码目的：通过创建两个线程来实现对一个数的递加

Output：
正在传送第 (1) 个货物
正在装车第 (1) 个货物
正在传送第 (2) 个货物
正在装车第 (2) 个货物
正在传送第 (3) 个货物
正在装车第 (3) 个货物
正在传送第 (4) 个货物
正在装车第 (4) 个货物
正在传送第 (5) 个货物
正在装车第 (5) 个货物
正在传送第 (6) 个货物
正在装车第 (6) 个货物
正在传送第 (7) 个货物
正在装车第 (7) 个货物
正在传送第 (8) 个货物
正在装车第 (8) 个货物
本次装车结束
本次装车结束

//////////////////////////
#NOTE:
a. compiling command: gcc multithread.c
b. running command: ./multithread
//////////////////////

互斥变量使用特定的数据类型：pthread_mutex_t，使用互斥量前要先初始化，使用的函数如下：
#include <pthread.h>
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);


简单的使用可以使用默认的属性初始化互斥量，函数的后一个参数设置为NULL即可。
对互斥量加锁解锁的函数如下：
#include <pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

条件变量
条件变量与互斥量一直使用时，允许线程以无竞争的方式等待特定的条件发生。条件变量是线程可用的另一种同步机制。
条件本身是由互斥量保护的。线程在改变条件状态之前必须产生锁住互斥量，其他线程在获得互斥量之前不会到这种改变，因为互斥量必须在锁定以后才能计算条件。
在使用条件变量之前必须先对它初始化。释放条件变量底层的内存空间之前，对条件变量反初始化。使用的相关函数如下：
#include <pthread.h>
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
int pthread_cond_signal(pthread_cond_t *cond);
