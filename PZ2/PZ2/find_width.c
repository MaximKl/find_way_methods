/* given from, find anywhere
*/
#include <string.h>
#include "search.h"
#pragma warning(disable:4996)
int find_wd(from, anywhere)
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
 between from and to "breadth-first mth" */
void isflight_width(from, to)
char* from, * to;
{
	int d, dist;
	char anywhere[20];
	extern int tos;
	while (dist = find_wd(from, anywhere))
	{
		d = match(anywhere, to);
		if (d)
		{
			push(from, to, dist);
			push(anywhere, to, d);
			return;
		}
	}
	/* try any connection */
	dist = find_wd(from, anywhere);
	if (dist)
	{
		push(from, to, dist);
		isflight_width(anywhere, to);
	}
	else
		if (tos > 0)
		{ /*backtrack*/
			pop(from, to, &dist);
			isflight_width(from, to);
		}
	return;
}
/* if connection between from and to,
 then return the distance of flight;
 if not, return 0 */