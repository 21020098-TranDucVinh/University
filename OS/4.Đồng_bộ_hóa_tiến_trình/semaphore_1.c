#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Mở 1 semaphore hiện có hoặc tạo 1 semaphore mới
// sem : con trỏ semaphore
// pShare : cho biết semaphore này được chia sẻ giữa các tiểu trình của 1 tiến trình (p = 0) hay tiến trình
// value : khởi tạo với giá trị value
// int sem_init(sem_t *sem, int pShared, unsigned int value)

// int sem_wait(sem_t sem)

// int sem_post(sem_t sem)

sem_t s0, s1, s2;

void *thread_0(void *ard);
void *thread_1(void *ard);
void *thread_2(void *ard);

int main()
{
    sem_init(&s0, 0, 1);
    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 0);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, thread_0, NULL);
    pthread_create(&t2, NULL, thread_1, NULL);
    pthread_create(&t3, NULL, thread_2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&s0);
    sem_destroy(&s1);
    sem_destroy(&s2);

    return 0;
}

void *thread_0(void *arg)
{
    while (1)
    {
        sem_wait(&s0);
        printf("0");
        sem_post(&s1);
        sem_post(&s2);
    }
}

void *thread_1(void *arg)
{
    sem_wait(&s1);
    sem_post(&s0);
}

void *thread_2(void *arg)
{
    sem_wait(&s2);
    sem_post(&s0);
}