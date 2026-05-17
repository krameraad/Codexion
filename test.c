#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>

#define ESC_X "\033[0m"
#define ESC_R "\033[91m"
#define ESC_G "\033[92m"

typedef struct 
{
	size_t i;
	pthread_mutex_t mtx;
}	ThreadCounter;

typedef struct 
{
	int *items;
	size_t count;
	pthread_mutex_t mutex;
	pthread_cond_t condition;
}	DataStream;

void *producer(void *arg)
{
	DataStream *ds = arg;
	unsigned long id = (unsigned long)pthread_self() % 10000;
	int n;

	for (size_t i = 0; i < 100; ++i)
	{
		pthread_mutex_lock(&ds->mutex);

		n = rand() / 1000;
		ds->items[ds->count] = n;
		ds->count += 1;
		printf(ESC_G "%4lu produced: %7d (count: %4zu)\n" ESC_X,
			id, n, ds->count);

		pthread_cond_broadcast(&ds->condition);
		pthread_mutex_unlock(&ds->mutex);
	}
	return NULL;
}

void *consumer(void *arg)
{
	DataStream *ds = arg;
	unsigned long id = (unsigned long)pthread_self() % 10000;

	for (size_t i = 0; i < 100; ++i)
	{
		pthread_mutex_lock(&ds->mutex);
		while (ds->count < 1)
			pthread_cond_wait(&ds->condition, &ds->mutex);

		ds->count -= 1;
		printf(ESC_R "%4lu consumed: %7d (count: %4zu)\n" ESC_X,
			id, ds->items[ds->count + 1], ds->count);

		pthread_mutex_unlock(&ds->mutex);
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t threads[20];
	DataStream ds = {0};
	ds.items = malloc(4000);
	srand(time(NULL));

	pthread_mutex_init(&ds.mutex, NULL);
	pthread_cond_init(&ds.condition, NULL);

	for (size_t i = 0; i < 10; ++i)
	{
		if (pthread_create(&threads[i], NULL, &producer, &ds))
			return (fprintf(stderr, "Error creating producer thread"), 1);
		if (pthread_create(&threads[i], NULL, &consumer, &ds))
			return (fprintf(stderr, "Error creating consumer thread"), 1);
	}
	for (size_t i = 0; i < 20; ++i)
		pthread_join(threads[i], NULL);
	printf("%zu\n", ds.count);

	pthread_mutex_destroy(&ds.mutex);
	pthread_cond_destroy(&ds.condition);
	free(ds.items);
	return 0;
}


/* Returns a `time_t` value that represents a timestamp in milliseconds. */
// time_t timestamp()
// {
// 	struct timeval tv;
//
// 	gettimeofday(&tv, NULL);
// 	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
// }

// void *timer(void *arg)
// {
// 	time_t start = timestamp();
//
// 	printf("Timer started.\n");
// 	fflush(stdout);
//
// 	usleep(1000000);
//
// 	time_t end = timestamp();
// 	printf("Timer ended (%lu).\n", end - start);
// 	fflush(stdout);
// 	return NULL;
// }

// void *counter(void *arg)
// {
// 	ThreadCounter *tc = arg;
// 	unsigned long id = (unsigned long)pthread_self();
//
// 	for (size_t i = 0; i < 1000; ++i)
// 	{
// 		pthread_mutex_lock(&tc->mtx);
// 		tc->i += 1;
// 		printf("%lu: %zu\n", id, tc->i);
// 		pthread_mutex_unlock(&tc->mtx);
// 	}
// 	return NULL;
// }