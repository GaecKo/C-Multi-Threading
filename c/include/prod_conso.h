#ifndef PROD_CONSO
#define PROD_CONSO

#include <pthread.h> 
#include <stdio.h>  
#include <stdlib.h>    
#include <stdbool.h>    
#include <unistd.h>
#include <semaphore.h>

// functions
int randomInt();
void insert_item(int item);
void delete_item();
void* producer();
void* consumer();
int main(int argc, const char* argv[]);

#endif