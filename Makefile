# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 13:04:11 by ljalikak          #+#    #+#              #
#    Updated: 2019/04/04 13:04:14 by ljalikak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall
## -Wextra -Werror
NAME = corewar
LIBSRC = ./libft/
LIB = $(LIBSRC)libft.a
HDR = ./includes/
HDR1 = $(HDR)ft_corewar.h \
$(HDR)ft_corewar_enum.h \
$(HDR)ft_corewar_struct.h \
$(HDR)op.h

SRC = ./sources/
SRC1 = main.c \
print.c \
print_incurses.c \
create_del_errors.c \
operations.c \
arg_for_operations.c \
create_players.c \
validations.c \
windous.c \
work_with_memory.c \
incurses_colors.c

OBJS = $(SRC1:.c=.o)

.PHONY: clean all fclean re lib_refresh norm

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) -lncurses $(LIB) $(OBJS)

$(LIB):
	@make lib_refresh

%.o: $(SRC)%.c $(HDR1)
	$(CC) $(CFLAGS) -c $< -I $(HDR) -I $(LIBSRC)

lib_refresh:
	make -C $(LIBSRC)

norm:
	norminette -R CheckForbiddenSourceHeader

clean:
	rm -rf $(OBJS)
	@make -C $(LIBSRC) clean

fclean: clean
	@rm -rf $(NAME)
	make -C $(LIBSRC) fclean

re: fclean all
