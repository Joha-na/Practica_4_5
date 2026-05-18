#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
//Variable compartida
int a=0;
long MAX=1e12;
void * funcion_hilo1(void *arg);
void * funcion_hilo2(void *arg);
//Declarar el semáforo
sem_t s;
int main (void)
{
 pthread_t hilo1, hilo2;
 //Inicializa el semáforo s, 0 porque no es compartido entre procesos sino ente hilos de un mismo proceso, valor inicial
 sem_init(&s,0,1);
 pthread_create(&hilo1, NULL, *funcion_hilo1, NULL);
 pthread_create(&hilo2, NULL, *funcion_hilo2, NULL);
 //Para esperar que terminen los hilos
 pthread_join(hilo1, NULL);
 pthread_join(hilo2, NULL);
 printf ("El valor de a es %d \n",a);
 return 0;
}
void * funcion_hilo1(void *arg)
{
 for(int i=0; i<MAX; i++)
 {
 //Bloqueo la variable compartida con sem_wait
 sem_wait(&s);
 a +=1;
 //Incremento el valor del semáforo
 sem_post(&s);
 }
}
void * funcion_hilo2(void *arg)
{
 for(int i=0; i<MAX; i++)
 {
 sem_wait(&s);
 a -=1;
 sem_post(&s);
 }
}

