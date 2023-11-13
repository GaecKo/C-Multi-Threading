#include <pthread.h>                   // message a arthur, ceci est la version qui block car ces idiots de philosophes prenent stupidement la fourchette gauche en premier
#include <stdio.h>                     // CEPENDANT, je finirais demain, je sais comment faire (j'espere) mais j'ai faim
#include <stdlib.h>                    // normalement ici soit t'as eu de la chance et le code finit, soit ils tiennent tous la baguette gauche comme des clochards
#include <stdbool.h>                   // une grande partie c'est des exemples des slides du cours 6, zou-bi
#include <unistd.h>

#define PHILOSOPHES 3                    // nombre de philosophe

pthread_t phil[PHILOSOPHES];             // les philosophes
pthread_mutex_t baguette[PHILOSOPHES];   // les baguettes (représentéent par des mutex), attention au cas ou 1 philosophe => 2 baguettes
int Id[PHILOSOPHES];

void mange(int id) {                     // mange pendant un temps random
printf("Philosophe [%d] mange\n",id);
    for(int i=0;i< 10; i++) {
    // philosophe mange
    }
}

void* philosopheNStartCycle(void* n){    // le philosophe N va exécuter 25 cycles (manger-penser)
    for ( size_t i = 0; i < 1000; i++){ // chacun mange 25 fois
        int *id=(int *) n;
        int left = *id;
        int right = (left + 1) % PHILOSOPHES;   // permet d'afficher

        printf("Philosophe [%d] pense\n",*id);                                  // pense
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
}

int main(int argc, const char* argv[]) { // argv[0] = ./comp,  argv[1] = nombre de philosophe (pas encore implémenté)
    int err;

    // init
    for (size_t i = 0; i < PHILOSOPHES; i++){

        Id[i] = i;                                                              // init les Id

        err = pthread_mutex_init( &baguette[i], NULL);                          // init les mutex (baguettes)
        if(err!=0) return -1;

        err = pthread_create(&(phil[i]), NULL, &philosopheNStartCycle, &(Id[i]));   // init les threads (philosophes)
        if(err!=0)return -2;
    }

    for(int i=0;i< PHILOSOPHES;i++) {

        err = pthread_join(phil[i],NULL);                                       // attend les threads (philosophes)
        if(err!=0) return -3;

        err = pthread_mutex_destroy(&(baguette[i]));                              // détruit tt les baguettes (pas tres écolo)
        if(err!=0) return -4;
    }

    return 1;    
}