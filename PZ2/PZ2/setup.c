/* found the route and distance
*/
#include <stdio.h>
#include "search.h"
#pragma warning(disable:4996)
void route(to)
char* to;
{
	int dist, t;
	extern struct stack bt_stack[];
	extern int tos;
	t = 0;
	dist = 0;
	while (t < tos)
	{
		printf("%s --> ", bt_stack[t].from);
		dist += bt_stack[t].dist;
		t++;
	}
	if (dist == 0) {
		return;
	}
	printf("%s\n", to);
	printf("Відстань %d км\n", dist);
	return;
}

int route2(to)
char* to;
{
	int dist, t;
	extern struct stack bt_stack[];
	extern int tos;
	t = 0;
	dist = 0;

	while (t < tos)
	{

		printf("%s --> ", bt_stack[t].from);
		dist += bt_stack[t].dist;
		t++;
	}
	if (dist == 0) {
		return 0;
	}
	printf("%s\n", to);
	printf("Відстань %d км\n", dist);
	return dist;
}



int route3(to)
char* to;
{
	int dist, t;
	static int old_dist = 32000;
	extern struct stack bt_stack[];
	extern int tos, stos;
	if (!tos) return 0; /* all done */
	t = 0;
	dist = 0;
	while (t < tos)
	{
		printf("%s --> ", bt_stack[t].from);
		dist += bt_stack[t].dist;
		t++;
	}
	printf("%s\n", to);
	printf("Відстань %d км\n", dist);
	/* if shorter, then make new solution */
	if (dist < old_dist && dist)
	{
		t = 0;
		old_dist = dist;
		stos = 0; /* clear old route from solution stack */
		while (t < tos)
		{
			spush(bt_stack[t].from, bt_stack[t].to,
				bt_stack[t].dist);
			t++;
		}
	}
	return dist;
}

void setup()
{
	assert_flight("Харків", "Херсон", 552);
	assert_flight("Херсон", "Одеса", 230);
	assert_flight("Харків", "Київ", 485);
	assert_flight("Харків", "Одеса", 650);
	assert_flight("Київ", "Чернівці", 540);
	assert_flight("Київ", "Херсон", 650);
	assert_flight("Київ", "Львів", 550);
	assert_flight("Одеса", "Вінниця", 430);
	assert_flight("Одеса", "Хмельницький", 560);
	assert_flight("Хмельницький", "Львів", 250);
	assert_flight("Одеса", "Львів", 800);
	return;
}