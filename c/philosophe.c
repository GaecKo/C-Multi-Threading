#include "header/philosophe.h"

// Global Var
int PHILOSOPHES;                        // number of philosopher
int FORKS;                              // number of fork

pthread_t* phil;                        // array of philosopher (array of threads)
pthread_mutex_t* baguette;              // array of fork (array of mutex)
int* Id;                                // array of fork's id (id of mutex)

void mange(int id) {}//printf("Philosophe [%d] mange\n",id);} // eat during 0 second

void* philosopheNStartCycle(void* n) { 
        int *id=(int *) n;
        int left = *id;
        int right;
        if (PHILOSOPHES == 1) right = 1;
        else right = (left + 1) % PHILOSOPHES;
              
    for ( size_t i = 0; i < 10000000; i++) {       

        int indexFirst = (left < right)? left : right;   // index of first fork caught
        int indexSecond = (left < right)? right : left;  // index of second fork caught

        pthread_mutex_lock(&baguette[indexFirst]);  

        pthread_mutex_lock(&baguette[indexSecond]); 

        mange(*id);      // eat

        pthread_mutex_unlock(&baguette[indexFirst]);   

        pthread_mutex_unlock(&baguette[indexSecond]); 
        
    }
    return (void *) NULL;
}

int main(int argc, const char* argv[]) { // argv[1] = number of philosopher
    int err;

    if (argc == 2){
        PHILOSOPHES = atoi(argv[1]);
    }
    else return -1;     // define number of philosophers

    FORKS = (PHILOSOPHES == 1)? 2:PHILOSOPHES;

    // allocates memory for philosophers and forks
    phil = (pthread_t *) malloc(PHILOSOPHES * sizeof(pthread_t));

    baguette = (pthread_mutex_t *) malloc(FORKS * sizeof(pthread_mutex_t));
    Id = (int *) malloc(FORKS * sizeof(int));
    
    // init
    for (size_t i = 0; i < PHILOSOPHES; i++) {

        Id[i] = i;  // init the Ids

        err = pthread_mutex_init(&baguette[i], NULL);  // init the mutexs (fork)
        if(err!=0) {
            printf("Error: %d", -2);
            return -2;
        }

        err = pthread_create(&(phil[i]), NULL, &philosopheNStartCycle, &(Id[i]));  // init the threads (philosopher)

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
        err = pthread_mutex_destroy(&(baguette[i]));  // destroy all forks (mutex)
        if (err != 0) {
            printf("Error: %d\n", err);
            return -5;
        }
    }
    
    return 0;    
}