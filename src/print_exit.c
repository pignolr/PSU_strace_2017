/*
** EPITECH PROJECT, 2021
** strace
** File description:
** print_exit.c
*/

#include <stdio.h>
#include <sys/ptrace.h>
#include "strace.h"

int print_exit(strace_t *strace_info)
{
	long ret;

	if (ptrace(PTRACE_GETEVENTMSG, strace_info->target_pid, NULL, &ret)
		== -1) {
		perror("Error ptrace PTRACE_GETEVENTMSG");
		return (ERR_RET);
	}
	fprintf(stderr, "+++ exited with %d +++\n", (char)ret);
	return (0);
}
