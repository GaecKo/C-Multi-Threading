#include "header/prod_conso.h"
#include "header/sem.h"

#define N 8 // places dans le buffer

int buffer[N];
pthread_mutex_t mutex;
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
        wait(&empty);
        pthread_mutex_lock(&mutex);

        if (todo <= 0) {
            pthread_mutex_unlock(&mutex);
            post(&full);
            break;
        }

        //printf("thread[%d]: add\n", *(int*)id);
        insert_item(item);
        todo--;

        pthread_mutex_unlock(&mutex);
        post(&full);
    }
    return NULL;
}

void* consumer(void* id) {
    while (1) {
        wait(&full);
        pthread_mutex_lock(&mutex);

        if (toeat <= 0) {
            pthread_mutex_unlock(&mutex);
            post(&empty);
            break;
        }

        //printf("thread[%d]: supp\n", *(int*)id);
        delete_item();
        toeat--;

        pthread_mutex_unlock(&mutex);
        post(&empty);
    }
    return NULL;
}

int main(int argc, const char* argv[]) {  // argv[1] = nombre de prod, argv[2] = nombre de cons; 
    pthread_mutex_init(&mutex, NULL);
    init(&empty, N);
    init(&full, 0);
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
        err = pthread_join(prod[i], NULL);  // wait threads (philosopher)
        if(err!=0) {
            printf("Error: %d\n", -4);
            return -4;
        }

        err = pthread_join(cons[i], NULL);  // wait threads (philosopher)
        if(err!=0) {
            printf("Error: %d\n", -5);
            return -5;
        }
    }


    err = pthread_mutex_destroy(&(mutex));
    if (err != 0) {
        printf("Error: %d\n", err);
        return -6;
    }

    destroy(&full);
    destroy(&empty);

    free(prod);
    free(cons);
    free(IdProd);
    free(IdCons);

    return 0;
}