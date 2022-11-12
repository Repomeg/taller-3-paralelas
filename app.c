#include <omp.h> // Librería OpenMP
#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char *argv[]) {
    
    // Declaración de variables
    int i,j;
    double x;
    double pi, sum = 0.0;
    double t1, t2, diff;
    static long nsteps = 1000000000;

    double step = 1.0/(double) nsteps;
    
    omp_set_num_threads(4); // Se define el número máximos de hilos

    // Calculo del tiempo por cada uno de los hilos
    for (j=1; j<= 4; j++) {
        printf(" Hilo %d: ", j);

        // This is the beginning of a single PI computation 
        omp_set_num_threads(j);

        sum = 0.0;
        t1 = omp_get_wtime(); // Se obtiene el tiempo inicial

        #pragma omp parallel for reduction(+:sum) private(x)
        for (i=0; i < nsteps; i++) {  // Se realiza el cálculo de pi
            x = (i+0.5)*step;
            sum += 4.0 / (1.0+x*x); 
        }

        // Se finaliza la región paralela
        pi = step * sum;
        
        t2 = omp_get_wtime();  // Se obtiene el tiempo final
        diff = t2 - t1;  // Se obtiene la diferencia de tiempo entre el final y el inicial
        printf("PI = %.10g calculado en %.4g segundos\n", pi, diff);

    }
}
