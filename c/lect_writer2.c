#include "include/lect_writer.h"
#include "include/sem.h"

// Global var
pthread_t* readers;
pthread_t* writers;

sem rsem; // Access to 'DB'
sem wsem;  // max 1 writer at once  

pthread_mutex_t mwc; // mutex for write count
int write_count;

pthread_mutex_t z; 
pthread_mutex_t mrc; // mutex for read count
int read_count;

int nb_readers;
int nb_writers;


void read_data() {
    for (int i=0; i<10000; i++);
}

void write_data() {
    for (int i=0; i<10000; i++);
}

// 2560
void* reader() {
    // reader method. Reads carefully while making sure data is 
    // synchronised / used by multiple threads properly
     int iter = 2560 / nb_readers;

    for (int i = 0; i < iter; i++) {
        pthread_mutex_lock(&z);
        wait(&rsem);

        pthread_mutex_lock(&mrc);
        read_count++;

        if (read_count == 1) {
            wait(&wsem);
        }

        pthread_mutex_unlock(&mrc);
        post(&rsem);
        pthread_mutex_unlock(&z);

        read_data();

        pthread_mutex_lock(&mrc);
        read_count--;

        if (read_count == 0) {
            post(&wsem);
        }
        pthread_mutex_unlock(&mrc);
    }

    return (void* ) NULL;
}

// 640 
void* writer() {
    // Writer method. Writes carefully while making sure data is 
    // synchronised / used by multiple threads properly
    int iter = 640 / nb_writers;
    for (int i = 0; i < iter; i++) {
        
        pthread_mutex_lock(&mwc);
        // Critical section

        write_count++;
        if (write_count == 1) {
            wait(&rsem);
        }
        pthread_mutex_unlock(&mwc);

        wait(&wsem);
        write_data();
        post(&wsem);

        pthread_mutex_lock(&mwc);
        // Critical section

        write_count--;
        if (write_count == 0) {
            post(&rsem);
        }
        pthread_mutex_unlock(&mwc);

    }

    return (void *) NULL;
}

int main(int argc, const char* argv[]) {

    int err;    
    
    // read initialisation:
    err = init(&rsem, 1);
    if (err != 0) return -1;
    
    read_count = 0;
    
    err = pthread_mutex_init(&mrc, NULL); // mutex for read count
    if (err != 0) return -2;
    
    // write initialisation
    err = init(&wsem, 1);
    if (err != 0) return -1;
    
    write_count = 0;
    
    
    err = pthread_mutex_init(&mwc, NULL); // mutex for write count
    if (err != 0) return -2;
    
    err = pthread_mutex_init(&z, NULL); 
    if (err != 0) return -2;
    
    if (argc != 3) {
        printf("\nWrong number of arguments, should be: ./lect-writer nb_readers nb_writers\n");
        return -3;
    }

    nb_readers = atoi(argv[1]);
    nb_writers = atoi(argv[2]);

    
    // create array of threads
    readers = (pthread_t *) malloc(nb_readers * sizeof(pthread_t));
    writers = (pthread_t *) malloc(nb_writers * sizeof(pthread_t));


    if (readers == NULL || writers == NULL) return -3;
    

    if (nb_readers == nb_writers) {
        // create step by step 1 reader and one writer
        for (int t_i = 0; t_i < nb_readers; t_i++) {

            err = pthread_create(&(writers[t_i]), NULL, &writer, NULL);
            if (err != 0) return -4;
            
            err = pthread_create(&(readers[t_i]), NULL, &reader, NULL);
            if (err != 0) return -4;

        }  
    } else {
        // firstly create all writers and then all readers (not as good)
        for (int t_i = 0; t_i < nb_writers; t_i++) {

            err = pthread_create(&(writers[t_i]), NULL, &writer, NULL);
            if (err != 0) return -4;
        }
        for (int t_i = 0; t_i < nb_readers; t_i++) {

            err = pthread_create(&(readers[t_i]), NULL, &reader, NULL);
            if (err != 0) return -4;
        } 
    }

    
    // Join threads
    for (int t_i = 0; t_i < nb_writers; t_i++) {

        err = pthread_join(writers[t_i], NULL);
        if (err != 0) return -5;
    }
    for (int t_i = 0; t_i < nb_readers; t_i++) {

        err = pthread_join(readers[t_i], NULL);
        if (err != 0) return -5;
    }

    // free malloc (threads lists)
    free(readers);
    free(writers);

    // destroy semaphores
    err = destroy(&rsem);
    if (err != 0) return -6;

    err = destroy(&wsem);
    if (err != 0) return -6;

    // destroy mutex
    err = pthread_mutex_destroy(&mwc);
    if (err != 0) return -7;

    err = pthread_mutex_destroy(&mrc);
    if (err != 0) return -7;

    err = pthread_mutex_destroy(&z);
    if (err != 0) return -7;

    return 0;
}