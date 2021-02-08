/*
** EPITECH PROJECT, 2021
** strace
** File description:
** strace.c
*/

#include <stdio.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include "strace.h"

static int do_single_step(strace_t *strace_info)
{
	if (ptrace(PTRACE_SINGLESTEP, strace_info->target_pid, NULL, NULL)
		== -1) {
		perror("Error ptrace PTRACE_SINGLESTEP");
		return (ERR_RET);
	}
	if (waitpid(strace_info->target_pid, &strace_info->status, 0) == -1) {
		perror("Error waitpid");
		return (ERR_RET);
	}
	return (0);
}

static int analyse_opcode(strace_t *strace_info)
{
	if (do_single_step(strace_info))
		return (ERR_RET);
	if (!WIFSTOPPED(strace_info->status))
		return (0);
	if (ptrace(PTRACE_GETREGS, strace_info->target_pid, NULL,
		&strace_info->regs)) {
		perror("Error ptrace PTRACE_GETREGS");
		return (ERR_RET);
	}
	return (print_syscall(strace_info));
}

static int analyse_trap(strace_t *strace_info)
{
	unsigned short ret;

	if (ptrace(PTRACE_GETREGS, strace_info->target_pid, NULL,
		&strace_info->regs)) {
		perror("Error ptrace PTRACE_GETREGS");
		return (ERR_RET);
	}
	ret = (unsigned short)ptrace(PTRACE_PEEKTEXT, strace_info->target_pid,
		strace_info->regs.rip, NULL);
	if (errno != 0) {
		perror("Error ptrace PTRACE_PEEKTEXT");
		return (ERR_RET);
	}
	if (ret == OPCODE_SYSCALL)
		return (analyse_opcode(strace_info));
	else
		return (0);
}

static int analyse_status(strace_t *strace_info)
{
	if (strace_info->status >> 8 == (SIGTRAP | (PTRACE_EVENT_EXEC << 8)))
		return (print_syscall(strace_info));
	if (WSTOPSIG(strace_info->status) == SIGTRAP)
		return (analyse_trap(strace_info));
	if (strace_info->status >> 16 == PTRACE_EVENT_EXIT)
		return (print_exit(strace_info));
	return (0);
}

int strace(strace_t *strace_info)
{
	while (WIFSTOPPED(strace_info->status)) {
		if (analyse_status(strace_info) == ERR_RET)
			return (ERR_RET);
		if (do_single_step(strace_info) == ERR_RET)
			return (ERR_RET);
	}
	return (0);
}
