#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
//Variable compartida
int a=0,MAX=1000000;
void * funcion_hilo1(void *arg);
void * funcion_hilo2(void *arg);
int main (void)
{
 pthread_t hilo1, hilo2;
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
 a +=1;
 }
}
void * funcion_hilo2(void *arg)
{
 for(int i=0; i<MAX; i++)
 {
 a -=1;
 }
}
