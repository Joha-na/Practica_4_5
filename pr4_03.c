#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void *mensaje(void *arg)
{
 char *msg;
 msg = ( char *) arg;
 printf ("%s",msg) ;
}
void main()
{
 pthread_t h1;
 pthread_t h2;
 char *hello = "Hello";
 char *world = "world";
 pthread_create (& h1 , NULL , mensaje , (void *) hello);
 pthread_join ( h1 , NULL);
 printf("\t");
 pthread_create (& h2 , NULL , mensaje , (void *) world);
 pthread_join ( h2 , NULL);
 printf("\n");
}

