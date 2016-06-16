/*
 * Copyright (c)2010 Derrell Lipman
 * Parallel Kernel EP: An embarrassingly parallel benchmark
 * Serial implementation
 */
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <pthread.h>

#define INITIAL_SEED    271828183
#define EPSILON         1.0e-8

// quantidade de threads. é alterada pelo parametro recebido na chamada do programa
int NUM_THREADS = 1;

// variavel para guardar o tamanho de N da entrada (2^N)
int M;

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


int verify (int size, double sx, double sy) {
    int verified = 0;
    double sx_verify_value, sy_verify_value, sx_err, sy_err;
    sx_verify_value = 0.0;
    sy_verify_value = 0.0;
    if (size == 28) {
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
 * sorteia n/NUM_THREADS numeros aleatorios 
 * @param n [description]
 */
void* epThread (void *params) {
    struct threadStruct *args = (struct threadStruct *) params;
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
    
    from = args->threadNum * (n / NUM_THREADS);
    until = (args->threadNum  + 1) * (n / NUM_THREADS);
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
        args->sumX += pair.x;
        args->sumY += pair.y;
        
        /*
         * Find the maximum of the absolute value of each value in the
         * pair. Take the floor of that maximum (by converting it to an
         * integer) so that we can use it as an index into the results
         * counters array.
         */
        maxXY = maximum(fabs(pair.x), fabs(pair.y));
        
        /* Update the appropriate counter corresponding to this value. */
        args->results[maxXY]++;
    }

    pthread_exit(params);
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
    pthread_t       threads[NUM_THREADS];
    struct threadStruct threadParams[NUM_THREADS];
    int             i, j;
    double          temp;

    /* Get the starting time so we can later calculate running time */
    gettimeofday(&tvStart, NULL);

    for (i = 0; i < NUM_THREADS; i++) {
        threadParams[i].threadNum = i;
        threadParams[i].sumX = 0.0;
        threadParams[i].sumY = 0.0;
        for (j = 0; j < 10; j++) {
            threadParams[i].results[j] = 0;
        }
        pthread_create(&threads[i], NULL, epThread, (void *) &threadParams[i]);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], (void *) &threadParams[i]);
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

    if ( verify(M, sumX, sumY) ) {
        printf("Verification = SUCCESSFUL\n");
    } else {
        printf("Verification = UNSUCCESSFUL\n");
    }

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
    // numero de threads para o problema
    NUM_THREADS = atoi(argv[2]);
    // classe do problema
    char class = argv[1][0];
    switch (class) {
        case 'B':
            M = 30;
            n = pow(2,30);
            printf("EP-PThreads: Class B\n\n");
            break;
        case 'C':
            M = 32;
            n = pow(2,32);
            printf("EP-PThreads: Class C\n\n");
            break;
        case 'A':
        default:
            M = 28;
            n = pow(2,28);
            printf("EP-PThreads: Class A\n\n");
            break;
    }
    printf("Numero de threads: %d\n\n", NUM_THREADS);

    ep();

    printf("\n\n---------------------------------\n\n");

    return 0;
}
