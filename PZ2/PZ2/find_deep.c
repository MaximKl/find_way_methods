#include <string.h>
#include "search.h"
#pragma warning(disable:4996)
int find_deep(from, anywhere)
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
void isflight_depp_search(from, to)
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
	dist = find_deep(from, anywhere);
	if (dist)
	{
		push(from, to, dist);
		isflight_depp_search(anywhere, to);
	}
	else
		if (tos > 0)
		{ /*backtrack*/
			pop(from, to, &dist);
			isflight_depp_search(from, to);
		}
	return;
}