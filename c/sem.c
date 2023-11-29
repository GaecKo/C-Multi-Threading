#include "include/sem.h"

// mutex
int init_mut(mut* m){
    m->state = 0;
    return 0;
}

int lock_mut(mut* m){
   int value = 1;
    while (value == 1) {
        __asm__(
            "xchg %0, %1"
            : "+r" (value), "+m" (m->state)
        );
        if (value == 1) usleep(100);
    }; // value = 1 si state == 1 car occupé donc on reesaye jusqu'a obtention
    return 0;
};

int unlock_mut(mut* m){
    __asm__(
        "movl $0, %0"
        :"=m" (m->state)
    );
    return 0;
};

int destroy_mut(mut* m){
    return 0;
};

// sem
int init_sem(sem *s, int value) {
    s->value = value;
    init_mut(&s->verrou);
    return 0;
}

int wait_sem(sem *s) {
    while (1) {
        lock_mut(&s->verrou);
        if (s->value > 0) {
            s->value--;
            unlock_mut(&s->verrou);
            break;
        }
        unlock_mut(&s->verrou);
        usleep(100);
    }
    return 0;
}

int post_sem(sem *s) {
    lock_mut(&s->verrou);
    s->value++;
    unlock_mut(&s->verrou);
    return 0;
}

int destroy_sem(sem *s) {
    destroy_mut(&s->verrou);
    return 0;
}