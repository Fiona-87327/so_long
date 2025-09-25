NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX42_DIR = MLX42
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a
MLX42_FLAGS = -ldl -lglfw -pthread -lm

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

INCLUDES = -I./include -I$(MLX42_DIR)/include -I$(LIBFT_DIR)

SRCS_DIR = src
SRCS = $(SRCS_DIR)/so_long.c \
	   $(SRCS_DIR)/ft_render_game.c \
	   $(SRCS_DIR)/ft_map.c \
	   $(SRCS_DIR)/ft_key_hand.c \
	   $(SRCS_DIR)/ft_game_init.c \
	   $(SRCS_DIR)/ft_free_and_clean.c \
	   $(SRCS_DIR)/ft_check_path.c \
	   $(SRCS_DIR)/ft_check_map.c \

all: deps $(NAME)

deps:
	@which cmake > /dev/null || (echo "Installing cmake..." && sudo apt-get update && sudo apt-get install -y cmake)
	@which pkg-config > /dev/null || (echo "Installing pkg-config..." && sudo apt-get install -y pkg-config)
	@pkg-config --exists glfw3 || (echo "Installing GLFW3..." && sudo apt-get install -y libglfw3-dev)

$(MLX42_LIB): deps
	@echo "Building MLX42..."
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build -j4

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(MLX42_LIB) $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX42_LIB) $(LIBFT_LIB) $(MLX42_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX42_DIR)/build

re: fclean all

.PHONY: all clean fclean re