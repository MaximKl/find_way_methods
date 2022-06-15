/* given from, find anywhere
*/
#include <string.h>
#include "search.h"
int find_delete_road(from, anywhere)
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
/* determine if there is a route between from and to
*/
void isflight_delete_road(from, to)
char* from, * to;
{
	int d, dist;
	char anywhere[20];
	extern int tos;
	/* see if destination is reached */
	d = match(from, to);
	if (d)
	{
		push(from, to, d);
		return;
	}
	/* try another connection */
	dist = find_delete_road(from, anywhere);
	if (dist)
	{
		push(from, to, dist);
		isflight_delete_road(anywhere, to);
	}
	else
		if (tos > 0)
		{ /*backtrack*/
			pop(from, to, &dist);
			isflight_delete_road(from, to);
		}
	return;
}