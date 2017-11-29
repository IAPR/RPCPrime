#include <rpc/rpc.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "prime.h"

CLIENT *cl1, *cl2, *cl3, *cl4, *cl5, *cl6;
char *hosts[] = {
	"127.0.0.1", 
	"127.0.0.1", 
    "127.0.0.1", 
    "127.0.0.1",
    "127.0.0.1",
    "127.0.0.1"
};
int hostnum = 6;
int running_threads = 0;

void CheckPrime( int num )    {
    int n = num % hostnum;
    
    int **res;
    res = malloc( sizeof(**res));

    //printf("Started thread for %i, %i\n", num, num);
    
    if( n == 0)
        *res = isprime_1(&num, cl1);
    else if( n == 1)
        *res = isprime_1(&num, cl2);
    else if( n == 2)
        *res = isprime_1(&num, cl3);
    else if( n == 3)
        *res = isprime_1(&num, cl4);
    else if( n == 4)
        *res = isprime_1(&num, cl5);
    else if( n == 5)
        *res = isprime_1(&num, cl6);

    //printf("NUM %i **RES %i *RES %i RES %i\n", num, **res, *res, res);
    
    if(**res == 1) 
        printf("Number %i IS prime!\n", num);
    else if(**res == 0)
        printf("Number %i NOT prime!\n", num);
    else
        printf("F**k, something failed (got the pun?)\n");
    
    /* Exit thread */
    free(res);
    running_threads--;
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

	// First Client
    if ((cl1 = clnt_create(hosts[0], PRIMECALC, PVERSION, "udp")) == NULL) {
        /* couldn't establish connection with server */
        printf("can't establish connection with host %s\n", hosts[0]);
        exit(2);
    }
	// Second Client
	if ((cl2 = clnt_create(hosts[1], PRIMECALC, PVERSION, "udp")) == NULL) {
        /* couldn't establish connection with server */
        printf("can't establish connection with host %s\n",hosts[1]);
        exit(2);
    }
    if ((cl3 = clnt_create(hosts[2], PRIMECALC, PVERSION, "udp")) == NULL) {
        /* couldn't establish connection with server */
        printf("can't establish connection with host %s\n", hosts[2]);
        exit(2);
    }
    if ((cl4 = clnt_create(hosts[3], PRIMECALC, PVERSION, "udp")) == NULL) {
        /* couldn't establish connection with server */
        printf("can't establish connection with host %s\n", hosts[3]);
        exit(2);
    }
    if ((cl5 = clnt_create(hosts[4], PRIMECALC, PVERSION, "udp")) == NULL) {
        /* couldn't establish connection with server */
        printf("can't establish connection with host %s\n", hosts[4]);
        exit(2);
    }
    if ((cl6 = clnt_create(hosts[5], PRIMECALC, PVERSION, "udp")) == NULL) {
        /* couldn't establish connection with server */
        printf("can't establish connection with host %s\n", hosts[5]);
        exit(2);
    }

    printf("RPC is working correctly, starting calculations\n");

    /* Calculations */
    for(;start_num < end_num; start_num++)  {   
        if(1 > 0)  {
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            
            pthread_t thread;
            pthread_create(
                    &thread,     // thread to use
                    &attr,          // TODO: Add attributes
                    CheckPrime, start_num
            );
            pthread_attr_destroy(&attr);
            
            running_threads++;
            
            //printf("THREAD %i\n", start_num);
            //sleep(.05);
        }
    }

    while(running_threads > 0)
        sleep(.01);
    
    
    clnt_destroy(cl1); /* done with handle */
    clnt_destroy(cl2); /* done with handle */
    clnt_destroy(cl3); /* done with handle */
    clnt_destroy(cl4); /* done with handle */
    clnt_destroy(cl5); /* done with handle */
    clnt_destroy(cl6); /* done with handle */
    return 0;
}
