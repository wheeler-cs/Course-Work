#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define ARRAY_LEN 16

void populateArray(int array[ARRAY_LEN])
{
    int i;
    for(i = 0; i < ARRAY_LEN; i++)
    {
        array[i] = (rand() % 10) + 1;
    }
}

int main(int argc, char ** argv)
{
    int i,
        addendsA[ARRAY_LEN],
        addendsB[ARRAY_LEN],
        sums[ARRAY_LEN];
    
    srand(time(NULL));
    populateArray(addendsA);
    populateArray(addendsB);

    #pragma omp parallel for num_threads(4)
    for(i = 0; i < ARRAY_LEN; i++)
    {
        sums[i] = addendsA[i] + addendsB[i];
    }

    for(i = 0; i < ARRAY_LEN; i++)
    {
        printf("sums[%d]: %d\n", i, sums[i]);
    }

    fflush(stdout);
    return 0;
}
