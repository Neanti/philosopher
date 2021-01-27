#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>

int main() {

    sem_t *pool;
    sem_t *txt;

    sem_unlink("pool");
    sem_unlink("txt");
    txt = sem_open("txt", O_CREAT, S_IRWXU, 1);
    pool = sem_open("pool", O_CREAT, S_IRWXU, 1);
    sem_wait(txt);
    printf("got txt\n");
    sem_post(txt);
    printf("post txt\n");
    sem_wait(pool);
    printf("got pool\n");
    sem_post(pool);
    printf("post pool\n");
    return 0;
}