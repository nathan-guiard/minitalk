# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 15:42:20 by nguiard           #+#    #+#              #
#    Updated: 2022/02/14 14:29:12 by nguiard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_SERV =  srcs/server_main.c		\
			srcs/server_signals.c	\

SRC_CLT = srcs/client_main.c		\
			srcs/client_signals.c	\

SRC_SERV_BONUS =  srcs_bonus/server_main.c		\
			srcs_bonus/server_signals.c			\

SRC_CLT_BONUS = srcs_bonus/client_main.c		\
			srcs_bonus/client_signals.c			\

CFLAGS = -Wall -Wextra -Werror

OBJ_SERV_BONUS = ${SRC_SERV_BONUS:.c=.o}

OBJ_CLT_BONUS = ${SRC_CLT_BONUS:.c=.o}

OBJ_SERV = ${SRC_SERV:.c=.o}

OBJ_CLT = ${SRC_CLT:.c=.o}

LIBFT_OBJ = libft/*.o libft/libft.a

NAME = minitalk

NAME_SERV = server

NAME_CLT = client

NAME_SERV_BONUS = server_bonus

NAME_CLT_BONUS = client_bonus

INCLUDE = -Iinclude/

LIBFT = libft/libft.a

CC = gcc

nb:=1

color:=6

all: ${NAME_CLT} ${NAME_SERV}

.c.o:
	@${CC} ${CLFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}
	@printf "\r\033[0;3%dmCompilation de l'objet %d terminee\033[0m" "$(color)" "$(nb)"
	$(eval nb=$(shell echo $$(($(nb)+1))))

${NAME_CLT}: ${OBJ_CLT}
	@make -C libft
	@printf "\n\033[0;34m"
	@${CC} ${INCLUDE} ${LIBFT} ${OBJ_CLT} -o ${NAME_CLT}
	@echo "\033[1;92m\nclient pret!\n\033[0m"
	$(eval nb=1)
	$(eval color=5)

${NAME_SERV}: ${OBJ_SERV}
	@printf '\033[0;35m'
	@${CC} ${INCLUDE} ${LIBFT} ${OBJ_SERV} -o ${NAME_SERV}
	@echo "\033[1;92m\nserver pret!\n\033[0m"

bonus: ${NAME_CLT_BONUS} ${NAME_SERV_BONUS}

${NAME_CLT_BONUS}: ${OBJ_CLT_BONUS}
	@make all -C libft
	@printf "\n\033[0;34m"
	@${CC} ${INCLUDE} ${LIBFT} ${OBJ_CLT_BONUS} -o ${NAME_CLT_BONUS}
	@echo "\033[1;92m\nclient pret!\n\033[0m"
	$(eval nb=1)
	$(eval color=5)

${NAME_SERV_BONUS}: ${OBJ_SERV_BONUS}
	@printf '\033[0;35m'
	@${CC} ${INCLUDE} ${LIBFT} ${OBJ_SERV_BONUS} -o ${NAME_SERV_BONUS}
	@echo "\033[1;92m\nserver pret!\n\033[0m"

clean:
	@make clean -C libft
	@rm -f ${OBJ_CLT} ${OBJ_SERV} ${OBJ_SERV_BONUS} ${OBJ_CLT_BONUS}
	@echo "clean ok!"

fclean:
	@make fclean -C libft
	@rm -f ${OBJ_CLT} ${OBJ_SERV} ${OBJ_SERV_BONUS} ${OBJ_CLT_BONUS} ${NAME_SERV} ${NAME_CLT} ${NAME_CLT_BONUS} ${NAME_SERV_BONUS}
	@echo "fclean ok!"

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: ${OBJ_CLT} ${OBJ_CLT_BONUS} ${OBJ_SERV} ${OBJ_SERV_BONUS}
