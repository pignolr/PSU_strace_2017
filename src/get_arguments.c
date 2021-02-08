/*
** EPITECH PROJECT, 2021
** strace
** File description:
** get_arguments.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "strace.h"

static int do_switch_arguments(strace_t *strace_info, int c, char *exec_name)
{
	switch (c) {
	case 's':
		strace_info->detail = true;
		break;
	case 'p':
		strace_info->target_pid = atoi(optarg);
		if (strace_info->target_pid <= 0) {
			printf("Invalid argument '%s': it must be a integer"
				" greater than 0\n", optarg);
			return (ERR_RET);
		}
		break;
	case 'h':
		printf(USAGE, exec_name);
		exit(EXIT_SUCCESS);
	default:
		fprintf(stderr, USAGE, exec_name);
		return (ERR_RET);
	}
	return (EXIT_SUCCESS);
}

int get_arguments(strace_t *strace_info, int ac, char **av, char **env)
{
	struct option opt_long[3];
	int c;

	if (ac == 1) {
		printf(USAGE, av[0]);
		return (ERR_RET);
	}
	memset(strace_info, 0, sizeof(strace_t));
	opt_long[0] = (struct option){ "detail", 0, NULL, 's' };
	opt_long[1] = (struct option){ "pid", 1, NULL, 'p' };
	opt_long[2] = (struct option){ "help", 0, NULL, 'h' };
	for (c = getopt_long(ac, av, ARGS, opt_long, NULL); c != -1;
		c = getopt_long(ac, av, ARGS, opt_long, NULL)) {
		if (do_switch_arguments(strace_info, c, av[0]))
			return (ERR_RET);
	}
	if (optind < ac)
		strace_info->command = av + optind;
	strace_info->env = env;
	return (EXIT_SUCCESS);
}

