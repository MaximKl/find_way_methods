/* stack routness
*/
#include <string.h>
#include <stdio.h>
#include "search.h"
#pragma warning(disable:4996)
void push(from, to, dist)
char* from, * to;
int dist;
{
	extern struct stack bt_stack[];
	extern int tos;
	if (tos < MAX)
	{
		strcpy(bt_stack[tos].from, from);
		strcpy(bt_stack[tos].to, to);
		bt_stack[tos].dist = dist;
		tos++;
	}
	else printf("Stack full.\n");
	return;
}