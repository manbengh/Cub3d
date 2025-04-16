SRC =	srcs/main.c \
		srcs/utils.c \
		srcs/utils2.c \
		srcs/map_check.c  \
		srcs/map_check2.c  \
		srcs/map_check3.c  \
		srcs/init_map.c  \
		srcs/ft_free.c  \
		srcs/my_game.c  \
		srcs/raycasting.c  \
		srcs/calculate.c  \
		srcs/moving.c  \
		srcs/init_game.c  \
		srcs/rotation.c  \
		srcs/texture.c  \
		srcs/raycasting_two.c\

OBJ = $(SRC:.c=.o)

CC = cc

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g3

INC = -Iincludes -I/usr/include -Iminilibx-linux -ILibft

MLX_LIB =  minilibx-linux/libmlx_Linux.a
MLX_FLAGS = -Lmlx -L/usr/lib/X11 -lXext -lX11 -lm

LIBFT = Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(INC) -o $(NAME) $(MLX_LIB) $(LIBFT)

$(MLX_LIB):
	make -C minilibx-linux

$(LIBFT):
	make -C Libft

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

clean:
	rm -f ${OBJ}
	make -C minilibx-linux clean
	make -C Libft clean

fclean: clean
	rm -f ${NAME}
	make fclean -C Libft

re: fclean all

.PHONY: all clean fclean re
