#include <omp.h> // Librería OpenMP
#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char *argv[]) {
    
    // Declaración de variables
    int i,j; // Variables para los ciclos for
    double x, pi, sum = 0.0;  // Variables para el cálculo de pi
    double t1, t2, diff;  // Variables para el cálculo del tiempo de ejecución
    static long nsteps = 1000000000; 

    double step = 1.0/(double) nsteps;

    int z= 8; // Se define el número máximos de hilos
    //omp_set_num_threads(z); 

    // Calculo del tiempo por cada uno de los hilos
    for (j=1; j<= z; j++) {
        printf(" Hilos %d: ", j); 

        // Se inicia el valor de hilos correspondiente
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
