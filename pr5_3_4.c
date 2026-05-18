#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Variable compartida que define el color del texto
// 0 = ROJO, 1 = VERDE, 2 = AZUL
int color_compartido = 0;

// Declarar el semáforo
sem_t semaforo_color;

void * rojo(void *id)
{
    // Bloquear el semáforo antes de acceder a la variable compartida
    sem_wait(&semaforo_color);
    
    // Sección crítica: modificar la variable compartida
    color_compartido = 0;  // 0 representa ROJO
    
    // Imprimir usando la variable compartida
    #define A "\x1b[31m"
    printf(A "Este texto es ROJO! (color_compartido = %d)\n", color_compartido);
    
    // Liberar el semáforo
    sem_post(&semaforo_color);
    
    return NULL;
}

void * verde(void *id)
{
    // Bloquear el semáforo
    sem_wait(&semaforo_color);
    
    // Modificar variable compartida
    color_compartido = 1;  // 1 representa VERDE
    
    // Imprimir
    #define B "\x1b[32m"
    printf(B "Este texto es VERDE! (color_compartido = %d)\n", color_compartido);
    
    // Liberar el semáforo
    sem_post(&semaforo_color);
    
    return NULL;
}

int main()
{
    pthread_t hilo_rojo, hilo_verde;
    int valor_sem;
    
    // Inicializar el semáforo
    // Parámetros: &semáforo, 0 (no compartido entre procesos), valor inicial 1
    sem_init(&semaforo_color, 0, 1);
    
    printf("=== DEMOSTRACIÓN CON SEMÁFORO ===\n");
    printf("Variable compartida 'color_compartido' controlada por semáforo\n\n");
    
    // Mostrar valor inicial del semáforo
    sem_getvalue(&semaforo_color, &valor_sem);
    printf("Valor inicial del semáforo: %d\n\n", valor_sem);
    
    // Crear los hilos
    pthread_create(&hilo_rojo, NULL, rojo, NULL);
    pthread_create(&hilo_verde, NULL, verde, NULL);
    
    // Esperar que terminen los hilos
    pthread_join(hilo_rojo, NULL);
    pthread_join(hilo_verde, NULL);
    
    // Mostrar valor final del semáforo
    sem_getvalue(&semaforo_color, &valor_sem);
    printf("\nValor final del semáforo: %d\n", valor_sem);
    printf("Valor final de color_compartido: %d\n", color_compartido);
    
    // Imprimir desde el hilo principal sin usar semáforo
    #define C "\x1b[34m"
    printf(C "\nEste texto es AZUL (impreso desde main, sin semáforo)\n");
    
    // Resetear color a blanco por defecto
    #define RESET "\x1b[0m"
    printf(RESET);
    
    // Destruir el semáforo
    sem_destroy(&semaforo_color);
    
    return 0;
}
