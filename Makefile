SRCS = check.c check2.c main.c map.c move.c move2.c reader.c reader2.c texture.c utils.c utils2.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX = mlx/libmlx.a
LIB = libft/libft.a
NAME = cub3d
all: $(NAME)

$(NAME): $(MLX) $(LIB) *.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(MLX) $(LIB) -o $(NAME) *.o -g

*.o: *.c gnl/*.c
	$(CC) $(CFLAGS) -c $(SRCS) gnl/*.c

$(LIB):
	@make all -C libft/

$(MLX):
	@make all -C mlx/

clean:
	rm -rf *.o
	@make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	@make clean -C mlx/
	@make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re