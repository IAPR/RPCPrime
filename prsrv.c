/*********************************************************************/
/* dateproc.c - remote procedures; called by server stub */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef MINGW_BUILD
        #include <rpc.h>
#else
        #include <rpc/rpc.h>
#endif

#include "prime.h"

/* return the binary date and time */
/* In Linux: long * bindate_1_svc(void* arg1, struct svc_req *arg2) {
*/

/* In Dec Unix: long * bindate_1() {
*/

int * isprime_1_svc(int* arg1, struct svc_req *arg2)    {
    int num = *arg1;
    int start_check = (num/2)+1;

    static int prime = 1;
    static int notprime = 0;

    if(num == 2)
        return &prime;
    
    while( start_check > 1 )    {
        if( (num % start_check) == 0 )
            return &notprime;
        else
            start_check--;
    }
    return &prime;
}
