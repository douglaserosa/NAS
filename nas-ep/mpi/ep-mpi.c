/*
 * Copyright (c)2010 Derrell Lipman
 * Parallel Kernel EP: An embarrassingly parallel benchmark
 * cilk implementation
 * gcc ep-cilk.c -fcilkplus -lcilkrts -lm
 */
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "mpi.h"


#define INITIAL_SEED    271828183

// quantidade de threads. é alterada pelo parametro recebido na chamada do programa
int NUM_THREADS = 1;

static double   n;
//static double a = pow(5, 13);
static double a = 1220703125.0;

static double   POW_2_N23; /* 2^-23 */
static double   POW_2_23;  /* 2^23 */
static double   POW_2_N46; /* 2^-46 */
static double   POW_2_46;  /* 2^46 */


#ifndef FALSE
# define        FALSE   (0)
# define        TRUE    (! FALSE)
#endif

/** Structure to provide pairs of random numbers */
typedef struct Pair
{
    double          x;
    double          y;
} Pair;

/**
 * estrutura para armazenar os parametros a serem utilizados nas threads
 */
struct threadStruct {
    int             threadNum;
    double          sumX;
    double          sumY;
    int             results[10];
};

/**
 * Find the maximum of two floating-point numbers.
 *
 * @param a
 *   The first of two numbers to be compared
 *
 * @param b
 *   The second of two numbers to be compared
 *
 * @return
 *   The floor of the maximum of the two parameter values.
 */
int
maximum(double a, double b)
{
    /* Return the integer (truncated) value of the maximum of a and b */
    return a >= b ? a : b;
}


/**
 * Multiple two floating point numbers, modulo 46.
 *
 * @param a
 *   The first of two numbers to be multiplied
 *
 * @param b
 *   The second of two numbers to be multiplied
 *
 * @return
 *   The modulo 46 product of the two parameter values.
 */
double
multiplyModulo46(double a, double b)
{
    static int          bInitialized = FALSE;
    double              a1;
    double              a2;
    double              b1;
    double              b2;
    double              t1;
    double              t2;
    double              t3;
    double              t4;
    double              t5;

    /* Have we initialized our very large and very small numbers? */
    if (! bInitialized)
    {
        /* Nope. Do it now. */
        POW_2_N23 = pow(2, -23);
        POW_2_23  = pow(2,  23);
        POW_2_N46 = pow(2, -46);
        POW_2_46  = pow(2,  46);

        /* Now we're initialized, so we don't need to run that code again. */
        bInitialized = TRUE;
    }

    /* Implementation of the modulo-46 multiplication from the NAS Benchmark */
    a1 = floor(POW_2_N23 * a);
    a2 = a - POW_2_23 * a1;
    b1 = floor(POW_2_N23 * b);
    b2 = b - POW_2_23 * b1;
    t1 = (a1 * b2) + (a2 * b1);
    t2 = floor(POW_2_N23 * t1);
    t3 = t1 - (POW_2_23 * t2);
    t4 = (POW_2_23 * t3) + (a2 * b2);
    t5 = floor(POW_2_N46 * t4);
    
    return t4 - (POW_2_46 * t5);
}


/**
 * Calculate and return the next pseudo-random number.
 * 
 * @return
 *   The next pseudo-random number, as determined from the pre-existing seed.
 */
double
pseudorandom(double *random_seed)
{
    double                      oldS;
    
    
    /* Save the old seed as it's used to calculate the return value */
    oldS = *random_seed;
    
    /* Calculate the next seed */
    *random_seed = multiplyModulo46(a, *random_seed);
    
    /* Calculate the return value based on the old seed */
    return POW_2_N46 * oldS;
}

/**
 * Get the seed for the kth pseudo-random number
 *
 * @param k
 *   The index of the pseudo-random number for which the seed is desired
 *
 * @return
 *   The seed for the random number at the index specified by the parameter.
 */
double
getSeedFor(double k)
{
    int             i;
    int             j;
    double          b;
    double          t;
    int             m;

    m = floor(log2(k)) + 1;
    b = INITIAL_SEED;
    t = a;
    for (i = 1; i <= m; i++)
    {
        j = k / 2;
        if (2 * j != k)
        {
            b = multiplyModulo46(b, t);
        }
        t = multiplyModulo46(t, t);
        k = j;
    }

    return b;
}

/**
 * Get a pair of random numbers, scaled to the range (-1, 1).
 *
 * @return
 *   A pair of pseudo-random numbers, each of which is in the range (-1, 1)
 */
Pair
randomPair(double *random_seed)
{
    Pair            pair;
    
    pair.x = 2 * pseudorandom(random_seed) - 1;
    pair.y = 2 * pseudorandom(random_seed) - 1;
    
    return pair;
}


/**
 * sorteia n/NUM_THREADS numeros aleatorios 
 * @param n [description]
 */
struct threadStruct * epThread (struct threadStruct * params) {
    double   random_seed;
    unsigned long   j;
    Pair            pair;
    double          t;
    double          temp;
    int             maxXY;
    unsigned long             from;
    unsigned long             until;

    /*
     * Gera o primeiro seed para esta thread. Cada laço sorteia um par de numeros
     * aleatorios (ou seja, sorteia 2 numeros).
     * Multiplicados o numero da thread (0,1,2,3,..) pela quantidade de
     * numeros que serão sorteados pelo benchmark divididos pela 
     * quantidade de threads criadas.
     * Esta quantidade deve ser multiplicada por 2 (por causa dos pares de numeros)
     * e somado 1 para pegarmos o primeiro seed que esta thread irá calcular.
     */
    
    from = params->threadNum * (n / NUM_THREADS);
    until = (params->threadNum  + 1) * (n / NUM_THREADS);
    random_seed = getSeedFor(from * 2 + 1);

    for (j = from + 1; j <= until; j++)
    {
        /* Obtain the next pair of random numbers */
        pair = randomPair(&random_seed);
        
        /* Is this pair acceptable? */
        t = (pair.x * pair.x) + (pair.y * pair.y);
        if (t > 1)
        {
            /* Nope. Reject */
            continue;
        }
        
        /* Calculate the multiplier for the values in this pair, and multiply */
        temp = sqrt((-2 * log(t)) / t);
        pair.x *= temp;
        pair.y *= temp;
        
        /* Keep a running sum of the x and y values */
        params->sumX += pair.x;
        params->sumY += pair.y;
        
        /*
         * Find the maximum of the absolute value of each value in the
         * pair. Take the floor of that maximum (by converting it to an
         * integer) so that we can use it as an index into the results
         * counters array.
         */
        maxXY = maximum(fabs(pair.x), fabs(pair.y));
        
        /* Update the appropriate counter corresponding to this value. */
        params->results[maxXY]++;
    }

    return params;
}

/**
 * Implementation of the main EP loop, generating pairs of pseudorandom
 * numbers, deciding if they're acceptable, tracking counts, and calculating
 * sums. This procedure is itself not free, but makes use of many free
 * sub-procedures.
 */
void
ep(void)
{
    struct timeval  tvStart;
    struct timeval  tvEnd;
    double          sumX = 0.0;
    double          sumY = 0.0;
    int             results[10] = { 0 };
    double          aux_sumX = 0.0;
    double          aux_sumY = 0.0;
    int             aux_results[10] = { 0 };
    struct threadStruct threadParams;
    int             i;
    double          temp;
    int             rank;
    MPI_Status      st;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    /* Get the starting time so we can later calculate running time */
    gettimeofday(&tvStart, NULL);

    threadParams.threadNum = rank;
    threadParams.sumX = 0.0;
    threadParams.sumY = 0.0;
    for (i = 0; i < 10; i++) {
        threadParams.results[i] = 0;
    }
    epThread(&threadParams);

    sumX = threadParams.sumX;
    sumY = threadParams.sumY;
    for (i = 0; i < 10; i++) {
        results[i] = threadParams.results[i];
    }

    if(rank == 0) {
        // eh o processo principal, sincronizar os resultados
        for(i = 1; i < NUM_THREADS; i++) {
            // receber sumX
            MPI_Recv( &aux_sumX, 1, MPI_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD, &st );
            // receber sumY
            MPI_Recv( &aux_sumY, 1, MPI_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD, &st );
            // receber results
            MPI_Recv( &aux_results, 10, MPI_int, i, MPI_ANY_TAG, MPI_COMM_WORLD, &st );
        }
    } else {
        // são os outros processos, enviar os dados computados
        // retornar sumX
        MPI_Send( &sumX, 1, MPI_LONG, 0, MPI_ANY_TAG, MPI_COMM_WORLD );
        // retornar sumY
        MPI_Send( &sumY, 1, MPI_LONG, 0, MPI_ANY_TAG, MPI_COMM_WORLD );
        // retornar results
        MPI_Send( results, 10, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD );
    }
    
    for (i = 0; i < NUM_THREADS; i++) {
        sumX += threadParams[i].sumX;
        sumY += threadParams[i].sumY;
        for(j = 0; j < 10; j++) {
            results[j] += threadParams[i].results[j];
        }
    }
    
    printf("l\tQt\n");
    printf("----------------\n");
    for (j = 0; j < 10; j++)
    {
        printf("%d\t%d\n", j, results[j]);
    }
    
    printf("sum(X) = %.16le\n", sumX);
    printf("sum(Y) = %.16le\n", sumY);

    /* Get the ending time so we can calculate running time */
    gettimeofday(&tvEnd, NULL);

    /* Calculate and display the running time */
    temp = ((tvEnd.tv_sec + ((double) tvEnd.tv_usec / 1000000)) -
            (tvStart.tv_sec + ((double) tvStart.tv_usec / 1000000)));
    printf("Time: %.4lf seconds.\n", temp);
}


int
main(int argc, char * argv[])
{
    int rank;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    //classe do problema
    char class = argv[1][0];
    switch (class) {
        case 'B':
            n = pow(2,30);
            if(rank == 0) {
                printf("Class B\n\n");
            }
            break;
        case 'A':
        default: 
            n = pow(2,28);
            if(rank == 0) {
                printf("Class A\n\n");
            }
            break;
    }
    //numero de threads para o problema
    MPI_Comm_size(MPI_COMM_WORLD,&NUM_THREADS);

    if(rank == 0) {
        printf("Numero de workers: %d\n\n", NUM_THREADS);
    }

    ep();

    if(rank == 0) {
        printf("\n\n---------------------------------\n\n");
    }

    MPI_Finalize();
    return 0;
}
