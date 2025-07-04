#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[NUM_PHILOSOPHERS];

pthread_mutex_t mutex;
pthread_cond_t cond[NUM_PHILOSOPHERS];

void test(int id) {
    int left = (id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    if (state[id] == HUNGRY && state[left] != EATING && state[right] != EATING) {
        state[id] = EATING;
        printf("Philosopher %d takes forks and starts EATING\n", id);
        pthread_cond_signal(&cond[id]);
    }
}

void pickup_forks(int id) {
    pthread_mutex_lock(&mutex);

    state[id] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", id);
    test(id);

    while (state[id] != EATING)
        pthread_cond_wait(&cond[id], &mutex);

    pthread_mutex_unlock(&mutex);
}

void return_forks(int id) {
    pthread_mutex_lock(&mutex);

    state[id] = THINKING;
    printf("Philosopher %d puts down forks and starts THINKING\n", id);

    int left = (id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    test(left);
    test(right);

    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* num) {
    int id = *(int*)num;
    free(num);

    while (1) {
        printf("Philosopher %d is THINKING\n", id);
        sleep(rand() % 3 + 1);

        pickup_forks(id);

        sleep(rand() % 3 + 1);

        return_forks(id);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_cond_init(&cond[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, philosopher, id);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_cond_destroy(&cond[i]);

    return 0;
}
