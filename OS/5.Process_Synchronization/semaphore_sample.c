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

sem_t sem;
void *thread(void *arg)
{
    sem_wait(&sem);
    printf("\nEntered CS.. \n");
    sleep(2);
    printf("\nJust Exitting CS .. \n");
    sem_post(&sem);
}

int main()
{
    sem_init(&sem, 0, 1);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread, NULL);
    pthread_create(&t2, NULL, thread, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);
    return 0;
}