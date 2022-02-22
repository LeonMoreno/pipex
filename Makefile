#Standard

NAME 		= pipex
INCLUDES	= include/
SRC_DIR		= src/
BONUS_DIR	= bonus/
CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror -I
RM			= rm -f

#Libft
LIBFT_A		= libft.a
LIBFT_DIR	= libft/
LIBFT  = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#sources Mandatory
SRC_FILES	=	pipex.c startChilds.c parserPath.c utils_pipex.c error_pipex.c
SRC 		= 	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		= 	$(SRC:.c=.o)

#Bonus Sources
SRC_BONUS_FILES = pipex_bonus.c start_bonus.c startChilds_bonus.c parserPath_bonus.c utils_pipex_bonus.c error_pipex_bonus.c
SRC_BONUS		= $(addprefix $(BONUS_DIR), $(SRC_BONUS_FILES))
OBJ_BONUS		= $(SRC_BONUS:.c=.o)

###
all:		$(NAME)

$(NAME):	$(OBJ)
			@echo "$(GRAY)     - Making libft... $(DEF_COLOR)"
			@make -C $(LIBFT_DIR)
			$(CC) $(OBJ) $(LIBFT) -o $(NAME)
			@echo "$(GREEN)pipex compiled!$(DEF_COLOR)"

.c.o :
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

bonus	:	$(OBJ_BONUS)
			@echo "$(GRAY)     - Making libft... $(DEF_COLOR)"
			@make -C $(LIBFT_DIR)
			$(CC) $(OBJ_BONUS) $(LIBFT) -o $(NAME)
			@echo "$(GREEN)pipex Bonus compiled!$(DEF_COLOR)"

clean:
			@$(RM) -rf $(OBJ) $(OBJ_BONUS)
			@make -C $(LIBFT_DIR) clean
			@echo "$(BLUE)PiPEX objects files cleaned!$(DEF_COLOR)"

fclean:				clean
				@$(RM) -f $(NAME)
				@make -C $(LIBFT_DIR) fclean
				@echo "$(CYAN)PiPEX executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for PiPeX!$(DEF_COLOR)"
norm:
			@norminette $(SRC) $(INCLUDES) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm
