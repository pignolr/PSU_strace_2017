/*
** EPITECH PROJECT, 2018
** strace
** File description:
** print_string.c
*/

#include <sys/ptrace.h>
#include <stdio.h>
#include <ctype.h>
#include "syscalls.h"

int print_str(strace_t *info, unsigned long reg)
{
	int i;
	int len;
	char c;

	c = 1;
	if (reg == 0)
		return (fprintf(stderr, "NULL"));
	len = fprintf(stderr, "\"");
	for (i = 0; i < 32 && c; ++i) {
		c = ptrace(PTRACE_PEEKTEXT, info->target_pid, reg + i, NULL);
		if (isprint(c) && c)
			len += fprintf(stderr, "%c", c);
		else if (c)
			len += fprintf(stderr, "\\%o", (int)c);
	}
	len += fprintf(stderr, "\"");
	if (i == 32)
		len += fprintf(stderr, "...");
	return (len);
}

int print_ptr(strace_t *info __attribute__((unused)), unsigned long reg)
{
	if (reg == 0)
		return (fprintf(stderr, "NULL"));
	return (fprintf(stderr, "0x%llx", (long long)reg));
}