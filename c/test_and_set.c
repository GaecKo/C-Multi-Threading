#include "include/test_and_set.h"

int nbrThreads;
int todo = 64000;

int verrou = 0;  // déverrouillé

void lock() {
    __asm__(
        "movl $1, %%eax;" // variable = 1;
        "enter:"
            "xchgl %%eax, %0;" // exchange "variable" with "verrou"
            "testl %%eax, %%eax;" // Test if "variable" = 0 
            "jnz enter;"
        : "=m" (verrou) // Output 
        : //no input 
        : "eax" // Clobbered register
    );
}

void unlock() {
    __asm__(
        "movl $0, %0"
        :"=m" (verrou)
    );
}

void* travail() { 

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

    for (size_t i = 0; i < nbrThreads; i++){

        err = pthread_create(&(threads[i]), NULL, &travail, NULL);  // init the threads
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

    return 0;
}