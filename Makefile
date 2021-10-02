NAME = fractol
LIBFT_NAME = libft.a
MINILIBX = libmlx.dylib
MAIN_NAME = ./src/fractol.c
HFILENAME = ./src/fractol.h

SRC_NAME = fractol.c color_functions.c mouse_press_button_control.c \
	keyboard_control.c init.c exit.c draw_fractal.c fractal_julia.c \
	fractal_mandelbrot.c fractal_buterfly.c fractal_burning_ship.c \
	fractal_mandelbar.c mouse_motion_control.c

CC = gcc

LIB_PATH = ./libft/
MLX_PATH = ./mlx/
SRC_PATH = ./src/
OBJ_PATH = ./obj/

MLX = -Lmlx -lmlx -framework OpenGL -framework Appkit
FLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_BONUS_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIBFT = $(addprefix $(LIB_PATH), $(LIBFT_NAME))

all:
	@$(MAKE) -C $(LIB_PATH)
	@$(MAKE) -C $(MLX_PATH)
	@$(MAKE) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c

	@mkdir -p $(OBJ_PATH)
	@printf  "\r%-25s\033[34m[$<]\033[0m\n" "$(NAME): $@"
	@$(CC) $(FLAGS) -Imlx -o $@ -c $<
	@printf "\033[A\033[2K"

$(NAME): $(OBJ) $(HFILENAME) $(LIBFT) Makefile

	@$(CC) $(FLAGS) $(LIBFT) $(MLX) $(OBJ) -o $(NAME)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

bonus: all

test: all

	@./$(NAME) Julia -0.8 0.156

leaks: all

	@valgrind ./$(NAME) --leak-check=full

clean:

	@$(MAKE) -C $(LIB_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean
	@rm -rf $(OBJ_PATH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"


fclean: clean

	@$(MAKE) -C $(LIB_PATH) fclean
	@rm -rf $(NAME)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

re: fclean all

.PHONY: clean fclean re bonus run
