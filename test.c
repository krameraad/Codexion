#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct 
{
	size_t i;
	pthread_mutex_t mtx;
}	ThreadCounter;

typedef struct 
{
	int *items;
	size_t count;
	size_t capacity;
	pthread_mutex_t mtx;
	pthread_cond_t cond;
}	DataStream;




void *producer(void *arg)
{
	DataStream *ds = arg;
	unsigned long id = (unsigned long)pthread_self();

	for (size_t i = 0; i < 1000; ++i)
	{
		
		pthread_mutex_lock(&ds->mtx);
		ds->count += 1;
		printf("Thread %lu produced: %zu\n", id, ds->items[0]);
		pthread_mutex_unlock(&ds->mtx);
	}
	return NULL;
}

void *consumer(void *arg)
{
	DataStream *ds = arg;
	unsigned long id = (unsigned long)pthread_self();

	for (size_t i = 0; i < 1000; ++i)
	{
		pthread_mutex_lock(&ds->mtx);
		ds->count -= 1;
		printf("%lu: %zu\n", id, ds->items[0]);
		pthread_mutex_unlock(&ds->mtx);
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t threads[10];
	ThreadCounter tc = {0};
	srand(time(NULL));

	pthread_mutex_init(&tc.mtx, NULL);
	printf("%zu\n", tc.i); fflush(stdout);

	for (size_t i = 0; i < 10; ++i)
	{
		if (pthread_create(&threads[i], NULL, &producer, &tc))
		{
			fprintf(stderr, "Error creating threads");
			return 1;
		}
	}
	for (size_t i = 0; i < 10; ++i)
		pthread_join(threads[i], NULL);

	pthread_mutex_destroy(&tc.mtx);
	printf("%zu\n", tc.i);
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