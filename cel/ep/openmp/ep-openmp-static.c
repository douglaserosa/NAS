/*
 * Copyright (c)2010 Derrell Lipman
 * Parallel Kernel EP: An embarrassingly parallel benchmark
 * OpenMp implementation
 * gcc ep-openmp.c -fopenmp -lm
 */
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <omp.h>

#define INITIAL_SEED    271828183
#define EPSILON         1.0e-8

// quantidade de threads. é alterada pelo parametro recebido na chamada do programa
int NUM_THREADS = 1;

// Tamanho do chunk. é alterado pelo parametro recebido na chamada do programa
int CHUNK_SIZE = 1;

// variavel para guardar o tamanho de M da entrada (2^M)
int M;

// variavel para guardar o tamanho de N da entrada (2^M)
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
    unsigned long   i;
    unsigned long   j;
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

int verify (int size, double sx, double sy) {
    int verified = 0;
    double sx_verify_value, sy_verify_value, sx_err, sy_err;
    sx_verify_value = 0.0;
    sy_verify_value = 0.0;
    if (size == 24) {
        sx_verify_value = -3.247834652034740e+3;
        sy_verify_value = -6.958407078382297e+3;
    } else if (size == 25) {
        sx_verify_value = -2.863319731645753e+3;
        sy_verify_value = -6.320053679109499e+3;
    } else if (size == 28) {
        sx_verify_value = -4.295875165629892e+3;
        sy_verify_value = -1.580732573678431e+4;
    } else if (size == 30) {
        sx_verify_value =  4.033815542441498e+4;
        sy_verify_value = -2.660669192809235e+4;
    } else if (size == 32) {
        sx_verify_value =  4.764367927995374e+4;
        sy_verify_value = -8.084072988043731e+4;
    }
    sx_err = fabs((sx - sx_verify_value) / sx_verify_value);
    sy_err = fabs((sy - sy_verify_value) / sy_verify_value);
    verified = ((sx_err <= EPSILON) && (sy_err <= EPSILON));
    return verified;
}


/**
 * Implementation of the main EP loop, generating pairs of pseudorandom
 * numbers, deciding if they're acceptable, tracking counts, and calculating
 * sums. This procedure is itself not free, but makes use of many free
 * sub-procedures.
 */
int ep(void)
{
    double          sumX = 0.0;
    double          sumY = 0.0;
    int             results[10] = { 0 };
    struct threadStruct threadParams[NUM_THREADS];
    int             i, j;

    double          random_seed;
    Pair            pair;
    double          t;
    double          multiplier;
    int             maxXY;
    int             verification;

    #pragma omp parallel private(i,j) shared (threadParams) num_threads(NUM_THREADS)
    {
        i = omp_get_thread_num();
        threadParams[i].threadNum = i;
        threadParams[i].sumX = 0.0;
        threadParams[i].sumY = 0.0;
        for (j = 0; j < 10; j++) {
            threadParams[i].results[j] = 0;
        }
    }

    #pragma omp parallel for private(i,j,random_seed,pair,t,multiplier,maxXY) shared (threadParams) schedule(static,CHUNK_SIZE) num_threads(NUM_THREADS)
    for (i = 0; i < (int) n; ++i)
    {
        j = omp_get_thread_num();
        // epThread(&threadParams[j], (double) i);

        if (i % CHUNK_SIZE == 0) {
            random_seed = getSeedFor(i * 2 + 1);
        }
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
        multiplier = sqrt((-2 * log(t)) / t);
        pair.x *= multiplier;
        pair.y *= multiplier;

        /* Keep a running sum of the x and y values */
        threadParams[j].sumX += pair.x;
        threadParams[j].sumY += pair.y;

        /*
            * Find the maximum of the absolute value of each value in the
            * pair. Take the floor of that maximum (by converting it to an
            * integer) so that we can use it as an index into the results
            * counters array.
            */
        maxXY = maximum(fabs(pair.x), fabs(pair.y));

        /* Update the appropriate counter corresponding to this value. */
        threadParams[j].results[maxXY]++;
    }
    
    // #pragma omp parallel for private(i,j) reduction(+:sumX,sumY,results[:10])
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

    verification = verify(M, sumX, sumY);
    if ( verification ) {
        printf("Verification = SUCCESSFUL\n");
    } else {
        printf("Verification = UNSUCCESSFUL\n");
    }

    return verification;
}


int
main(int argc, char * argv[])
{
    // variaveis para calculo de tempo
    struct timeval  tvStart;
    struct timeval  tvEnd;
    double          totalTime, begin, end;
    int             verification;
    // classe do problema
    char            class;

    /* Get the starting time so we can later calculate running time */
    gettimeofday(&tvStart, NULL);

    class = argv[1][0];

    printf("---------------------------------\n");

    switch (class) {
        case 'W':
            M = 25;
            n = pow(2,M);
            printf("EP-OpenMP: Class W\n");
            break;
        case 'A':
            M = 28;
            n = pow(2,M);
            printf("EP-OpenMP: Class A\n");
            break;
        case 'B':
            M = 30;
            n = pow(2,M);
            printf("EP-OpenMP: Class B\n");
            break;
        case 'C':
            M = 32;
            n = pow(2,M);
            printf("EP-OpenMP: Class C\n");
            break;
        case 'S':
        default:
            M = 24;
            n = pow(2,M);
            printf("EP-OpenMP: Class S\n");
            break;
    }
    // numero de threads para o problema
    omp_set_num_threads(atoi(argv[2]));
    NUM_THREADS = atoi(argv[2]);
    CHUNK_SIZE = atoi(argv[3]);
    if (CHUNK_SIZE <= 0) {
        CHUNK_SIZE = 1;
    }
    printf("Tamanho do problema: 2^%d = %ld\n", M, (long) n);
    printf("Numero de threads: %d\n", NUM_THREADS);
    printf("Tamanho do Chunk: %d\n\n", CHUNK_SIZE);
    
    verification = ep();

    /* Get the ending time so we can calculate running time */
    gettimeofday(&tvEnd, NULL);

    /* Calculate and display the running time */
    begin = (tvStart.tv_sec + ((double) tvStart.tv_usec / 1000000));
    end = (tvEnd.tv_sec + ((double) tvEnd.tv_usec / 1000000));
    totalTime = ( end - begin );
    printf("Time: %.4lf seconds.\n", totalTime);

    // saida: classe;threads;M;N;verificacao;begin;end;tempo;chunksize
    printf("SUMMARY: %c;%d;%d;%ld;%d;%.4lf;%.4lf;%.4lf;%d;",class,NUM_THREADS,M,(long)n,verification,begin,end,totalTime,CHUNK_SIZE);

    return 0;
}
