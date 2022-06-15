/* given from, find anywhere
*/
#include <string.h>
#include "search.h"
int find_opt_sol(from, anywhere)
char* from, * anywhere;
{
	extern struct FL flight[];
	extern int find_pos, f_pos;
	find_pos = 0;
	while (find_pos < f_pos)
	{
		if (!strcmp(flight[find_pos].from, from) &&
			!flight[find_pos].skip)
		{
			strcpy(anywhere, flight[find_pos].to);
			flight[find_pos].skip = 1; /* make active */
			return flight[find_pos].distance;
		}
		find_pos++;
	}
	return 0;
}
/* determine if there is a route
 between from and to */
void isflight_opt_sol(from, to)
char* from, * to;
{
	int d, dist;
	char anywhere[100];
	extern int tos;
	/* see if destination is reached */
	d = match(from, to);
	if (d)
	{
		push(from, to, d);
		return;
	}
	/* try another connection */
	dist = find_opt_sol(from, anywhere);
	if (dist)
	{
		push(from, to, dist);
		isflight_opt_sol(anywhere, to);
	}
	else
		if (tos > 0)
		{ /*backtrack*/
			pop(from, to, &dist);
			isflight_opt_sol(from, to);
		}
	return;
}

void spush(from, to, dist)
char* from, * to;
int dist;
{
	extern struct stack solution[];
	extern int stos;
	if (stos < MAX)
	{
		strcpy(solution[stos].from, from);
		strcpy(solution[stos].to, to);
		solution[stos].dist = dist;
		stos++;
	}
	else printf("Shortest distance stack full.\n");
}