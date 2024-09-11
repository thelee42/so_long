CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3

SRC_DIR = source
OBJ_DIR = objet
MLX_DIR = libmlx
LIBFT_DIR = libft

MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    MLXFLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
    MLXFLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
endif

LIBFTFLAGS = -L$(LIBFT_DIR) -lft
INCLUDES = -I$(SRC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SOURCE = $(wildcard $(SRC_DIR)/*.c)
OBJET = $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCE:.c=.o)))

NAME = so_long

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ_DIR) $(OBJET) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJET) $(MLXFLAGS) $(LIBFTFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

lclean: fclean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)


re: fclean all

.PHONY: all clean fclean re lclean
