#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
sem_t full, empty;
int in = 0, out = 0;
int buffer[5];
pthread_mutex_t mut;

void *producer(void *pno) {
    int item;
    for (int i = 0; i < 5; i++) {
        item = rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mut);
        buffer[in] = item;
        cout << "Producer " << *((int *)pno) << " : Insert Item " << buffer[in] << " at " << in << endl;
        in = (in + 1) % 5;
        pthread_mutex_unlock(&mut);
        sem_post(&full);
    }
}

void *consumer(void *cno) {
    for(int i = 0; i < 5; i++) {
        sem_wait(&full);    
        pthread_mutex_lock(&mut);   
        int item = buffer[out];
        cout << "Consumer " << *((int *)cno) << " : Remove Item " << item << " from " << out << endl;
        out = (out + 1) % 5;
        pthread_mutex_unlock(&mut);
        sem_post(&empty);
    }
}


int main() {
    /*
     Taking 5 consumers and 5 producers
    */
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mut, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 5);
    int ind[5] = {1, 2, 3, 4, 5};
    for(int i = 0; i < 5; i++) 
        pthread_create(&pro[i], NULL, &producer, (void *)&ind[i]);
    for(int i = 0; i < 5; i++) 
        pthread_create(&con[i], NULL, &consumer, (void *)&ind[i]);
    for(int i = 0; i < 5; i++)
        pthread_join(pro[i], NULL);
    for(int i = 0; i < 5; i++)
        pthread_join(con[i], NULL);
    pthread_mutex_destroy(&mut);
    sem_destroy(&full);
    sem_destroy(&empty);
}