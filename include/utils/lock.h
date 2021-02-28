/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lock.h
 * Author: sk
 *
 * Created on September 14, 2019, 11:31 AM
 */

#ifndef LOCK_H
#define LOCK_H

#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define DETECT_DEADLOCKS         1
#define NEED_EXIT_IN_DEADLOCKS   1
    
#define INFO_LOCK_READ    1
#define INFO_LOCK_WRITE   2

void __LOCK_INIT();
int __LOCK_READ(pthread_rwlock_t *lock, int line_in_call_source, const char *function_name);
int __LOCK_WRITE(pthread_rwlock_t *lock, int line_in_call_source, const char *function_name);
int __LOCK_FREE(pthread_rwlock_t *lock, int line_in_call_source, const char *function_name);

#endif /* LOCK_H */

