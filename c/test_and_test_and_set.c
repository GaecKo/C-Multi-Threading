#include "header/test_and_test_and_set.h"

int nbrThreads;
int verrou = 0;  // déverrouillé
int todo = 64000;

// Fonction test_and_set
bool test_and_set() {
    if (verrou == 1) return false; // verrou occupé
    verrou = 1;
    return true;
}

void *travail() {

    for (int i = 0; i < todo/nbrThreads; i++) {
        while (test_and_set() == false) { // on a pas le verrou
            while (verrou == 1) {}
        }
        // Section critique
        for (size_t i = 0; i < 10000; i++);

        // Libération du verrou
        verrou = 0;
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
    free(Id);
}