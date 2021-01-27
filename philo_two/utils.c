#include "utils.h"

int error_arg()
{
    write(1, "Args error\n", 11);
    return 1;
}

int error_thread()
{
    write(1, "Thread error\n", 13);
    return 1;
}

int error_mutex()
{
    write(1, "Mutex error\n", 12);
    return 1;
}

int error_malloc()
{
    write(1, "Malloc error\n", 13);
    return 1;
}


int ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return i;
}

int is_number(char *s)
{
    int i;

    i = 0;
    while(s[i] >= '0' && s[i] <= '9')
        i++;
    if (i != ft_strlen(s))
        return 0;
    return 1;
}

int ft_toInt(char *s)
{
    int i;
    int r;

    i = 1;
    r = 0;
    r = r + (s[0] - 48);
    while(i < ft_strlen(s))
    {
        r = (10 * r) + (s[i] - 48);
        i++;
    }
    return r;
}

param_philo * fill_arg(char **av, int ac)
{
    int *t;
    int i;
    param_philo *p;

    if (!(p = malloc(sizeof(param_philo))))
        return NULL;
    if (!(t = (int*)malloc(sizeof(int) * 5)))
        return NULL;
    i = 1;
    while(i < ac)
    {
        t[i - 1] = ft_toInt(av[i]);
        i++;
    }
    p->ph = t[0];
    p->die = t[1];
    p->eat = t[2];
    p->sleep = t[3];
    if (ac == 5)
        p->nb = -1;
    else
        p->nb = t[4];
    return p;
}
