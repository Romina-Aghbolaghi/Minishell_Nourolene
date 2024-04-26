# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romina <romina@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 13:55:38 by cbiteau           #+#    #+#              #
#    Updated: 2024/04/26 12:27:46 by romina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

AUTHOR	=  Romina - The MinHell
DATE	= 21/04/2024

SRC_DIR		=	Srcs/
OBJ_DIR		=	objs/
INC_DIR 	=	Includes/
LIBFT_PATH	=	libft/
READLINE_LIB	=	-lreadline -lhistory -L/usr/local/lib

SRC_FILES	=	Minishell/minishell.c Minishell/minishell_utils.c \
				Signals/signals.c \
				Envirenments/env.c Envirenments/env_utils.c \
				Initialization/initialization.c Initialization/initialization2.c\
				Free/free_env.c Free/free.c Free/free_all.c\
				Errors/errors.c \
				Token/create_token.c Token/token_utils.c Token/quotes.c Token/get_index.c \
				Token/word.c  Token/dollar.c\
				Parsing/parsing.c Parsing/parsing_utils.c \
				Execution/cmd_execution.c \
				Builtins/builtins_utils.c 



				
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
DEP			=	$(OBJ:.o=.d)

CC			=	clang
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g3
CPPFLAGS	=	-I/usr/local/include -I$(LIBFT_PATH) -I$(INC_DIR) 
LIBFT		=	$(LIBFT_PATH)/libft.a



COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[KO]"
WARN_STRING  = "[WARN]"
COM_STRING   = "Compiling"

define run
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

	
all:	$(LIBFT) $(NAME) header  

header:
	@printf "%b" "$(OK_COLOR)"
	@echo "        ___  _____ ___  ___      _        "
	@echo "       /   |/ __  \|  \/  |     | |       "
	@echo "      / /| |\`' / /'| .  . | __ _| | _____ "
	@echo "     / /_| |  / /  | |\/| |/ _\` | |/ / _ \\"
	@echo "     \___  |./ /___| |  | | (_| |   <  __/"
	@echo "         |_/\_____/\_|  |_/\__,_|_|\_\___|"
	@echo
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)\n"
	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date: 	$(WARN_COLOR)$(DATE)\n\033[m"
	@echo




	
# all:	 $(NAME) $(LIBFT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) all
	
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(READLINE_LIB) -o $@ $(OBJ) $(LIBFT)
	@echo  "$(GREEN)Minishell: Mandatory created!$(DEFAULT)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -o $@ -c $<

-include $(DEP)

clean:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@$(RM) -r $(OBJ_DIR)
	@echo  "$(YELLOW)Minishell: object files deleted!$(DEFAULT)"

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@$(RM) $(NAME) $(LIBFT)
	@echo  "$(RED)Minishell: all deleted!$(DEFAULT)"
	
re: fclean all 

.PHONY: all clean fclean re

#COLORS
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
DEFAULT	= \033[0m
			












# NAME	= minishell
# CC 		= clang
# CFLAGS	= -Wall -Werror -Wextra -g
# LIBFT	= libft/
# AUTHOR	= Romina - The Mini Crushers
# DATE	= 21/04/2024

# SRCS		= 	Minishell/main_utils.c \
#             Signals/signals.c \
#             Envirenments/env.c Envirenments/env_utils.c \
#             Initialization/initialization.c \
#             Free/free_env.c Free/free.c Free/free_all.c\
#             Errors/errors.c \
#             Token/create_token.c Token/token_utils.c Token/quotes.c Token/get_index.c \
#             Token/word.c  Token/dollar.c\
#             Parsing/parsing.c Parsing/parsing_utils.c

# MAIN		= main.c

# OBJ_MAIN	= $(addprefix objs/, ${MAIN:.c=.o})
# OBJS		= $(addprefix objs/, ${SRCS:.c=.o})
# OBJS_TESTS	= $(addprefix objs_tests/, ${SRCS_TESTS:.c=.o})

# COM_COLOR   = \033[0;34m
# OBJ_COLOR   = \033[0;36m
# OK_COLOR    = \033[0;32m
# ERROR_COLOR = \033[0;31m
# WARN_COLOR  = \033[0;33m
# NO_COLOR    = \033[m

# OK_STRING    = "[OK]"
# ERROR_STRING = "[KO]"
# WARN_STRING  = "[WARN]"
# COM_STRING   = "Compiling"

# define run
# printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
# $(1) 2> $@.log; \
# RESULT=$$?; \
# if [ $$RESULT -ne 0 ]; then \
#   printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
# elif [ -s $@.log ]; then \
#   printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
# else  \
#   printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
# fi; \
# cat $@.log; \
# rm -f $@.log; \
# exit $$RESULT
# endef

# all:	header $(NAME)

# header:
# 	@printf "%b" "$(OK_COLOR)"
# 	@echo "        ___  _____ ___  ___      _        "
# 	@echo "       /   |/ __  \|  \/  |     | |       "
# 	@echo "      / /| |\`' / /'| .  . | __ _| | _____ "
# 	@echo "     / /_| |  / /  | |\/| |/ _\` | |/ / _ \\"
# 	@echo "     \___  |./ /___| |  | | (_| |   <  __/"
# 	@echo "         |_/\_____/\_|  |_/\__,_|_|\_\___|"
# 	@echo
# 	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)\n"
# 	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)\n"
# 	@printf "%b" "$(OBJ_COLOR)Date: 	$(WARN_COLOR)$(DATE)\n\033[m"
# 	@echo

# $(NAME): 	$(LIBFT) ${OBJS} ${OBJ_MAIN}
# 			@$(call run,$(CC) $(CFLAGS) -o $@ ${OBJS} ${OBJ_MAIN} -L./libft -lft -lreadline -lncurses)

# objs/%.o: 	Srcs/%.c
# 			@mkdir -p $(dir $@)
# 			@$(call run,$(CC) $(CFLAGS) -c $< -o $@)

# $(LIBFT):
# 			@$(call run,make -sC ./libft libft.a)

# clean:		header
# 			@rm -rf objs
# 			@make -sC ./libft clean
# 			@printf "%-53b%b" "$(COM_COLOR)clean:" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"

# fclean:		header clean
# 			@rm -rf $(NAME)
# 			@make -sC ./libft fclean
# 			@printf "%-53b%b" "$(COM_COLOR)fclean:" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"

# re:			fclean all

# .PHONY:		all clean fclean re libft header
