## Pseudo Code reader / writer
2 semaphores
1. `rseam` -> accès db
2. `wsem` -> 1 seul écrivain à la fois

### Écrivain :

```c
while (true) {
    ...;
}
lock(mwc) // change value of w_count, mwc is a mutex
wc ++;
f(wc == 1) {
    wait(rsem);
}
unlock(mwc); 
wait(wsem);
write();
post(wsem);
lock(mwc);
wc -- ;
if (wc == 0) {
    post(rsem);
}
unlock(mwc);
```
### Lecteur:

```c
while (true) {
    lock(z); // without it, the semaphore could all be taken by readers and never by writers
    wait(rsem); // wait access to "db"
    lock(mrc); // mutex for reader counter
    rc ++; // nb reader increase
    if (rc ==1) {
        wait(wsem) // disable access to write for writers
    }
    unlock(mrc);
    post(rsem);
    unlock(z);
    read();
    lock(mrc);
    rc --;
    if (rc == 0) {
        post(wsem); // authorize writers to write
    }
    unlock(mrc);
}

```


```c
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <semaphore.h>
#include <stdbool.h>
// PC:Pseudo Code du tp


sem_t db;

//sem_init(&db, 0, 1);

/* Writer 
640 écritures*/

void writer(void){

    while(true){
        think_up_data();

        pthread_mutex_lock(&mutex_writecount);
            //section critique - writecount
            writecount = writecount+1;
            if(writecount == 1){
                //premier writer arrive
                sem_wait(&rsem);
            }
        pthread_mutex_unlock(&mutex_writecount);

        sem_wait(&wsem);
            //section critique, un seul write à la fois
            write_database();
        sem_post(&wsem);

        pthread_mutex_lock(&mutex_writecount);
            //section critique - writecount
            writecount = writecount-1;
            if(writecount == 0){
                //départ du dernier writer
                sem_post(&rsem);
            }
        pthread_mutex_unlock(&mutex_writecount);
    }

}


/* Reader 
2560 lectures*/

void reader(void){

    while(true){
        pthread_mutex_lock(&z);
        // exclusion mutuelle, un seul reader en attente sur rien
        sem_wait(&rsem);

        pthread_mutex_lock(&mutex_readcount);
            //exclusion mutuelle, readcount
            readcount = readcount + 1;
            if(readcount == 1){
                //arrivée du premier reader
                sem_wait(&wsem);
            }
        pthread_mutex_unlock(&mutex_readcount);
        sem_post(&rsem); // libération prochain reader/writer
        pthread_mutex_unlock(&z);

        read_database();

        pthread_mutex_lock(&mutex_readcount);
        // exclusion mutuelle, readcount
            readcount = readcount - 1;
            if(readcount == 0){
                // départ du dernier reader
                sem_post(&wsem);
            }
        pthread_mutex_unlock(&mutex_readcount);
        use_data_read();
    }
}
```
