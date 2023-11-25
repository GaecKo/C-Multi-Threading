#ifndef LECT_WRITER
#define LECT_WRITER

#include <pthread.h> 
#include <stdio.h>  
#include <stdlib.h>    
#include <stdbool.h>    
#include <unistd.h>
#include <semaphore.h>

void read_data();
void write_data();

void* reader();
void* writer();

int main(int argc, const char* argv[]);

// Global var
pthread_t* readers;
pthread_t* writers;

pthread_mutex_t mwc; // mutex for write count
int write_count;

pthread_mutex_t z; 
pthread_mutex_t mrc; // mutex for read count
int read_count;

int nb_readers;
int nb_writers;

#endif