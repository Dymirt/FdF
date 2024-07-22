# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -g -fdiagnostics-color=always
CFLAGS_light = -Wall -Wextra -g -fdiagnostics-color=always

# Executable name
NAME = fdf

# Source files
SRC = main.c \
	ft_realloc.c \
	src/read_map_file.c \
	helpers_3d.c \
	ft_atoi_base.c \
	src/colors.c \
	src/isometric.c \
	src/img.c \
	src/navigation.c \
	src/t_dot/for_each_t_dot_mod_func.c\
	src/t_dot/for_each_t_dot.c\
	src/t_dot/t_dot.c \
	src/keys.c \
	src/cleaning.c \


# Rule for compiling libft
LIBFT_DIR = Libft/

# Object files
OBJDIR = obj/
OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR),$(OBJ))

# Rule for compiling libft
MINILIBX_DIR = minilibx-mac-osx/


# Main rule for compiling the project
$(NAME): $(OBJ)

	@make -C $(LIBFT_DIR)
	@make -C $(MINILIBX_DIR)
#	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit

# Rule for compiling individual source files
$(OBJDIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
# Rule for cleaning object files
clean:
	rm -f $(OBJ)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MINILIBX_DIR)


# Rule for fully cleaning the project (removing executable and object files)
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

# Default rule
re: fclean all

# Default rule
all: unzip $(NAME)

bonus : all

unzip:
	tar -xzf minilibx-linux.tgz

# Phony targets to avoid conflicts with file names
.PHONY: all clean fclean re

