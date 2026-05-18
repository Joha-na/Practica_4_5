#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
struct timeval tinicio , tfin ;
double promedio = 0.0;
void * hilo ( void * arg )
{
 gettimeofday (& tfin , NULL ) ;
 int tfin_seg= tfin.tv_sec;
 int tini_seg = tinicio.tv_sec;
 promedio += ( tfin_seg - tini_seg);
}
int main ()
{
 int i = 0;
 pthread_t h ;
 for ( i = 0 ; i < 100000 ; i ++ )
 {
 gettimeofday (& tinicio , NULL );
 pthread_create (& h, NULL , hilo , NULL) ;
 pthread_join (h, NULL);
 }
printf ("El tiempo de creación de los %d hilos es %f segundos\n", i , promedio);
}

