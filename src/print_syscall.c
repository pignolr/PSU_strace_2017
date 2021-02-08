/*
** EPITECH PROJECT, 2018
** strace
** File description:
** print_syscall.c
*/

#include <stdio.h>
#include "syscalls.h"

static int print_loop(strace_t *info, unsigned long *regs)
{
	int i;
	int j;
	int len;
	int ret;

	len = 0;
	for (i = 0; i < syscall_tab_g[info->regs.orig_rax].n_args; ++i) {
		for (j = 0; j < MAX_TYPE; ++j) {
			if (syscall_tab_g[info->regs.orig_rax].args[i]
				== print_ptr_g[j].type)
				ret = print_ptr_g[j].func(info, regs[i]);
			if (ret < 0)
				return (ERR_RET);
		}
		len += ret;
		if (i + 1 < syscall_tab_g[info->regs.orig_rax].n_args)
			len += fprintf(stderr, ", ");
	}
	return (len);
}

static int cleaner_print(strace_t *info)
{
	int i;
	int ret;

	fprintf(stderr, "= ");
	if (syscall_tab_g[info->regs.orig_rax].ret == VOID)
		fprintf(stderr, "?");
	else {
		for (i = 0; i < MAX_TYPE; ++i) {
			if (syscall_tab_g[info->regs.orig_rax].ret
				== print_ptr_g[i].type)
				ret = print_ptr_g[i].func(info, info->regs.rax);
			if (ret < 0)
				return (ERR_RET);
		}
	}
	fprintf(stderr, "\n");
	return (0);
}

static int clean_print(strace_t *info, unsigned long *regs)
{
	int ret;
	int len;

	len = fprintf(stderr, "%s(", syscall_tab_g[info->regs.orig_rax].name);
	if (syscall_tab_g[info->regs.orig_rax].print_f != 0)
		return (syscall_tab_g[info->regs.orig_rax].print_f(info, regs));
	if (syscall_tab_g[info->regs.orig_rax].args[0] != VOID) {
		ret = print_loop(info, regs);
		if (ret < 0)
			return (ERR_RET);
		len += ret;
	}
	len += fprintf(stderr, ") ");
	while (len < 40)
		len += fprintf(stderr, " ");
	return (cleaner_print(info));
}

int print_syscall(strace_t *info)
{
	unsigned long regs[REG_MAX_IDX];

	regs[REG_RDI_IDX] = info->regs.rdi;
	regs[REG_RSI_IDX] = info->regs.rsi;
	regs[REG_RDX_IDX] = info->regs.rdx;
	regs[REG_RCX_IDX] = info->regs.rcx;
	regs[REG_R8_IDX] = info->regs.r8;
	regs[REG_R9_IDX] = info->regs.r9;
	if (info->detail == false)
		return (rough_print(info, regs));
	return (clean_print(info, regs));
}