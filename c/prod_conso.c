#include "header/prod_conso.h"

#define N 8 // places dans le buffer
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m" 

int buffer[N];
pthread_mutex_t mutex;
sem_t empty; // compte les places vides
sem_t full;  // compte les places occupées

int* IdProd;
int* IdCons;

pthread_t* prod; // liste des producteur (threads)
pthread_t* cons; // liste des consomateur (threads)

int todo = 20;  // nbr d'item a faire
int toeat = 20;  // nbr d'item a manger

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
    printf("%s buffer[%d] = %d\n", GREEN, index_place_libre, item);
    for (int i=0; i<10000; i++);  // simule utilisation du cpu
}

void delete_item(){
    printf("%s buffer[%d] : SUPPRIMÉ\n", RED, index_place_libre);
    index_place_libre--;
    for (int i=0; i<10000; i++);  // simule utilisation du cpu
}

void* producer(){
    int item;
    bool continuer = true;
    while(continuer){ // les producteurs tournent jusqua avoir produit 8192 items.
        item = randomInt();
        sem_wait(&empty); // attente d'une place libre
        pthread_mutex_lock(&mutex);
        // section critique

        if (todo > 0){ // juste pour consommer moins d'energie, ils arretent de tourner si il ont produit les 8192 items.
            insert_item(item);
            todo--;
            }
        else continuer = false;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // une place remplie en plus
    }
    return NULL;
}

void* consumer(){
    int item;
    bool continuer = true;
    while(continuer){
        sem_wait(&full); // attente d'une place remplie
        pthread_mutex_lock(&mutex);
        // section critique

        if (toeat > 0){ // juste pour consommer moins d'energie, ils arretent de tourner si il ont mangé les 8192 items.
            delete_item();
            toeat--;
            }
        else continuer = false;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // une place libre en plus
    }
    return NULL;
}

int main(int argc, const char* argv[]) {  // argv[1] = nombre de prod, argv[2] = nombre de cons; 
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, N);
    sem_init(&full, 0 , 0);
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
    
    printf("init done\n");
    int err;
    for (size_t i = 0; i < NP; i++){
        IdProd[i] = i;
        err = pthread_create(&(prod[i]), NULL, &producer, &(IdProd[i]));  // init the threads (philosopher)
        if(err!=0) {
            printf("Error: %d", -2);
            return -2;
        }
    }
    for (size_t i = 0; i < NC; i++){
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
    }

    for (int i=0; i< NC; i++) {
        err = pthread_join(cons[i], NULL);  // wait threads (philosopher)
        if(err!=0) {
            printf("Error: %d\n", -5);
            return -5;
        }
    }

    printf("%s ok\n", RESET);
    return 1;
}
