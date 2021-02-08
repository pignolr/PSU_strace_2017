/*
** EPITECH PROJECT, 2018
** strace
** File description:
** print_syscall.c
*/

#include <stdio.h>
#include "syscalls.h"

int rough_print(strace_t *info, unsigned long *regs)
{
	int i;

	fprintf(stderr, "%s(", syscall_tab_g[info->regs.orig_rax].name);
	for (i = 0; i < syscall_tab_g[info->regs.orig_rax].n_args; ++i) {
		if (print_hex(info, regs[i]) < 0)
			return (ERR_RET);
		if (i + 1 < syscall_tab_g[info->regs.orig_rax].n_args)
			fprintf(stderr, ", ");
	}
	fprintf(stderr, ") = ");
	if (syscall_tab_g[info->regs.orig_rax].ret == VOID)
		fprintf(stderr, "?");
	else if (print_hex(info, info->regs.rax) < 0)
		return (ERR_RET);
	fprintf(stderr, "\n");
	return (0);
}
