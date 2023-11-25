#include "header/philosophe.h"
#include "sem.c"

#include <pthread.h>
#include <stdlib.h>


int PHILOSOPHES;                        // number of philosopher
int FORKS;                              // number of fork

pthread_t* phil;                        // array of philosopher (array of threads)
sem* forks;              // array of fork (array of mutex)
int* Id;                                // array of fork's id (id of mutex)

void mange(int id) {}  // eat during 0 second

void* philosopheNCycle(void* n) { 
        int* id=(int*) n;
        int left = *id;
        int right;
        if (PHILOSOPHES == 1) right = 1;
        else right = (left + 1) % PHILOSOPHES;
              
    for ( size_t i = 0; i < 10000000; i++) {       

        int indexFirst = (left < right)? left : right;  // index of first fork caught
        int indexSecond = (left < right)? right : left;  // index of second fork caught

        wait(&forks[indexFirst]);  // take the first fork
        //printf("philosophe[%d]: a pris baguette[%d]\n", *id, indexFirst);

        wait(&forks[indexSecond]);  // take de second fork
        //printf("philosophe[%d]: a pris baguette[%d]\n", *id, indexSecond);

        mange(*id);  // eat
        //printf("philosophe[%d]: mange\n", *id);

        post(&forks[indexFirst]);  // drop de first fork
        post(&forks[indexSecond]);  // drop de second fork
        
    }
    return NULL;
}

int main(int argc, const char* argv[]) { // argv[1] = number of philosopher
    int err;

    if (argc == 2){
        PHILOSOPHES = atoi(argv[1]);  // define number of philosophers
    }
    else return -1; 

    FORKS = (PHILOSOPHES == 1)? 2:PHILOSOPHES;  // define number of forks

    // allocates memory for philosophers, forks and id
    phil = (pthread_t *) malloc(PHILOSOPHES * sizeof(pthread_t));
    forks = (sem *) malloc(FORKS * sizeof(sem));
    Id = (int *) malloc(FORKS * sizeof(int));
    
    // init philosophers, forks and id
    for (size_t i = 0; i < PHILOSOPHES; i++) {

        Id[i] = i;  // init the Ids

        err = init(&forks[i], 1);  // init semaphores (fork)
        if(err!=0) {
            printf("Error: %d", -2);
            return -2;
        }

        err = pthread_create(&(phil[i]), NULL, &philosopheNCycle, &(Id[i]));  // init the threads (philosopher)
        if(err!=0) {
            printf("Error: %d", -3);
            return -3;
        }
    }

    for (int i=0; i< PHILOSOPHES; i++) {
        err = pthread_join(phil[i], NULL);  // wait threads (philosopher)
        if(err!=0) {
            printf("Error: %d", -4);
            return -4;
        }
    }

    for (int i=0; i< FORKS; i++) {
        err = destroy(&(forks[i]));  // destroy all forks (semaphores)
        if (err != 0) {
            printf("Error: %d\n", err);
            return -5;
        }
    }

    free(phil);
    free(forks);
    free(Id);
    
    return 0;    
}