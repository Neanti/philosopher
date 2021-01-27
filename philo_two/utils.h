#ifndef UTILS_H
#define UTILS_H
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>

typedef struct {
    int ph;
    int die;
    int eat;
    int sleep;
    int nb;
} param_philo;

typedef struct {
    sem_t *end;
    int n;
} fin;

typedef struct {
    int n;
    param_philo p;
    sem_t *pool;
    pthread_t *th;
    sem_t *txt;
    struct timeval start;
    fin *end;
} philo;

int error_arg();
int error_thread();
int error_mutex();
int error_malloc();
int ft_strlen(char *s);
int is_number(char *s);
int ft_toInt(char *s);
param_philo * fill_arg(char **av, int ac);

#endif