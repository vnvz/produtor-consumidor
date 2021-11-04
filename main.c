#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_ITEM 5
#define BUFFER 5

sem_t vazio;
sem_t cheio;

int in = 0;
int out = 0;
int buffer[BUFFER];
pthread_mutex_t mutex;

void *insert_item(void *ino)
{
    int data;
    for(int i = 0; i < MAX_ITEM; i++){
        data = rand();
        sem_wait(&vazio);           // Funções respectivas
        pthread_mutex_lock(&mutex); // de espera
        
        buffer[in] = data;
        printf("Produtor %d: Inserir dado %d em %d\n", 
        *((int *)ino),              // Inserir o dado no buffer
        buffer[in], in);            // e printar info sobre ele

        in = (in + 1) % BUFFER;     
        pthread_mutex_lock(&mutex); // Sinalizar ao consumidor
        sem_post(&cheio);           // que o buffer está cheio
    }
}

void *remove_item(void *rno)
{
    for(int i = 0; i < MAX_ITEM; i++){
        sem_wait(&cheio);           // Funções respectivas
        pthread_mutex_lock(&mutex); // de espera

        int data = buffer[out];
        printf("Consumidor %d: Remover dado %d em %d\n",
        *((int *)rno),              // Remover o dado do buffer
        data, out);                 // e printar info sobre ele

        out = (out + 1) % BUFFER;
        pthread_mutex_unlock(&mutex); // Sinalizar ao produtor
        sem_post(&vazio);             // que o buffer está vazio
    }
}

int main()
{
    pthread_t produtor[5], consumidor[5]; // Definição dos tipos
    pthread_mutex_init(&mutex, NULL);     // Inicializar o mutex
    
    sem_init(&vazio, 0, BUFFER);          // Inicializar os semáforos
    sem_init(&cheio, 0, 0);               // de vazio e cheio

    int numpc[5] = {1,2,3,4,5};               // Usado para numerar o
                                          // produtor e consumidor

    for(int i = 0; i < 5; i++){
        pthread_create(&produtor[i], NULL, (void *)insert_item, (void *)&numpc[i]);
    } // Cria a thread do produtor

    for(int i = 0; i < 5; i++){
        pthread_create(&consumidor[i], NULL, (void *)remove_item, (void *)&numpc[i]);
    } // Cria a thread do consumidor

    for(int i = 0; i < 5; i++){
        pthread_join(produtor[i], NULL); // Prevenção de deadlock
    }

    for(int i = 0; i < 5; i++){
        pthread_join(consumidor[i], NULL);  // Prevenção de deadlock
    }

    pthread_mutex_destroy(&mutex);  // Limpeza do lixo
    sem_destroy(&vazio);
    sem_destroy(&cheio);
}