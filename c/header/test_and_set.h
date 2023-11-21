#ifndef TEST_AND_SET
#define TEST_AND_SET

#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <stdbool.h>

// functions
static inline void lock();
static inline void unlock();
void* travail(void* n);
int main(int argc, const char* argv[]);
#endif