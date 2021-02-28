#include "lock.h"

#if defined(DETECT_DEADLOCKS)
    
struct InfoLock
{
    int line, type_lock;
    string function_name;
};

map<pthread_rwlock_t* , vector<InfoLock> > list_locked_old;

pthread_rwlock_t __lock;
    
#endif

void __LOCK_INIT()
{
    pthread_rwlock_init(&__lock, NULL);
}

int __LOCK_READ(pthread_rwlock_t *lock, int line_in_call_source, const char *function_name)
{
    int res;
    
#if defined(DETECT_DEADLOCKS)
    {
        time_t seconds = time(NULL);
        time_t wait_time, reported_wait = 0;
        do 
        {
            res = pthread_rwlock_tryrdlock(lock);
            if (res == EBUSY) 
            {
                wait_time = time(NULL) - seconds;
                if( wait_time > reported_wait && (wait_time % 5) == 0 ) 
                {
                    printf(">> Deadlock READ:\t line %d waited %d in \"%s\"\n", line_in_call_source, (int)wait_time, function_name);
                    
                    pthread_rwlock_rdlock(&__lock);
                    
                    map<pthread_rwlock_t* , vector<InfoLock> >::iterator _it = list_locked_old.find( lock );
                    if( _it != list_locked_old.end() )
                    {
                        printf("old lock >>\n");
                        
                        vector<InfoLock> &list = _it->second;
                        
                        for(int k = 0; k < list.size(); k++)
                        {
                            printf("[%d] line: %d [%s] type: %d\n", k, list[k].line, list[k].function_name.c_str(), list[k].type_lock);
                        }
                    }
                    
                    pthread_rwlock_unlock(&__lock);
                    
#if defined(NEED_EXIT_IN_DEADLOCKS)
                    exit( EXIT_FAILURE );              
#endif
                    
                    reported_wait = wait_time;
                }
                
                usleep(200);
            }
            
        } 
        while (res == EBUSY);
        
        InfoLock il;
        il.function_name = function_name;
        il.line          = line_in_call_source;
        il.type_lock     = INFO_LOCK_READ;
        
        pthread_rwlock_wrlock(&__lock);
        
        map<pthread_rwlock_t* , vector<InfoLock> >::iterator _it = list_locked_old.find( lock );
        if( _it != list_locked_old.end() )
        {
            list_locked_old[ lock ].push_back(il);
        }
        else
        {
            vector<InfoLock> value;
            value.push_back(il);

            list_locked_old[ lock ] = value;
            
            //list_locked_old.insert( std::make_pair( lock, vector<InfoLock>( il ) ) );
        }
        
        pthread_rwlock_unlock(&__lock);
    }
#else
    res = pthread_rwlock_rdlock(lock);
#endif
    
    return res;
}

int __LOCK_WRITE(pthread_rwlock_t *lock, int line_in_call_source, const char *function_name)
{
    int res;
    
#if defined(DETECT_DEADLOCKS)
    {
        time_t seconds = time(NULL);
        time_t wait_time, reported_wait = 0;
        do 
        {
            res = pthread_rwlock_trywrlock(lock);
            if (res == EBUSY) 
            {
                wait_time = time(NULL) - seconds;
                if (wait_time > reported_wait && (wait_time % 5) == 0) 
                {
                    printf(">> Deadlock WRITE:\t line %d waited %d in \"%s\"\n", line_in_call_source, (int)wait_time, function_name);
                    
                    pthread_rwlock_rdlock(&__lock);
                    
                    map<pthread_rwlock_t* , vector<InfoLock> >::iterator _it = list_locked_old.find( lock );
                    if( _it != list_locked_old.end() )
                    {
                        printf("old lock >>\n");
                        
                        vector<InfoLock> &list = _it->second;
                        
                        for(int k = 0; k < list.size(); k++)
                        {
                            printf("[%d] line: %d [%s] type: %d\n", k, list[k].line, list[k].function_name.c_str(), list[k].type_lock);
                        }
                    }
                    
                    pthread_rwlock_unlock(&__lock);
                    
#if defined(NEED_EXIT_IN_DEADLOCKS)
                    exit( EXIT_FAILURE );              
#endif
                    reported_wait = wait_time;
                }
                
                usleep(200);
            }
        } 
        while (res == EBUSY);
        
        InfoLock il;
        il.function_name = function_name;
        il.line          = line_in_call_source;
        il.type_lock     = INFO_LOCK_WRITE;
        
        pthread_rwlock_wrlock(&__lock);
        
        map<pthread_rwlock_t* , vector<InfoLock> >::iterator _it = list_locked_old.find( lock );
        if( _it != list_locked_old.end() )
        {
            list_locked_old[ lock ].push_back(il);
        }
        else
        {
            vector<InfoLock> value;
            value.push_back(il);

            list_locked_old[ lock ] = value;
        }
        
        pthread_rwlock_unlock(&__lock);
    }
#else
    res = pthread_rwlock_wrlock(lock);
#endif
    
    return res;
}

int __LOCK_FREE(pthread_rwlock_t *lock, int line_in_call_source, const char *function_name)
{
    int res = pthread_rwlock_unlock(lock);
    
#if defined(DETECT_DEADLOCKS)
    
    if (res)
    {
        printf(">> Error FREE:\t line %d in \"%s\"\n", line_in_call_source, function_name);
    }
    
    pthread_rwlock_wrlock(&__lock);
    
    list_locked_old.erase( lock );
    
    pthread_rwlock_unlock(&__lock);
    
#endif
    
    return res;
}