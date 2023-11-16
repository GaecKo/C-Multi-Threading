#include "header/lect_writer.h"

pthread_t* readers;
pthread_t* writers;

sem_t rsem; // Access to 'DB'
sem_t wsem;  // max 1 writer at once

pthread_mutex_t mwc; // mutex for write count
int write_count;

pthread_mutex_t z; 
pthread_mutex_t mrc; // mutex for read count
int read_count;


void read_data() {
    printf("hello");
    for (int i=0; i<10000; i++);
}

void write_data() {
    printf("hye");
    for (int i=0; i<10000; i++);
}

// 2560
void* reader() {
    for (int i = 0; i < 2560; i++) {
        pthread_mutex_lock(&z);
        sem_wait(&rsem);

        pthread_mutex_lock(&mrc);
        read_count++;

        if (read_count == 1) {
            sem_wait(&wsem);
        }

        pthread_mutex_unlock(&mrc);
        sem_post(&rsem);
        pthread_mutex_unlock(&z);

        read_data();

        pthread_mutex_lock(&mrc);
        read_count++;

        if (read_count == 0) {
            sem_post(&wsem);
        }
        pthread_mutex_unlock(&mrc);
    }

    return (void* ) NULL;
}

// 640 
void* writer() {

    for (int i = 0; i < 640; i++) {
        
        pthread_mutex_lock(&mwc);
        // Critical section

        write_count++;
        if (write_count == 1) {
            sem_wait(&rsem);
        }
        pthread_mutex_unlock(&mwc);

        sem_wait(&wsem);
        write_data();
        sem_post(&wsem);

        pthread_mutex_lock(&mwc);
        // Critical section

        write_count--;
        if (write_count == 0) {
            sem_post(&rsem);
        }
        pthread_mutex_unlock(&mwc);

    }

    return (void *) NULL;
}

int main(int argc, const char* argv[]) {
    
    int err;
    
    // read initialisation:
    err = sem_init(&rsem, 0, 0);
    if (err != 0) return -1;
    read_count = 0;
    
    err = pthread_mutex_init(&mrc, NULL); // mutex for read count
    if (err != 0) return -2;

    

    // write initialisation
    err = sem_init(&wsem, 0, 0);
    if (err != 0) {
        printf("\nError: %d\n", err);
        return -1;
    } 
    write_count = 0;
    

    err = pthread_mutex_init(&mwc, NULL); // mutex for write count
    if (err != 0) return -2;
    err = pthread_mutex_init(&z, NULL); 
    if (err != 0) return -2;
    
    int nb_readers = atoi(argv[1]);
    int nb_writers = atoi(argv[2]);

    

    readers = (pthread_t *) malloc(nb_readers * sizeof(pthread_t));
    writers = (pthread_t *) malloc(nb_readers * sizeof(pthread_t));

    if (readers == NULL || writers == NULL) {
        return -3;
    }

    if (nb_readers == nb_writers) {
        // create step by step 1 reader and one writer
        for (int t_i; t_i < nb_readers; t_i++) {
            err = pthread_create(&(writers[t_i]), NULL, &writer, NULL);
            if (err != 0) return -4;
            err = pthread_create(&(readers[t_i]), NULL, &reader, NULL);
            if (err != 0) return -4;

        }  
    } else {
        // firstly create all writers and then all readers (not as good)
        for (int t_i; t_i < nb_writers; t_i++) {
            err = pthread_create(&(writers[t_i]), NULL, &writer, NULL);
            if (err != 0) return -4;
        }
        for (int t_i; t_i < nb_readers; t_i++) {
            err = pthread_create(&(readers[t_i]), NULL, &reader, NULL);
            if (err != 0) return -4;
        } 
    }

    
    // Join threads
    for (int t_i; t_i < nb_writers; t_i++) {
        err = pthread_join(writers[t_i], NULL);
        if (err != 0) return -5;
    }
    for (int t_i; t_i < nb_readers; t_i++) {
        err = pthread_join(readers[t_i], NULL);
        if (err != 0) return -5;
    }

    // destroy semaphores
    err = sem_destroy(&rsem);
    if (err != 0) return -6;
    sem_destroy(&wsem);
    if (err != 0) return -6;

    // destroy mutex
    err = pthread_mutex_destroy(&mwc);
    if (err != 0) return -7;

    err = pthread_mutex_destroy(&mrc);
    if (err != 0) return -7;

    pthread_mutex_destroy(&z);
    if (err != 0) return -7;

}