#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <stdbool.h>

int nbrThreads;
int verrou = 0;  // déverrouillé
int todo = 64000;

static inline void lock() {
    int value = 1;
    do {
        __asm__(
            "xchg %0, %1" // échange les valeurs de %0 et %1
            : "+r" (value), "+m" (verrou)
        );
    } while (value == 1);
}

static inline void unlock() {
    verrou = 0;
    }

void* travail(void* n) { 

    for(int i = 0; i < todo/nbrThreads; i++){
        lock();
        for (size_t i = 0; i < 10000; i++);
        unlock();
    }
    return NULL;
}

int main(int argc, const char* argv[]) {
    int err;
    
    if (argc == 2){
        nbrThreads = atoi(argv[1]);  // define number of threads
    }
    else return -1;

    pthread_t* threads = (pthread_t *) malloc(nbrThreads * sizeof(pthread_t));
    int* Id = (int *) malloc(nbrThreads * sizeof(int));

    for (size_t i = 0; i < nbrThreads; i++){
        Id[i] = i;
        err = pthread_create(&(threads[i]), NULL, &travail, &(Id[i]));  // init the threads
        if(err!=0){
            printf("Error: %d", -3);
            return -3;
        }
    }

    for (int i=0; i< nbrThreads; i++) {
        err = pthread_join(threads[i], NULL);  // wait threads 
        if(err!=0) {
            printf("Error: %d", -4);
            return -4;
        }
    }

    free(threads);
    free(Id);

    return 0;
}