#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[])	{
    int start_num, end_num;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <start_number> <end_number>\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1], "%i", &start_num);
    sscanf(argv[2], "%i", &end_num);

    /* Calculations */
    for(;start_num < end_num; start_num++)  {   
        int res = isprime(start_num);

        if(res == 1) 
            printf("Number %i IS prime!\n", start_num);
	else
	    printf("Number %i NOT prime!\n", start_num);
    }

}
