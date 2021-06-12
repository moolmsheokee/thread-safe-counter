#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
};

#define PATH "/mnt/c/Users/andy8/thread-safe-counter"

typedef struct _counter_t {
    int value;
    int semid;
    key_t key;
    struct sembuf s;
    union semun arg;
} semcounter_t;

unsigned int loop_cnt;
semcounter_t semcounter;

void init(semcounter_t *c) {
    c->value = 0;
    key_t key;
    key = ftok(PATH, 'z');
    int semid = segment(c->key, 1, 0600 | IPC_CREAT);
}

void increment(semcounter_t *c) {

    int semid;
    struct sembuf s;
    
    s.sem_num = 0;
    s.sem_op = -1;
    s.sem_flg = 0;
    semop(semid, &s, 1);
    
    c->value++;
    
    s.sem_num = 0;
    s.sem_op = 1;
    s.sem_flg = 0;
    semop(semid, &s, 1);
}

void decrement(counter_t *c) {
    
    int semid;
    struct sembuf s;
    
    s.sem_num = 0;
    s.sem_op = -1;
    s.sem_flg = 0;
    semop(semid, &s, 1);
    
    c->value--;
    
    s.sem_num = 0;
    s.sem_op = 1;
    s.sem_flg = 0;
    semop(semid, &s, 1);
}

int get(counter_t *c) {
    
    int semid;
    struct sembuf s;
    
    s.sem_num = 0;
    s.sem_op = -1;
    s.sem_flg = 0;
    semop(semid, &s, 1);
    
    int rc = c->value;
    
    s.sem_num = 0;
    s.sem_op = 1;
    s.sem_flg = 0;
    semop(semid, &s, 1);

    return rc;
}

void *mythread(void *arg)
{
    char *letter = arg;
    int i;

    printf("%s: begin\n", letter);
    for (i = 0; i < loop_cnt; i++) {
        increment(&semcounter);
    }
    printf("%s: done\n", letter);
    return NULL;
}
                                                                             
int main(int argc, char *argv[])
{       
    
    loop_cnt = atoi(argv[1]);
    init(&semcounter);

    if (semcounter.key < 0){
        perror(argv[0]);
        exit(1);
    }
    if (semcounter.semid < 0){
        perror(argv[0]);
        exit(1);
    }
    
    pthread_t p1, p2;
    printf("main: begin [counter = %d]\n", get(&semcounter));
    pthread_create(&p1, NULL, mythread, "A"); 
    pthread_create(&p2, NULL, mythread, "B");
    // join waits for the threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    printf("main: done [counter: %d] [should be: %d]\n", get(&semcounter), loop_cnt * 2);
    
    return 0;
}
