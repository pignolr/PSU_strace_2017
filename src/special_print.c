/*
** EPITECH PROJECT, 2018
** strace
** File description:
** special_print.c
*/

#include <sys/stat.h>
#include <sys/ptrace.h>
#include <stdio.h>
#include "syscalls.h"

static int fstat_returns(strace_t *info, int len)
{
	while (len < 40)
		len += fprintf(stderr, " ");
	fprintf(stderr, "= ");
	if (print_int(info, info->regs.rax) < 0)
		return (ERR_RET);
	fprintf(stderr, "\n");
	return (0);
}

int print_fstat(strace_t *info, unsigned long *regs)
{
	struct stat tmp;
	int len;
	int ret;

	tmp.st_mode = (mode_t)ptrace(PTRACE_PEEKTEXT, info->target_pid,
		regs[1] + ((long)&tmp.st_mode - (long)&tmp), NULL);
	tmp.st_size = (off_t)ptrace(PTRACE_PEEKTEXT, info->target_pid,
		regs[1] + ((long)&tmp.st_size - (long)&tmp), NULL);
	ret = print_int(info, regs[0]);
	if (ret < 0)
		return (ERR_RET);
	len = 6 + ret + fprintf(stderr, ", {st_mode=%d, st_size=%li, ...}) ",
		tmp.st_mode, tmp.st_size);
	return (fstat_returns(info, len));
}

static int nanosleep_returns(strace_t *info, int len)
{
	len += fprintf(stderr, ") ");
	while (len < 39)
		len += fprintf(stderr, " ");
	fprintf(stderr, "= ");
	if (print_int(info, info->regs.rax) < 0)
		return (ERR_RET);
	fprintf(stderr, "\n");
	return (0);
}

int print_nanosleep(strace_t *info, unsigned long *regs)
{
	struct timespec tmp;
	int len;
	int ret;

	tmp.tv_sec = (time_t)ptrace(PTRACE_PEEKTEXT, info->target_pid,
		regs[0] + ((long)&tmp.tv_sec - (long)&tmp), NULL);
	tmp.tv_nsec = (long)ptrace(PTRACE_PEEKTEXT, info->target_pid,
		regs[0] + ((long)&tmp.tv_nsec - (long)&tmp), NULL);
	len = 10 + fprintf(stderr, "{tv_sec=%lu, tv_nsec=%li}, ",
		tmp.tv_sec, tmp.tv_nsec);
	ret = print_ptr(info, regs[1]);
	if (ret < 0)
		return (ERR_RET);
	len += ret;
	return (nanosleep_returns(info, len));
}