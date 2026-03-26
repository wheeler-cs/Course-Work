#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define ARRAY_LEN 8

int main(int argc, char ** argv)
{
    // Variables for operation
    int i,
        sum,
        addends[ARRAY_LEN];

    // Randomly popluate array with values
    srand(time(NULL));
    for(i = 0; i < ARRAY_LEN; i++)
    {
        addends[i] = rand() % 2;
    }

    // Sum values in array
    sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(i = 0; i < ARRAY_LEN; i++)
    {
        sum += addends[i];
    }

    // Print results
    for(i = 0; i < ARRAY_LEN; i++)
    {
        printf("%d ", addends[i]);
    }
    printf("= %d\n", sum);

    // Clean up
    fflush(stdout);
    return 0;
}
