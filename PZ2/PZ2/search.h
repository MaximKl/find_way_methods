#pragma once
#define MAX 100
#pragma warning(disable:4996)
/* ��������� ���� ������ ������ */
struct FL
{
	char from[100];
	char to[100];
	int distance;
	char skip; /* used in backtracking */
};
struct stack
{
	char from[100];
	char to[100];
	int dist;
};
