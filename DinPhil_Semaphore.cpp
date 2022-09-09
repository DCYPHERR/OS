
#include <bits/stdc++.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define N 5
#define THINKING 2
#define HUNGRY 3
#define EATING 0
#define LEFT (phnum) % N
#define RIGHT (phnum + 1) % N

int phil[N];
int times = 1;

class monitor
{

	// state of the philosopher
	int state[N];

	// Philosopher condition variable
	pthread_cond_t phcond[N];

	// mutex variable for synchronization
	pthread_mutex_t condLock;

public:
	void test(int phnum)
	{

		if (state[(phnum + 1) % 5] != EATING and state[(phnum + 4) % 5] != EATING and state[phnum] == HUNGRY)
		{
			state[phnum] = EATING;

			pthread_cond_signal(&phcond[phnum]);
		}
	}

	void take_fork(int phnum)
	{

		pthread_mutex_lock(&condLock);
		state[phnum] = HUNGRY;
		test(phnum);
		if (state[phnum] != EATING)
		{
			pthread_cond_wait(&phcond[phnum], &condLock);
		}
		cout << "Philosopher " << phnum << " is Eating"
			 << endl;

		pthread_mutex_unlock(&condLock);
	}

	void put_fork(int phnum)
	{

		pthread_mutex_lock(&condLock);
		state[phnum] = THINKING;

		test(RIGHT);
		test(LEFT);

		pthread_mutex_unlock(&condLock);
	}
	monitor()
	{

		for (int i = 0; i < N; i++)
		{
			state[i] = THINKING;
		}

		for (int i = 0; i < N; i++)
		{
			pthread_cond_init(&phcond[i], NULL);
		}

		pthread_mutex_init(&condLock, NULL);
	}
	~monitor()
	{

		for (int i = 0; i < N; i++)
		{
			pthread_cond_destroy(&phcond[i]);
		}

		pthread_mutex_destroy(&condLock);
	}
}

phil_object;

void *philosopher(void *arg)
{
	int c = 0;
	while (c < times)
	{
		int i = *(int *)arg;
		sleep(1);
		phil_object.take_fork(i);
		sleep(0.5);
		phil_object.put_fork(i);
		c++;
	}
}

int main()
{
	pthread_t thread_id[N];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,
								PTHREAD_CREATE_JOINABLE);

	for (int i = 0; i < N; i++)
	{
		phil[i] = i;
	}

	for (int i = 0; i < N; i++)
	{
		pthread_create(&thread_id[i], &attr, philosopher,
					   &phil[i]);
		cout << "Philosopher " << i + 1 << " is thinking..."
			 << endl;
	}

	for (int i = 0; i < N; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	// Destroying
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);

	return 0;
}
