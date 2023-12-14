# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 23:19:26 by jlara-na          #+#    #+#              #
#    Updated: 2023/12/14 20:01:10 by jlara-na         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	fdf

#-----------DIR PATHS------------

SRC_DIR			:=		src/
OBJ_DIR			:=		obj/
LIB_DIR			:=		lib/
INC_DIR			:=		inc/
LFT_DIR			:=		$(LIB_DIR)libft/
MLX_DIR			:=		$(LIB_DIR)mlx/

#-----------CMP PARAM------------

CC				:=		gcc
CFLAGS			:=		-g -O3 -Wall -Wextra -Werror #-fsanitize=address
MLXCC			:=		-I mlx -L $(MLX_DIR) -lmlx
HEADER			:=		-I$(INC_DIR) -I$(LFT_DIR) -I$(MLX_DIR)
OPENGL			:=		-framework OpenGL -framework AppKit

#-----------ARCHIVE LIB----------

LIBFT			:=		$(LFT_DIR)libft.a
MLX				:=		$(MLX_DIR)libmlx.a

#-----------SHORT CUTS-----------

RM				:=		rm -f

#------------ANSI DEF------------

CLEAR			=		\033[2J\033[1;1H
DEF_COLOR		=		\033[0;39m
GRAY			=		\033[0;90m
RED				=		\033[0;91m
GREEN			=		\033[0;92m
YELLOW			=		\033[0;93m
YELLOWB			=		\033[0;93;5m
BLUE			=		\033[0;94m
MAGENTA			=		\033[0;95m
CYAN			=		\033[0;96m
WHITE			=		\033[0;97m

#---------SRC OBJ DEP INC---------

SRC_FILES		=		main			\
						setup			\
						map				\
						map_utils		\
						hooks_keydown	\
						draw			\
						draw_utils		\
						bresenham		\
						hooks_utils		\

SRC 			= 		$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 		$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 			= 		$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS			= 		$(addprefix $(INCLUDE), $(addsuffix .h, $(INC_FILES)))

#----------CACHE----------

OBJF			=		.cache_exists

#---------------------------------

all:	makelibs
			@$(MAKE) $(NAME)

makelibs:
			@echo "\n			$(YELLOWB)⚙$(YELLOW)COMPILING LIBFT...$(CYAN)			\n"
			@$(MAKE) -C $(LFT_DIR)
			@echo "\n			$(YELLOWB)⚙$(YELLOW)COMPILING MINILIBX...$(CYAN)			\n"
			@$(MAKE) -C	$(MLX_DIR)
			@echo "$(DEF_COLOR)"

-include	${DEPS}
$(NAME):	$(OBJ)
			@echo "\n$(BLUE)$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXCC) -o $(NAME)$(DEF_COLOR)\n"
			@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXCC) $(OPENGL) -o $(NAME)
			@echo "$(CLEAR)$(GREEN)			✔FDF COMPILED CORRECTLY\n$(DEF_COLOR)"

bonus:
			@$(MAKE) all

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS) | $(OBJF)
			@echo "$(YELLOWB)			⚙$(YELLOW)COMPILING: $< ...$(DEF_COLOR)"
			@$(CC) $(CFLAGS) -MMD -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

$(LIBFT):
			@make -C $(LFT_DIR)
			@echo "$(GREEN)LIBFT	COMPILED$(DEF_COLOR)"
$(MLX):
			@make -C $(MLX_DIR)
			@echo "$(GREEN)MLX		COMPILED$(DEF_COLOR)"

clean:
			@echo "$(CLEAR)\n			🧹SWEEPING THE FLOOR🧹\n"
			@make clean -sC $(LFT_DIR)
			@echo "$(CYAN)LIBFT				$(GREEN)CLEANED$(DEF_COLOR)"
			@make clean -sC $(MLX_DIR)
			@echo "$(CYAN)LMLX				$(GREEN)CLEANED$(DEF_COLOR)"
			@$(RM) -rf $(OBJ_DIR)
			@echo "$(CYAN)LFDF OBJ FILES			$(GREEN)CLEANED$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@echo "$(CYAN)FDF EXECUTABLE			$(GREEN)CLEANED$(DEF_COLOR)"
			@$(RM) -f $(MLX)
			@echo "$(CYAN)MLX .a				$(GREEN)CLEANED$(DEF_COLOR)"
			@$(RM) -f $(LIBFT)
			@echo "$(CYAN)LIBFT .a			$(GREEN)CLEANED$(DEF_COLOR)"

re:			fclean
			@$(MAKE)
			@echo "$(GREEN)			✔FDF CLEANED, REBUILT & READY TO USE\n$(DEF_COLOR)"

norminette:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true
			@norminette $(INC_DIR) | grep -v Norme -B1 || true

PHONY: all makelibs bonus clean fclean re norminette
