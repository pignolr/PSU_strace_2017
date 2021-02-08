/*
** EPITECH PROJECT, 2018
** strace
** File description:
** print_number.c
*/

#include <sys/ptrace.h>
#include <stdio.h>
#include "syscalls.h"

int print_ulong(strace_t *info __attribute__((unused)), unsigned long reg)
{
	return (fprintf(stderr, "%lu", (unsigned long)reg));
}

int print_long(strace_t *info __attribute__((unused)), unsigned long reg)
{
	return (fprintf(stderr, "%li", (long)reg));
}

int print_int(strace_t *info __attribute__((unused)), unsigned long reg)
{
	return (fprintf(stderr, "%d", (int)reg));
}

int print_uint(strace_t *info __attribute__((unused)), unsigned long reg)
{
	return (fprintf(stderr, "%u", (unsigned int)reg));
}

int print_hex(strace_t *info __attribute__((unused)), unsigned long reg)
{
	return (fprintf(stderr, "0x%lx", reg));
}