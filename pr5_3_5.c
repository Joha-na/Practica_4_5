#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Variable compartida que define el color del texto
// 0 = ROJO, 1 = VERDE, 2 = AZUL
int color_compartido = 0;

// Declarar el mutex (como en la Figura 4)
pthread_mutex_t mutex_color;

void * rojo(void *id)
{
    // Bloquear el mutex (como en la Figura 4)
    pthread_mutex_lock(&mutex_color);
    
    // --- SECCIÓN CRÍTICA ---
    // Modificamos la variable compartida
    color_compartido = 0;
    
    #define A "\x1b[31m"
    printf(A "Este texto es ROJO (color_compartido = %d)\n", color_compartido);
    #define RESET "\x1b[0m"
    printf(RESET);
    // --- FIN SECCIÓN CRÍTICA ---
    
    // Liberar el mutex (como en la Figura 4)
    pthread_mutex_unlock(&mutex_color);
    
    return NULL;
}

void * verde(void *id)
{
    // Bloquear el mutex
    pthread_mutex_lock(&mutex_color);
    
    // --- SECCIÓN CRÍTICA ---
    color_compartido = 1;
    
    #define B "\x1b[32m"
    printf(B "Este texto es VERDE (color_compartido = %d)\n", color_compartido);
    printf(RESET);
    // --- FIN SECCIÓN CRÍTICA ---
   
    // Liberar el mutex
    pthread_mutex_unlock(&mutex_color);
    
    return NULL;
}

int main()
{
    pthread_t hilo_rojo, hilo_verde;
    
    printf("EJERCICIO 3.5: MUTEX CON VARIABLE COLOR\n");
    
    // Inicializar el mutex (como en la Figura 4)
    pthread_mutex_init(&mutex_color, NULL);
    
    printf("Valor inicial de color_compartido: %d\n\n", color_compartido);
    
    // Crear los hilos (como en la Figura 3)
    pthread_create(&hilo_rojo, NULL, rojo, NULL);
    pthread_create(&hilo_verde, NULL, verde, NULL);
    
    // Esperar que terminen los hilos (como en la Figura 3)
    pthread_join(hilo_rojo, NULL);
    pthread_join(hilo_verde, NULL);
    
    // Destruir el mutex (como en la Figura 4)
    pthread_mutex_destroy(&mutex_color);
    
    // Imprimir desde el main (como en la Figura 3)
    #define C "\x1b[34m"
    printf(C "\nEste texto es AZUL \n");
    printf(RESET);
    
    printf("\nValor final de color_compartido: %d\n", color_compartido);
    
    return 0;
}
