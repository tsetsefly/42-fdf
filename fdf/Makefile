# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtse <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/15 14:55:24 by dtse              #+#    #+#              #
#    Updated: 2016/11/15 14:55:26 by dtse             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		fdf.a
FILENAMES	=		fdf.c					\
					rotation.c				\
					superstruct_setup.c		\
					file_handling.c			\
					debugging_functions.c	\
					draw.c					\
					key_press.c				\
					angle_wrangler.c		\
					error_checking.c

CC			=		gcc
CFLAGS		+=		-Wall -Wextra -Werror
CFLAGS		+=		-I includes/

SRCS		=		$(addprefix srcs/, $(FILENAMES))
OBJS		=		$(addprefix build/, $(FILENAMES:.c=.o))

LIBFT		=		./libft/libft.a
LIBINC		=		-I./libft
LIBLINK		=		-L./libft -lft

LIBMLX		=		./minilibx_macos/libmlx.a 
LIBMLXINC	=		-I./minilibx_macos/
LIBMLXLINK	=		-L./minilibx_macos -lmlx -framework OpenGL -framework AppKit -Iminilibx_macos

.PHONY:	all clean fclean re

all: libft libmlx $(NAME)

build:
	mkdir $@

build/%.o: srcs/%.c | build
	$(CC) $(CFLAGS) $(LIBINC) $(LIBMLXINC) -o $@ -c $<

libft: $(LIBFT)

$(LIBFT):
	make -C ./libft

libmlx: $(LIBMLX)

$(LIBMLX):
	make -C ./libmlx

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBLINK) $(LIBMLXLINK) -o $@ $^ -fsanitize=address

clean: rm -rf build/

fclean: clean
	rm -f $(NAME)

re: fclean all

