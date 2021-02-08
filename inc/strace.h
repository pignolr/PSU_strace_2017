/*
** EPITECH PROJECT, 2018
** strace
** File description:
** strace.h
*/

#ifndef STRACE_STRACE_H_
#define STRACE_STRACE_H_

#include <stdbool.h>
#include <sys/types.h>
#include <sys/user.h>

#define USAGE "USAGE: %s [-s] [-p <pid>|<command>]\n"
#define ERR_RET 84
#define ARGS "+hsp:"

#define OPCODE_SYSCALL 0x050f

typedef enum e_reg_args {
	REG_RDI_IDX = 0,
	REG_RSI_IDX = 1,
	REG_RDX_IDX = 2,
	REG_RCX_IDX = 3,
	REG_R8_IDX = 4,
	REG_R9_IDX = 5,
	REG_MAX_IDX = 6
} t_reg_args;

typedef struct strace_s {
	bool detail;
	char **command;
	char **env;
	pid_t target_pid;
	int status;
	struct user_regs_struct regs;
} strace_t;

int get_arguments(strace_t *strace_info, int ac, char **av, char **env);
int init_trace(strace_t *strace_info);
int strace(strace_t *strace_info);
int print_syscall(strace_t *strace_info);
int print_exit(strace_t *strace_info);

#endif /* !STRACE_STRACE_H_ */
