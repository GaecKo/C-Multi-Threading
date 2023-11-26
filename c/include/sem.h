#ifndef SEM
#define SEM

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // import usleep()
#include <stdio.h>

// mutex
typedef struct {
    int state; // 1 = close, 0 = open
} mut;

int init_mut(mut* m);

int lock_mut(mut* m);

int unlock_mut(mut* m);

int destroy_mut(mut* m);

// semaphore
typedef struct {
    int value;
    mut verrou;
} sem;

int init_sem(sem *s, int value);

int wait_sem(sem *s);

int post_sem(sem *s);

int destroy_sem(sem *s);

#endif