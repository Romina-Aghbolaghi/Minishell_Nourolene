# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romina <romina@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:45:57 by rmohamma          #+#    #+#              #
#    Updated: 2024/04/21 16:06:17 by romina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRC		=		libft/ft_isalpha.c \
	  			libft/ft_isdigit.c \
	  			libft/ft_isalnum.c \
	  			libft/ft_isascii.c \
	  			libft/ft_isprint.c \
	  			libft/ft_strlen.c \
	  			libft/ft_memset.c \
	  			libft/ft_bzero.c \
	  			libft/ft_memcpy.c \
	  			libft/ft_memmove.c \
				libft/ft_strcpy.c \
	  			libft/ft_strlcpy.c \
	  			libft/ft_strlcat.c \
	  			libft/ft_toupper.c \
	  			libft/ft_tolower.c \
	  			libft/ft_strchr.c \
	  			libft/ft_strrchr.c \
				libft/ft_strcmp.c \
	  			libft/ft_strncmp.c \
	  			libft/ft_memchr.c \
	  			libft/ft_memcmp.c \
	  			libft/ft_strnstr.c \
	  			libft/ft_atoi.c \
	  			libft/ft_calloc.c \
	  			libft/ft_strdup.c \
	  			libft/ft_substr.c \
	  			libft/ft_strjoin.c \
	  			libft/ft_strtrim.c \
	  			libft/ft_split.c \
	  			libft/ft_itoa.c \
	  			libft/ft_strmapi.c \
	  			libft/ft_striteri.c \
	  			libft/ft_putchar_fd.c \
	  			libft/ft_putstr_fd.c \
				libft/ft_putendl_fd.c \
	  			libft/ft_putnbr_fd.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				printf/ft_printf.c \
				printf/ft_printbase.c \
				printf/ft_putstr.c \
				printf/ft_putchar.c \
				printf/ft_putnbr.c \
				printf/ft_unsign.c \
				printf/ft_upperhex.c \
				printf/ft_lowerhex.c \
				printf/ft_point.c \
				

SRC_BONUS	=	libft/ft_lstnew.c \
				libft/ft_lstadd_front.c \
				libft/ft_lstsize.c \
				libft/ft_lstlast.c \
				libft/ft_lstadd_back.c \
				libft/ft_lstdelone.c \
				libft/ft_lstclear.c \
				libft/ft_lstiter.c \
				libft/ft_lstmap.c \


OBJ		=	${SRC:%.c=%.o}

OBJ_BONUS	=	${SRC_BONUS:%.c=%.o}

HEADER		=	libft.h

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

all:	$(NAME)

%.o: %.c $(HEADER)
		@$(CC) -c $(CFLAGS) -o $@ $<
		
		
$(NAME): $(OBJ) $(OBJ_BONUS)
		@ar rc $(NAME) $^
#		@echo  "$(GREEN)Libft: Mandatory created!$(DEFAULT)"
clean:
	@rm -f $(OBJ) $(OBJ_BONUS)
#	@echo  "$(YELLOW)Libft: object files deleted!$(DEFAULT)"
	
fclean:	clean
	@rm -f $(NAME)
#	@echo  "$(RED)Libft: all deleted!$(DEFAULT)"
	
re:	fclean all

.PHONY: all clean fclean re

#COLORS
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
DEFAULT	= \033[0m
