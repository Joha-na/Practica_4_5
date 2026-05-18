#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

// Variable compartida
int a = 0;
long MAX = 1000000;  // Reducido a 1e6 para que sea manejable

// Declarar el semáforo
sem_t s;

void * funcion_hilo1(void *arg);
void * funcion_hilo2(void *arg);
void * funcion_hilo3(void *arg);

int main(void)
{
    pthread_t hilo1, hilo2, hilo3;
    int valor_semaforo;
    
    // Inicializa el semáforo con valor inicial 1
    sem_init(&s, 0, 1);
    
    // Crear los tres hilos
    pthread_create(&hilo1, NULL, *funcion_hilo1, NULL);
    pthread_create(&hilo2, NULL, *funcion_hilo2, NULL);
    pthread_create(&hilo3, NULL, *funcion_hilo3, NULL);
    
    // Esperar que terminen los hilos
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    
    // Obtener y mostrar el valor final del semáforo
    sem_getvalue(&s, &valor_semaforo);
    printf("\n=========================================\n");
    printf("RESULTADOS FINALES:\n");
    printf("El valor de a es: %d\n", a);
    printf("Valor final del semáforo: %d\n", valor_semaforo);
    printf("=========================================\n");
    
    // Destruir el semáforo
    sem_destroy(&s);
    
    return 0;
}

void * funcion_hilo1(void *arg)
{
    int valor_sem;
    
    for(int i = 0; i < MAX; i++)
    {
        // Mostrar valor del semáforo antes de bloquear
        sem_getvalue(&s, &valor_sem);
        if(i % 100000 == 0) {  // Imprimir cada 100,000 iteraciones
            printf("Hilo1 - Iteración %d: Valor semáforo antes de sem_wait: %d\n", i, valor_sem);
        }
        
        // Bloquear la variable compartida
        sem_wait(&s);
        
        // Sección crítica
        a += 1;
        
        // Mostrar valor después de la operación
        sem_getvalue(&s, &valor_sem);
        if(i % 100000 == 0) {
            printf("Hilo1 - Iteración %d: Valor semáforo después de a+=1: %d\n", i, valor_sem);
        }
        
        // Incrementar el valor del semáforo
        sem_post(&s);
    }
    
    printf("Hilo1 ha terminado sus %ld iteraciones\n", MAX);
    return NULL;
}

void * funcion_hilo2(void *arg)
{
    int valor_sem;
    
    for(int i = 0; i < MAX; i++)
    {
        sem_getvalue(&s, &valor_sem);
        if(i % 100000 == 0) {
            printf("Hilo2 - Iteración %d: Valor semáforo antes de sem_wait: %d\n", i, valor_sem);
        }
        
        sem_wait(&s);
        a -= 1;
        
        sem_getvalue(&s, &valor_sem);
        if(i % 100000 == 0) {
            printf("Hilo2 - Iteración %d: Valor semáforo después de a-=1: %d\n", i, valor_sem);
        }
        
        sem_post(&s);
    }
    
    printf("Hilo2 ha terminado sus %ld iteraciones\n", MAX);
    return NULL;
}

void * funcion_hilo3(void *arg)
{
    int valor_sem;
    
    for(int i = 0; i < MAX; i++)
    {
        sem_getvalue(&s, &valor_sem);
        if(i % 100000 == 0) {
            printf("Hilo3 - Iteración %d: Valor semáforo antes de sem_wait: %d\n", i, valor_sem);
        }
        
        sem_wait(&s);
        
        // El tercer hilo puede hacer una operación diferente
        // Por ejemplo, multiplicar o simplemente leer el valor
        a = a;  // Operación neutra para no afectar el resultado final
        
        sem_getvalue(&s, &valor_sem);
        if(i % 100000 == 0) {
            printf("Hilo3 - Iteración %d: Valor semáforo dentro de SC: %d\n", i, valor_sem);
        }
        
        sem_post(&s);
    }
    
    printf("Hilo3 ha terminado sus %ld iteraciones\n", MAX);
    return NULL;
}
