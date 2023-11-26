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

#endif