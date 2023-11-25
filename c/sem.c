#include "header/sem.h"

int init(sem *s, int value) {
    s->value = value;
    pthread_mutex_init(&s->verrou, NULL);
    return 0;
}

int wait(sem *s) {
    while (1) {
        pthread_mutex_lock(&s->verrou);
        if (s->value > 0) {
            s->value--;
            pthread_mutex_unlock(&s->verrou);
            break;
        }
        pthread_mutex_unlock(&s->verrou);
        usleep(100);
    }
    return 0;
}

int post(sem *s) {
    pthread_mutex_lock(&s->verrou);
    s->value++;
    pthread_mutex_unlock(&s->verrou);
    return 0;
}

int destroy(sem *s) {
    pthread_mutex_destroy(&s->verrou);
    return 0;
}