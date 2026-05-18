#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *mensaje(void *arg)
{
    char *msg;
    msg = (char *) arg;
    printf("%s\n", msg);
}

void main()
{
    pthread_t h1, h2, h3, h4;
    
    char *msg1 = "Soy el hilo 1: Hola mundo";
    char *msg2 = "Soy el hilo 2: Buenas Tardes";
    char *msg3 = "Soy el hilo 3: Buenas Noches";
    char *msg4 = "Soy el hilo 4: Último hilo";
    
    pthread_create(&h1, NULL, mensaje, (void *) msg1);
    pthread_create(&h2, NULL, mensaje, (void *) msg2);
    pthread_create(&h3, NULL, mensaje, (void *) msg3);
    pthread_create(&h4, NULL, mensaje, (void *) msg4);
    
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    pthread_join(h3, NULL);
    pthread_join(h4, NULL);
}
