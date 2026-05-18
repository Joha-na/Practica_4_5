#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

struct timeval tinicio, tfin;
double tiempo_total = 0.0;

void *hilo_vacio(void *arg)
{
    // Hilo que no hace nada, solo para medir tiempo de creación
    return NULL;
}

void main()
{
    int i;
    pthread_t h;
    int cantidades[] = {1000000, 2000000, 3000000};
    int num_pruebas = 3;
    
    printf("=== MEDICIÓN DE TIEMPO DE CREACIÓN DE HILOS ===\n\n");
    
    for(int prueba = 0; prueba < num_pruebas; prueba++)
    {
        int num_hilos = cantidades[prueba];
        tiempo_total = 0.0;
        
        printf("Creando %d hilos...\n", num_hilos);
        
        // Medir tiempo de creación de todos los hilos
        gettimeofday(&tinicio, NULL);
        
        for(i = 0; i < num_hilos; i++)
        {
            pthread_create(&h, NULL, hilo_vacio, NULL);
            pthread_join(h, NULL);
        }
        
        gettimeofday(&tfin, NULL);
        
        // Calcular tiempo en microsegundos
        long segundos = tfin.tv_sec - tinicio.tv_sec;
        long microsegundos = tfin.tv_usec - tinicio.tv_usec;
        double tiempo_us = segundos * 1000000.0 + microsegundos;
        
        printf("Resultado para %d hilos:\n", num_hilos);
        printf("  Tiempo total: %.0f microsegundos\n", tiempo_us);
        printf("  Tiempo total: %.2f segundos\n", tiempo_us / 1000000.0);
        printf("  Tiempo promedio por hilo: %.2f microsegundos\n\n", tiempo_us / num_hilos);
    }
}
