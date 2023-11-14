#ifndef PHILOSOPHE
#define PHILOSOPHE

#include <pthread.h> 
#include <stdio.h>  
#include <stdlib.h>    
#include <stdbool.h>    
#include <unistd.h>

// Gloval Var
int PHILOSOPHES;                        // number of philosopher

pthread_t* phil;                        // array of philosopher (array of threads)
pthread_mutex_t* baguette;              // array of fork (array of mutex)
int* Id;

// Functions
void* philosopheNStartCycle(void* n);
void mange(int id);
int main(int argc, const char* argv[]);

#endif 