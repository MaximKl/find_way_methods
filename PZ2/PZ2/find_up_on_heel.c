/* given from, find anywhere farthest away
Hill-Climbing Search
*/
#include <string.h>
#include "search.h"
#pragma warning(disable:4996)
int find_up(from, anywhere)
char* from, * anywhere;
{
	extern struct FL flight[];
	extern int find_pos, f_pos;
	int pos, dist;
	pos = dist = 0;
	find_pos = 0;
	while (find_pos < f_pos)
	{
		if (!strcmp(flight[find_pos].from, from) &&
			!flight[find_pos].skip)
		{
			if (flight[find_pos].distance > dist)
			{
				pos = find_pos;
				dist = flight[find_pos].distance;
			}
		}
		find_pos++;
	}
	if (pos)
	{
		strcpy(anywhere, flight[pos].to);
		flight[pos].skip = 1; /* make active */
		return flight[pos].distance;
	}
	return 0;
}
/* determine if there is a route
 between from and to */
void isflight_Up_On_Hill(from, to)
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
	dist = find_up(from, anywhere);
	if (dist)
	{
		push(from, to, dist);
		isflight_Up_On_Hill(anywhere, to);
	}
	else
		if (tos > 0)
		{ /*backtrack*/
			pop(from, to, &dist);
			isflight_Up_On_Hill(from, to);
		}
	return;
}