#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include "search.h"
#pragma warning(disable:4996)
void isflight_depp_search(char*, char*);
void isflight_Up_On_Hill(char*, char*);
void isflight_width(char*, char*);
void isflight_min_cost(char*, char*);
void isflight_delete_road(char*, char*);
void isflight_delete_node(char*, char*);
void isflight_opt_sol(char*, char*);
int route2(char*);
int route3(char*);
void route(char*);
void setup(void);
struct FL flight[MAX]; /* array of db structures */
int f_pos = 0; /* number of entries in flight db */
int find_pos = 0; /* index for searching flight db */
int tos = 0; /* top of stack */
int stos = 0; /* top of solution stack */
struct stack bt_stack[MAX]; /* backtracking stack */
struct stack solution[MAX]; /* hold temporary solution */
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int dist,t;
	char from[100], to[100], c1[100], c2[100];;
	char choose;
	char isStop = 'C';
	while (isStop == 'C') {
		struct FL EmtyStruct = {"", "",0};
		f_pos = 0;
		find_pos = 0;
		tos = 0;
		for (int i = 0; i < 100; i++)
		{
			from[i] = "";
			to[i] = "";
			c1[i] = "";
			c2[i] = "";
		}
		printf("1\tМетод пошуку в глибину\n");
		printf("2\tМетод пошуку в ширину\n");
		printf("3\tМетод пошуку на холмі\n");
		printf("4\tМетод пошуку з мінімальними витратами\n");
		printf("5\tМетод пошуку з видаленням шляху\n");
		printf("6\tМетод пошуку з видаленням вузла\n");
		printf("7\tМетод пошуку з знаходженням оптимального рішення\n");

		printf("Оберіть метод пошуку: ");
		choose = getche();
		printf("\n");
		setup();
		printf("Звідки:\n ");
		gets(from);
		printf("Куди:\n ");
		gets(to);
		printf("\n");

		if (choose == '1') {
			isflight_depp_search(from, to);
		}
		else if (choose == '2') {

			isflight_width(from, to);

		}
		else if (choose == '3') {

			isflight_Up_On_Hill(from, to);

		}else if (choose == '4') {

			isflight_min_cost(from, to);

		}else if (choose == '5') {
			do
			{
				isflight_delete_road(from, to);
				dist = route2(to);
				if (!dist) break;
				tos = 0; /* reset the backtrack stack */
			} while (getche() != 'q');
		} else if (choose == '6') {
			do
			{
				isflight_delete_node(from, to);
				dist = route2(to);
				if (!dist) break;
				clearmarkers(); /* reset the database */
				if (tos > 0) pop(c1, c2, &dist);
				retract(c1, c2); /* remove last node from database */
				tos = 0; /* reset the backtrack stack */
			} while (getche() != 'q');
		}
		else if (choose == '7') {
			do
			{
				isflight_opt_sol(from, to);
				dist = route3(to);
				tos = 0; /* reset the backtrack stack */
			} while (dist != 0); /* while still finding solusions */
			t = 0;
			printf("\nОптималний шлях:\n");
			while (t < stos)
			{
				printf("%s --> ", solution[t].from);
				dist += solution[t].dist;
				t++;
			}
			printf("%s\n", to);
			printf("Відстань %d км\n", dist);
		}
		route(to);
		printf("\nЗупинитися (S)\nПродовжити (С)\n");
		isStop = getche();
		isStop = toupper(isStop);
		printf("\n\n");
		for (int i = 0; i < 50; i++) {
			flight[i] = EmtyStruct;
		}
	}
	return;
}