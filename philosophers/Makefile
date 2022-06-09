SRCS_DIR = srcs/

SRCS=	action.c \
		init.c \
		main.c \
		utils.c \

OBJ_DIR = objs/

OBJS = ${SRCS:%.c=${OBJ_DIR}%.o}

NAME= philo

CC= gcc

FLAGS= -Wall -Wextra -Werror

LEAKS= -g3 -fsanitize=thread

INC_DIR = incs

INCLUDES =	${INC_DIR}/philo.h

${OBJ_DIR}%.o : ${SRCS_DIR}%.c	${INCLUDES}
				mkdir -p objs
				${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

${NAME}:	Makefile ${OBJS}
			${CC} ${FLAGS} ${LEAKS} ${OBJS} -o ${NAME}

clean:
			rm -f ${OBJS}
			rm -rf objs

fclean:		clean
			rm -f ${NAME}

re:			fclean all

PHONY= all clean fclean re