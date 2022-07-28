#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define g 9.81
#define arena 100
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void delay(int milli_seconds) { 
	clock_t start_time = clock(); 
	while (clock() < start_time + milli_seconds)
		;
}

int randNumber(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int vypis(int t1, int t2, int ciel) {
	int i;
	system("cls");
	if ((ciel > arena) || (ciel < 0)) {
		printf("SHOT OUT OF THE RANGE");
		delay(1000);
		system("cls");
		ciel = 0;
	}
	for (i = 0; i < 23; i++) {
		printf("\n");
	}
	for (i = 1; i <= arena; i++) {
		if (i == ciel) {
			printf("*");
		}
		else if (i == t1) {
			printf("1");
		}
		else if (i == t2) {
			printf("2");
		}
		else {
			printf(" ");
		}
	}
	printf("\n");
	for (i = 1; i <= arena; i++) {
		printf("_");
	}
	printf("\n\n");
	return 0;
}

int skuska(int t1, int t2) {
	while ((t1 == t2) || (t1 + 1 == t2) || (t1 - 1 == t2)) {
		t1 = randNumber(1, arena);
		t2 = randNumber(1, arena);
	}
	return 0;
}

int Players_turn(int t1, int t2) {
	int ciel, d, uhol, rychlost;
	double alfa;
	printf("Player's turn (1) \n");
	printf("Enter angle (deg): ");
	scanf("%d", &uhol);
	printf("Enter velocity (km/h): ");
	scanf("%d", &rychlost);
	alfa = uhol * M_PI / 180;
	d = ((rychlost / 3.6) * (rychlost / 3.6)) / g * (sin(2 * alfa));
	if (t1 < t2) {
		ciel = t1 + d;
	}
	else {
		ciel = t1 - d;
	}
	return ciel;
}

int Computers_turn(int t1, int t2, int round) {
	int d, ciel, angle, velocity, bolin;
	double pomoc, alfa;
	angle = randNumber(1, 89);
	alfa = angle * M_PI / 180;
	d = abs(t2 - t1);
	pomoc = d * g / (sin(2 * alfa));
	velocity = (sqrt(pomoc)) * 3.6;
	d = ((velocity / 3.6) * (velocity / 3.6)) / g * (sin(2 * alfa));
	bolin = randNumber(1, 2);
	if (t1 > t2) {
		if (bolin == 1) {
			ciel = (t2 + d) + (randNumber(0, round));
		}
		else {
			ciel = (t2 + d) - (randNumber(0, round));
		}
	}
	else {
		if (bolin == 1) {
			ciel = (t2 - d) + (randNumber(0, round));
		}
		else {
			ciel = (t2 - d) - (randNumber(0, round));
		}
	}
	printf("                                                              Computer's turn (2)\n");
	printf("                                                              Enter angle (deg): %d\n", angle);
	printf("                                                              Enter velocity (km/h): %d", velocity);
	delay(2000);
	return ciel;
}

int game(int t1, int t2) {
	int ciel = 0, round;
	skuska(t1, t2);
	printf("(0-20; 20 - EASY, 10 - MEDIUM, 5 - HARD, 0 - INSANE) \nPlease enter difficulty:  ");
	scanf("%d", &round);
	vypis(t1, t2, ciel);
	while (t1 > 0) {
		ciel = Players_turn(t1, t2);
		vypis(t1, t2, ciel);
		if ((ciel == t2) || (ciel == t2 + 1) || (ciel == t2 - 1)) {
			break;
		}
		delay(2000);
		ciel = Computers_turn(t1, t2, round);
		vypis(t1, t2, ciel);
		if ((ciel == t1) || (ciel == t1 + 1) || (ciel == t1 - 1)) {
			break;
		}
		round--;
	}
	if ((ciel == t1) || (ciel == t1 + 1) || (ciel == t1 - 1)) {
		printf("Computer wins \n");
	}
	if ((ciel == t2) || (ciel == t2 + 1) || (ciel == t2 - 1)) {
		printf("Player wins \n");
	}
	return 0;
}

int main() {
	int t1, t2;
	srand(time(0));
	t1 = randNumber(1, arena);
	t2 = randNumber(1, arena);
	game(t1, t2);
	return 0;
}