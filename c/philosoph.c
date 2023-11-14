#include <pthread.h>                   // message a arthur, ceci est la version qui block car ces idiots de philosophes prenent stupidement la fourchette gauche en premier
#include <stdio.h>                     // CEPENDANT, je finirais demain, je sais comment faire (j'espere) mais j'ai faim
#include <stdlib.h>                    // normalement ici soit t'as eu de la chance et le code finit, soit ils tiennent tous la baguette gauche comme des clochards
#include <stdbool.h>                   // une grande partie c'est des exemples des slides du cours 6, zou-bi
#include <unistd.h>
 
int PHILOSOPHES;                        // nombre de philosophe

pthread_t* phil;                        // tableau de philosophe (array of threads)
pthread_mutex_t* baguette;              // tableau de baguette (array of mutex)
int* Id;

void mange(int id) {printf("Philosophe [%d] mange\n",id);}                      // simule un repas de 0 secondes

void* philosopheNStartCycle(void* n){ 
        int *id=(int *) n;
        int left = *id;
        int right;
        if (PHILOSOPHES == 1) right = 1;
        else right = (left + 1) % PHILOSOPHES;
              
    for ( size_t i = 0; i < 10000000; i++){                                       
        printf("Philosophe [%d] pense\n",*id);                                  // pense
        if (left < right){
            pthread_mutex_lock(&baguette[left]);                                    // prend baguette gauche
            printf("Philosophe [%d] possède baguette gauche [%d]\n",*id,left);
            pthread_mutex_lock(&baguette[right]);                                   // prend baguette droite
            printf("Philosophe [%d] possède baguette droite [%d]\n",*id,right);
            mange(*id);                                                             // mange
            pthread_mutex_unlock(&baguette[left]);                                  // repose la baguette de gauche
            printf("Philosophe [%d] a libéré baguette gauche [%d]\n",*id,left);
            pthread_mutex_unlock(&baguette[right]);                                 // repose la baguette de droite
            printf("Philosophe [%d] a libéré baguette droite [%d]\n",*id,right);
        }   
        else{
            pthread_mutex_lock(&baguette[right]);                                    // prend baguette gauche
            printf("Philosophe [%d] possède baguette droite [%d]\n",*id,right);
            pthread_mutex_lock(&baguette[left]);                                   // prend baguette droite
            printf("Philosophe [%d] possède baguette gauche [%d]\n",*id,left);
            mange(*id);                                                             // mange
            pthread_mutex_unlock(&baguette[right]);                                  // repose la baguette de gauche
            printf("Philosophe [%d] a libéré baguette right [%d]\n",*id,right);
            pthread_mutex_unlock(&baguette[left]);                                 // repose la baguette de droite
            printf("Philosophe [%d] a libéré baguette left [%d]\n",*id,left);
        } 
    }
}

int main(int argc, const char* argv[]) { // argv[0] = ./comp,  argv[1] = nombre de philosophe (pas encore implémenté)
    int err;

    if (argc == 2) {PHILOSOPHES = atoi(argv[1]);} else return -1;               // définit le nombre de philosophe a table

    // Alloue memoire pour philosophe et baguette
    phil = (pthread_t *)malloc(PHILOSOPHES * sizeof(pthread_t));

    if (PHILOSOPHES > 1){
    baguette = (pthread_mutex_t *)malloc(PHILOSOPHES * sizeof(pthread_mutex_t));
    Id = (int *)malloc(PHILOSOPHES * sizeof(int));
    }
    else{  // si 1 philosophe il y a deux baguettes
        baguette = (pthread_mutex_t *)malloc((PHILOSOPHES+1) * sizeof(pthread_mutex_t));
        Id = (int *)malloc((PHILOSOPHES+1) * sizeof(int));
    }

    // init
    for (size_t i = 0; i < PHILOSOPHES; i++){

        Id[i] = i;                                                              // init les Id

        err = pthread_mutex_init( &baguette[i], NULL);                          // init les mutex (baguettes)
        if(err!=0) return -2;

        err = pthread_create(&(phil[i]), NULL, &philosopheNStartCycle, &(Id[i]));   // init les threads (philosophes)
        if(err!=0)return -3;
    }

    for(int i=0;i< PHILOSOPHES;i++) {

        err = pthread_join(phil[i],NULL);                                       // attend les threads (philosophes)
        if(err!=0) return -4;

        err = pthread_mutex_destroy(&(baguette[i]));                              // détruit tt les baguettes (pas tres écolo)
        if(err!=0) return -5;
    }

    return 1;    
}