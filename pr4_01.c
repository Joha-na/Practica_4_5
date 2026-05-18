#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//Primera funcion donde se imprime el valor de a
void *function1 (void *arg)
{
int a = 10;
int *p = &a;
printf ("El valor de p con function1 es %d \n",*p);
}
//Segunda funcion donde se imprime el valor de a
void *function2 (void *arg)
{
int a=20;
int *p = &a;
printf ("El valor de p con function2 es %d \n",*p);
}
int main()
{
/*Declaracion de hilos h1 y h2 de tipo pthread*/
/*Es necesario guardar el identificador ya que una vez que un hilo comienza a funcionar, la única forma de controlarlo es a través de su
identificador*/
pthread_t h1 ;
pthread_t h2 ;
/*Se crean los hilos h1 y h2 y se inicia la ejecución de la función que se le pasa como tercer argumento function1 y function2*/
pthread_create (& h1 , NULL , function1, NULL);
/*La funcion pthread_join permite la ejecucion de los hilos*/
pthread_join(h1,NULL);
pthread_create (& h2 , NULL , function2, NULL);
pthread_join(h2,NULL);
}
