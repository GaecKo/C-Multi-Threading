#ifndef SEM
#define SEM

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // import usleep()
#include <stdio.h>

typedef struct {
    int value;
    pthread_mutex_t verrou;
} sem;

int init(sem *s, int value);

int wait(sem *s);

int post(sem *s);

int destroy(sem *s);

#endif