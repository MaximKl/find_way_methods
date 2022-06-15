/* if connection between from and to,
 then return the distance of flight;
 if not, return 0 */
#include <string.h>
#include "search.h"
#pragma warning(disable:4996)
int match(from, to)
char* from, * to;
{
	register int t;
	extern struct FL flight[];
	extern int f_pos;
	for (t = f_pos - 1; t > -1; t--)
		if (!strcmp(flight[t].from, from) &&
			!strcmp(flight[t].to, to)) return flight[t].distance;
	return 0; /* not found */
}
/*
*/