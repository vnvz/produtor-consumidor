#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_ITEM 5
#define BUFFER 5

sem_t vazio;
sem_t cheio;

int in = 0;
int out = 0;
int buffer_arr[BUFFER];
pthread_mutex_t mutex;

void *insert_item(void *ino)
{   
    int data;
    for(int i = 0; i < MAX_ITEM; i++) {
        data = rand();
        sem_wait(&vazio);           // Funções de espera
        pthread_mutex_lock(&mutex);

        buffer_arr[in] = data;      // Inserir o dado no buffer e printar info sobre ele
        printf("Produtor %d: Inserir dado %d em %d\n", *((int *)ino), buffer_arr[in], in);

        in = (in + 1) % BUFFER;     // Sinalizar o consumidor que o buffer está cheio
        pthread_mutex_unlock(&mutex);
        sem_post(&cheio);
    }
}
void *remove_item(void *cno)
{   
    for(int i = 0; i < MAX_ITEM; i++) {
        sem_wait(&cheio);           // Funções de espera
        pthread_mutex_lock(&mutex);
        
        int data = buffer_arr[out]; // Remover dado do buffer e printar info sobre ele
        printf("Consumidor %d: Remover dado %d em %d\n",*((int *)cno), data, out);

        out = (out + 1) % BUFFER;   // Sinalizar ao produtor que o buffer está vazio
        pthread_mutex_unlock(&mutex);
        sem_post(&vazio);
    }
}

int main()
{   
    pthread_t produtor[5], consumidor[5]; // Definição dos tipos
    pthread_mutex_init(&mutex, NULL);     // Inicializar o mutex

    sem_init(&vazio, 0, BUFFER);          // Inicializar os semáforos
    sem_init(&cheio, 0, 0);               // de vazio e cheio

    int numpc[5] = {1,2,3,4,5};
    int sleept;
    printf("Esse programa demonstrará 5 produtores e 5 consumidores.\n");
    printf("Por quanto tempo o programa deverá dormir após a execução?\n");
    scanf("%d", &sleept);

    for(int i = 0; i < 5; i++) {
        pthread_create(&produtor[i], NULL, (void *)insert_item, (void *)&numpc[i]);
    } // Cria a thread do produtor]

    for(int i = 0; i < 5; i++) {
        pthread_create(&consumidor[i], NULL, (void *)remove_item, (void *)&numpc[i]);
    } // Cria a thread do consumidor

    for(int i = 0; i < 5; i++) {
        pthread_join(produtor[i], NULL); // Prevenção de deadlock
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(consumidor[i], NULL); // Prevenção de deadlock
    }

    printf("\n\nO programa irá adormecer por %d segundos", sleept);
    printf("\nBoa noite...");
    printf("\nBom dia! Até mais!");

    pthread_mutex_destroy(&mutex); // Limpeza do lixo
    sem_destroy(&vazio);
    sem_destroy(&cheio);

    sleep(sleept);

    return 0;
}