NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lm -lXext -lX11  # Linux，如果是 macOS，换成 -lmlx -framework OpenGL -framework AppKit

SRCS = so_long.c map.c game.c mlx_utils.c
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
LIBFT_INC = -Ilibft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re