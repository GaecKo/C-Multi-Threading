#include "header/philosophe.h"

// Global Var
int PHILOSOPHES;                        // number of philosopher

pthread_t* phil;                        // array of philosopher (array of threads)
pthread_mutex_t* baguette;              // array of fork (array of mutex)
int* Id;

void mange(int id) {}//printf("Philosophe [%d] mange\n",id);} // eat during 0 second

void* philosopheNStartCycle(void* n) { 
        int *id=(int *) n;
        int left = *id;
        int right;
        if (PHILOSOPHES == 1) right = 1;
        else right = (left + 1) % PHILOSOPHES;
              
    for ( size_t i = 0; i < 10000000; i++) {                                       
        //printf("Philosophe [%d] pense\n",*id);   // think

        if (left < right) {
            pthread_mutex_lock(&baguette[left]);   // take left fork
            //printf("Philosophe [%d] possède baguette gauche [%d]\n",*id,left);

            pthread_mutex_lock(&baguette[right]);    // take right fork
            //printf("Philosophe [%d] possède baguette droite [%d]\n",*id,right);

            mange(*id);      // eat

            pthread_mutex_unlock(&baguette[left]);   // drop left fork
            //printf("Philosophe [%d] a libéré baguette gauche [%d]\n",*id,left);

            pthread_mutex_unlock(&baguette[right]); // drop right fork
            //printf("Philosophe [%d] a libéré baguette droite [%d]\n",*id,right);

        } else {
            pthread_mutex_lock(&baguette[right]);   // take left fork
            //printf("Philosophe [%d] possède baguette droite [%d]\n",*id,right);

            pthread_mutex_lock(&baguette[left]);  // take right fork
            //printf("Philosophe [%d] possède baguette gauche [%d]\n",*id,left);

            mange(*id);          // eat

            pthread_mutex_unlock(&baguette[right]);   // drop left fork
            //printf("Philosophe [%d] a libéré baguette right [%d]\n",*id,right);

            pthread_mutex_unlock(&baguette[left]);   // drop right fork
            //printf("Philosophe [%d] a libéré baguette left [%d]\n",*id,left);
        } 
    }
    return (void *) NULL;
}


int main(int argc, const char* argv[]) { // argv[1] = number of philosopher
    int err;

    if (argc == 2) 
        PHILOSOPHES = atoi(argv[1]);
    else 
        return -1;     // define number of philosophers

    // allocates memory for philosophers and forks
    phil = (pthread_t *) malloc(PHILOSOPHES * sizeof(pthread_t));

    

    if (PHILOSOPHES > 1) {
        baguette = (pthread_mutex_t *) malloc(PHILOSOPHES * sizeof(pthread_mutex_t));
        Id = (int *) malloc(PHILOSOPHES * sizeof(int));
    }
    else {  // 1 philosopher => 2 forks
        baguette = (pthread_mutex_t *) malloc((PHILOSOPHES+1) * sizeof(pthread_mutex_t));
        Id = (int *) malloc((PHILOSOPHES+1) * sizeof(int));
    }

    // init
    for (size_t i = 0; i < PHILOSOPHES; i++) {

        Id[i] = i;          // init the Ids

        err = pthread_mutex_init(&baguette[i], NULL); // init the mutexs (fork)
        if(err!=0) {
            printf("Error: %d", -2);
            return -2;
        }
            

        err = pthread_create(&(phil[i]), NULL, &philosopheNStartCycle, &(Id[i]));   // init the threads (philosopher)

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

    for (int i=0; i< PHILOSOPHES; i++) {
        
        err = pthread_mutex_destroy(&(baguette[i])); // destroy all forks (mutex)
        if (err != 0) {
            printf("Error: %d\n", err);
            return -5;
        }


        if (PHILOSOPHES == 1){
            err = pthread_mutex_destroy(&(baguette[i+1])); // destroy all forks (mutex)
            if(err!=0) {
                printf("Error: %d", err);
                return -6;
            }
        }
    }
    return 0;    
}

