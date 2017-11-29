#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 4

pthread_mutex_t running_mutex;
int running_threads = 0;

int isprime(int num)    {
    int start_check = (num/2)+1;

    static int prime = 1;
    static int notprime = 0;

    while( start_check > 1 )    {
        if( (num % start_check) == 0 )
            return notprime;
        else
            start_check--;
    }
    return prime;
}

void CheckPrime( int num )    {    
    int res;
    
    pthread_mutex_lock(&running_mutex);
    running_threads++;
    pthread_mutex_unlock(&running_mutex);

    res = isprime(num);

    //printf("NUM %i **RES %i *RES %i RES %i\n", num, **res, *res, res);
    
    if(res == 1) 
        printf("%i IS prime!\n", num);
    /*
     * else if(res == 0)
     *   printf("Number %i NOT prime!\n", num);
    */
    
    pthread_mutex_lock(&running_mutex);
    running_threads--;
    pthread_mutex_unlock(&running_mutex);
    pthread_exit(NULL);
}   

int main(int argc, char *argv[]) {
    int start_num, end_num;
    if (argc != 3) {
        fprintf(stderr, "usage: %s <start_number> <end_number>\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1], "%i", &start_num);
    sscanf(argv[2], "%i", &end_num);

    /* Sanitize input */
    printf("Start: %d\tEnd: %d\n", start_num, end_num);
    if(start_num <= 1 || start_num > end_num || end_num <= 1)   {
        perror("ERROR: Invalid number range. Aborting\n");
        exit(4);
    }
    
    pthread_mutex_init(&running_mutex, NULL);

    /* Calculations */
    for(;start_num < end_num; start_num++)  {
        
        while( running_threads > MAX_THREADS ) 
            sleep(.1);
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        
        pthread_t thread;
        pthread_create(
            &thread,     // thread to use
            &attr,          // TODO: Add attributes
            CheckPrime, start_num
        );
        pthread_attr_destroy(&attr);
    }

    while(running_threads > 0)
        printf("Running threads: %i\n", running_threads);
        sleep(.1);

    return 0;
}
