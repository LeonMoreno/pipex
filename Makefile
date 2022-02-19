#Standard

NAME 		= pipex
INCLUDES	= include/
SRC_DIR		= src/
CC 			= gcc
CFLAGS		= -g -Wall -Wextra -Werror -I
RM		= rm -f

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

#sources

SRC_FILES	=	pipex.c start.c startChilds.c parserPath.c utils_pipex.c


SRC 		= 	$(addprefix $(SRC_DIR), $(SRC_FILES))


OBJ 		= 	$(SRC:.c=.o)


###
all:		$(NAME)

$(NAME):	$(OBJ)
			@echo "$(GRAY)     - Making libft... $(DEF_COLOR)"
			@make -C $(LIBFT_DIR)
			$(CC) $(OBJ) $(LIBFT) -o $(NAME) $(MLX)
			@echo "$(GREEN)pipex compiled!$(DEF_COLOR)"

.c.o :
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

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
