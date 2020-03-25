#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t wrt;          //semaphore can also be used sem_t wrt
pthread_mutex_t mutex;
int shared_value;
int active_reader = 0;

void *writers(void *writer_no)
{   
	pthread_mutex_lock(&wrt);
	//int n = rand() % 20; //an amount of time 
	shared_value = shared_value*2;
	printf("Writer %d modified count to %d\n\n",(*((int *)writer_no)),shared_value);
	pthread_mutex_unlock(&wrt);

}
void *readers(void *reader_no)
{   
	// Reader will lock before modifying acive_reader aka Entry Section
	pthread_mutex_lock(&mutex);
	active_reader++;
	if(active_reader == 1) {
	pthread_mutex_lock(&wrt); // Here if the id belongs to the first reader, it will block writer as reader have the higher proprity
	}
	pthread_mutex_unlock(&mutex);
	// Reading Section or Exit Section
	int n = rand() % 20;
	printf("Reader %d: is waiting....\n\n",*((int *)reader_no));
	sleep(n);
	printf("Reader %d: is reading......\n\n",*((int *)reader_no));
	printf("Reader %d: read shared variable as %d\n\n",*((int *)reader_no),shared_value);
	//}
	printf("Number of readers currently present = %d\n\n",active_reader);
	// Reader will the lock before modifying active_reader
	pthread_mutex_lock(&mutex);
	active_reader--;
	if(active_reader == 0) {
	pthread_mutex_unlock(&wrt); // If no readers are present, it will wake up the writer thread. 
	}
	pthread_mutex_unlock(&mutex);
}

int main()
{   

	printf("Enter the share value: \n");
	scanf("%d",&shared_value);
	pthread_t reads[5],writes[5];
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&wrt,NULL);

	int b[5] = {1,2,3,4,5};

	for(int j = 0; j < 5; j++) {
	pthread_create(&reads[j], NULL, (void *)readers, (void *)&b[j]);
	}
	for(int j = 0; j < 5; j++) {
	pthread_create(&writes[j], NULL, (void *)writers, (void *)&b[j]);
	}

	for(int j = 0; j < 5; j++) {
	pthread_join(reads[j], NULL);
	}
	for(int j = 0; j < 5; j++) {
	pthread_join(writes[j], NULL);
	}

	pthread_mutex_destroy(&mutex); //datastructures needs to be destroyed as sem and pthreads are data structure
	pthread_mutex_destroy(&wrt);

	return 0;

}
