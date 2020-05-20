#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

 /*number of zombies in the game:
you should synchronize threads editing this variable*/
int zombieCounter = 0;
int zombiesKilled = 0;

/* Returns true if number of zombies in the room are
greater than or equal to 100.*/
int tooManyZombiesInTheRoom() {
	if (zombieCounter >= 100)
		return true;
	else
		return false;
}

/* Returns true if there is at least one zombies in the room.*/
int zombiesExist() {
	if (zombieCounter >= 0)
		return true;
	else
		return false;
}
/*Returns the number of zombies killed.*/
int getKilledCount() {
	return zombiesKilled;
}

/* Returns the number of zombies in the room.*/
int getInTheRoomCount() {
	return zombieCounter;
}

/*Returns true if more than 100 zombies have been killed.*/
int killed100Zombies() {
	if (zombiesKilled >= 100)
		return true;
	else
		return false;
}

/* Keeps track of number of zombies entered.*/
void zombieEntered() {
	while (!(killed100Zombies()) && !(tooManyZombiesInTheRoom()) && zombiesExist())
	{
		srand(time(NULL));
		int rondomly = rand() % 2; //a zombie with a 50% chance every 2ms
		if (rondomly == 0) {
			usleep(2);
			++zombieCounter;
			printf("Total number of zombies entered in room : %d \n", getInTheRoomCount());
		}
	}
}
/* Keeps track of number of zombies killed.*/
void zombieKilled() {

	while (!(killed100Zombies()) && !(tooManyZombiesInTheRoom()) && zombiesExist())
	{
		srand(time(NULL));
		int rondomly = rand() % 2;
		if (rondomly == 0) {
			usleep(2);
			--zombieCounter;
			++zombiesKilled;
			printf("number of zombies killed : %d \n", getKilledCount());
		}
	}
}

/*doorman thread*/
void *doorMan(void *p) {
	zombieEntered();
}

/*slayer thread*/
void *slayer(void *p) {
	zombieKilled();
}

/*simulator main thread*/
int main(int argc, char **argv) {
	int val = atoi(argv[1]);
	pthread_t doorMan_t[val];
	pthread_t slayer_t;

	pthread_create(&slayer_t, NULL, slayer, NULL);

	for (int i = 0; i < val; i++) {
		pthread_create(&doorMan_t[i], NULL, doorMan, NULL);
		pthread_join(doorMan_t[i], NULL);
	}

	pthread_join(slayer_t, NULL);

}
