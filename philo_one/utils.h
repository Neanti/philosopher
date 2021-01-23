#ifndef UTILS_H
#define UTILS_H
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
typedef struct {
    int ph;
    int die;
    int eat;
    int sleep;
    int nb;
} param_philo;

typedef struct {
    int n;
    pthread_mutex_t *m;
} forks;

typedef struct {
    int n;
    param_philo p;
    forks *fl;
    forks *fr;
    pthread_t *th;
    pthread_mutex_t *txt;
    struct timeval start;
} philo;

int error_arg();
int error_thread();
int error_mutex();
int error_malloc();
int ft_strlen(char *s);
int is_number(char *s);
int ft_toInt(char *s);
param_philo * fill_arg(char **av, int ac);
void print_arg(param_philo *p);


#endif