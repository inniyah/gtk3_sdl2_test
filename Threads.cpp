#include "Threads.h"

#include <cstdio>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

const pthread_mutex_t  Mutex::Initializer = PTHREAD_MUTEX_INITIALIZER;
const pthread_mutex_t  RecursiveMutex::Initializer = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
const pthread_cond_t   Condition::Initializer = PTHREAD_COND_INITIALIZER;
const pthread_rwlock_t RWLock::Initializer = PTHREAD_RWLOCK_INITIALIZER;
