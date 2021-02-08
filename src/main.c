/*
** EPITECH PROJECT, 2018
** strace
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "strace.h"

int main(int ac, char **av, char **env)
{
	struct strace_s strace_info;

	if (get_arguments(&strace_info, ac, av, env) == ERR_RET
		|| init_trace(&strace_info) == ERR_RET
		|| strace(&strace_info) == ERR_RET)
		return (ERR_RET);
	return (EXIT_SUCCESS);
}
