#ifndef PHILOSOPHE
#define PHILOSOPHE

#include <pthread.h> 
#include <stdio.h>  
#include <stdlib.h>    
#include <stdbool.h>    
#include <unistd.h>

// Functions
void* philosopheNStartCycle(void* n);
void mange(int id);
int main(int argc, const char* argv[]);

#endif 