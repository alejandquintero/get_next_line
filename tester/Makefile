# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/25 17:47:25 by aquinter          #+#    #+#              #
#    Updated: 2023/11/25 19:54:41 by aquinter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.exe

NAME_BONUS = gnl_bonus.exe

FS = -fsanitize=address

RM = rm -f

CC = gcc

CFLAGS = -Wextra -Wall -Werror

SRC = gnl/get_next_line.c gnl/get_next_line_utils.c main.c

SRC_BONUS = gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c \
			main_bonus.c

ifeq ($(strip $(BUFFER_SIZE)),)
    BUFFER_SIZE_FLAG =
else
    BUFFER_SIZE_FLAG = -D BUFFER_SIZE=$(BUFFER_SIZE)
endif

all:
	${CC} ${CFLAGS} -o ${NAME} ${SRC} ${FS} ${BUFFER_SIZE_FLAG}

bonus:
	${CC} ${CFLAGS} -o ${NAME_BONUS} ${SRC_BONUS} ${FS} ${BUFFER_SIZE_FLAG}

fclean:
	${RM} ${NAME} ${NAME_BONUS}

re:	fclean all
