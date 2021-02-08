/*
** EPITECH PROJECT, 2021
** strace
** File description:
** attach.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include "strace.h"

static void exec_command(char **command, char **env)
{
	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
		perror("Error ptrace PTRACE_TRACEME");
		exit(ERR_RET);
	}
	if (execvpe(command[0], command, env) == -1) {
		perror("Error execvp");
		exit(ERR_RET);
	}
}

static int trace_command(strace_t *strace_info)
{
	if (waitpid(strace_info->target_pid, &strace_info->status, 0) == -1) {
		perror("Error waitpid");
		return (ERR_RET);
	}
	if (ptrace(PTRACE_SETOPTIONS, strace_info->target_pid, NULL,
		PTRACE_O_TRACEEXEC | PTRACE_O_TRACEEXIT) == -1) {
		perror("Error ptrace PTRACE_OPTION");
		return (ERR_RET);
	}
	if (strace_info->detail)
		fprintf(stderr, "execve(\"%s\", %p, %p) = 0x0\n",
			strace_info->command[0], strace_info->command,
			strace_info->env);
	else
		fprintf(stderr, "execve(%p, %p, %p) = 0x0\n",
			strace_info->command[0], strace_info->command,
			strace_info->env);
	return (0);
}

static int exec_and_trace_command(strace_t *strace_info)
{
	strace_info->target_pid = fork();
	if (strace_info->target_pid == -1) {
		perror("Error fork");
		return (ERR_RET);
	} else if (strace_info->target_pid != 0) {
		return (trace_command(strace_info));
	} else {
		exec_command(strace_info->command, strace_info->env);
		return (0);
	}
}

static int trace_pid(pid_t pid)
{
	if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
		perror("Error ptrace PTRACE_ATTACH");
		return (ERR_RET);
	}
	return (0);
}

int init_trace(strace_t *strace_info)
{
	if (strace_info->target_pid)
		return (trace_pid(strace_info->target_pid));
	else
		return (exec_and_trace_command(strace_info));
}
