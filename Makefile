##
## EPITECH PROJECT, 2018
## strace
## File description:
## Makefile
##

CC		= gcc

CFLAGS		+= -W -Wall -Wextra -Werror

CPPFLAGS	+= -Iinc -D_GNU_SOURCE

LDFLAGS		+=

LDLIBS		+=

NAME		= strace

SRCS		=\
		src/init_trace.c \
		src/strace.c \
		src/print_exit.c \
		src/get_arguments.c \
		src/print_syscall.c \
		src/print_number.c \
		src/print_string.c \
		src/print_read.c \
		src/special_print.c \
		src/print_no_s.c \
		src/main.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
