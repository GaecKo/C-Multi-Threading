#include "include/prod_conso.h"
#include "include/sem.h"

#define N 8 // places dans le buffer

int buffer[N];
mut mutex;
sem empty;
sem full;

int* IdProd;
int* IdCons;

pthread_t* prod; // liste des producteur (threads)
pthread_t* cons; // liste des consomateur (threads)

int todo = 8192;  // nbr d'item a faire
int toeat = 8192;  // nbr d'item a manger

int index_place_libre = 0;

int randomInt(){
    int INT_MAX= 2147483647;
    int INT_MIN = -2147483648;

    long long range = (long long)INT_MAX - (long long)INT_MIN + 1;
    int randomNumber = (int)(((long long)rand() * range) / (INT_MAX + 1) + INT_MIN);

    return randomNumber;
}

void insert_item(int item){
    buffer[index_place_libre] = item;
    index_place_libre++;
    for (int i=0; i<10000; i++);  // simule utilisation du cpu
}

void delete_item(){
    index_place_libre--;
    for (int i=0; i<10000; i++);  // simule utilisation du cpu
}

void* producer(void* id) {
    int item;
    while (1) {
        item = randomInt();
        wait_sem(&empty);
        lock_mut(&mutex);

        if (todo <= 0) {
            unlock_mut(&mutex);
            post_sem(&full);
            break;
        }

        //printf("thread[%d]: add\n", *(int*)id);
        insert_item(item);
        todo--;

        unlock_mut(&mutex);
        post_sem(&full);
    }
    return NULL;
}

void* consumer(void* id) {
    while (1) {
        wait_sem(&full);
        lock_mut(&mutex);

        if (toeat <= 0) {
            unlock_mut(&mutex);
            post_sem(&empty);
            break;
        }

        //printf("thread[%d]: supp\n", *(int*)id);
        delete_item();
        toeat--;

        unlock_mut(&mutex);
        post_sem(&empty);
    }
    return NULL;
}

int main(int argc, const char* argv[]) {  // argv[1] = nombre de prod, argv[2] = nombre de cons; 
    init_mut(&mutex);
    init_sem(&empty, N);
    init_sem(&full, 0);
    int NP;
    int NC;
    if (argc == 3){
        NP = atoi(argv[1]);  // define number of prod
        NC = atoi(argv[2]);  // define number of cuns
    }
    else return -1; 

    // allocates memory for prod/cons, idProd/idCons
    prod = (pthread_t *) malloc(NP * sizeof(pthread_t));
    cons = (pthread_t *) malloc(NC * sizeof(pthread_t));
    IdProd = (int *) malloc(NP * sizeof(int));
    IdCons = (int *) malloc(NC * sizeof(int));
    
    int err;
    for (size_t i = 0; i < NP; i++){
        IdProd[i] = i;
        err = pthread_create(&(prod[i]), NULL, &producer, &(IdProd[i]));  // init the threads (philosopher)
        if(err!=0) {
            printf("Error: %d", -2);
            return -2;
        }
        IdCons[i] = i;
        err = pthread_create(&(cons[i]), NULL, &consumer, &(IdCons[i]));  // init the threads (philosopher)
        if(err!=0) {
            printf("Error: %d\n", -3);
            return -3;
        }
    }

    for (int i=0; i< NP; i++) {
        err = pthread_join(prod[i], NULL);  // wait_sem threads (philosopher)
        if(err!=0) {
            printf("Error: %d\n", -4);
            return -4;
        }

        err = pthread_join(cons[i], NULL);  // wait_sem threads (philosopher)
        if(err!=0) {
            printf("Error: %d\n", -5);
            return -5;
        }
    }


    err = destroy_mut(&(mutex));
    if (err != 0) {
        printf("Error: %d\n", err);
        return -6;
    }

    destroy_sem(&full);
    destroy_sem(&empty);

    free(prod);
    free(cons);
    free(IdProd);
    free(IdCons);

    return 0;
}