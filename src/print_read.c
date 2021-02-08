/*
** EPITECH PROJECT, 2018
** strace
** File description:
** print_read.c
*/

#include <sys/stat.h>
#include <sys/ptrace.h>
#include <stdio.h>
#include <ctype.h>
#include "syscalls.h"

static int read_returns(strace_t *info, unsigned long reg, int len)
{
	int ret;

	len += fprintf(stderr, ", ");
	ret = print_ulong(info, reg);
	if (ret < 0)
		return (ERR_RET);
	len += fprintf(stderr, ") ");
	while (len < 40)
		len += fprintf(stderr, " ");
	fprintf(stderr, "= ");
	if (print_int(info, info->regs.rax) < 0)
		return (ERR_RET);
	fprintf(stderr, "\n");
	return (0);
}

int print_read(strace_t *info, unsigned long *regs)
{
	int len;
	unsigned char c;
	unsigned int i;

	len = print_int(info, regs[0]);
	if (len < 0)
		return (ERR_RET);
	len += fprintf(stderr, ", \"");
	for (i = 0; i < 32 && i < regs[2]; ++i) {
		c = (int)ptrace(PTRACE_PEEKTEXT, info->target_pid, regs[1] + i,
			NULL);
		if (isprint(c))
			len += fprintf(stderr, "%c", c);
		else
			len += fprintf(stderr, "\\%o", (int)c);
	}
	len += fprintf(stderr, "\"");
	if (i == 32)
		len += fprintf(stderr, "...");
	return (read_returns(info, regs[2], len));
}