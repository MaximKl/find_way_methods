/* given from, find anywhere
*/
#include <string.h>
#include "search.h"
int find_delete_node(from, anywhere)
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
void isflight_delete_node(from, to)
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
	dist = find_delete_node(from, anywhere);
	if (dist)
	{
		push(from, to, dist);
		isflight_delete_node(anywhere, to);
	}
	else
		if (tos > 0)
		{ /*backtrack*/
			pop(from, to, &dist);
			isflight_delete_node(from, to);
		}
	return;
}
/* reset the "skip" field i.e.,
 retractive all nodes */
void clearmarkers()
{
	int t;
	extern struct FL flight[];
	extern int f_pos;
	for (t = 0; t < f_pos; ++t)
		flight[t].skip = 0;
	return;
}

void retract(from, to)
char* from, * to;
{
	int t;
	extern struct FL flight[];
	extern int f_pos;
	for (t = 0; t < f_pos; t++)
		if (!strcmp(flight[t].from, from) &&
			!strcmp(flight[t].to, to)) {
			strcpy(flight[t].from, "");
			return;
		}
	return;
}
