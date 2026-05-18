#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
/*Función que imprime Hello*/
void *hello (void *arg)
{
char msg[5] = "Hello";
printf("%s",msg);
}
/*Función que imprime world*/
void *world(void *arg)
{
char msg[5]="world";
printf("%s",msg);
}
/*Funcion main*/
void main()
{
pthread_t h1 ;
pthread_t h2 ;
pthread_create (& h1 , NULL , hello, NULL);
pthread_join(h1,NULL);
pthread_create (& h2 , NULL , world, NULL);
pthread_join(h2,NULL);
printf ( "\n ");
}
