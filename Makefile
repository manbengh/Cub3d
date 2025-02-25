SRC =	srcs/main.c \
		srcs/utils.c \
		srcs/utils2.c \
		srcs/map_check.c  \
		srcs/map_check2.c  \
		srcs/init_map.c  \
		srcs/ft_free.c  \

OBJ = $(SRC:.c=.o)

CC = cc

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g3

INC = -Iincludes -I/usr/include -ILibft

# MLX_LIB =  minilibx-linux/libmlx_Linux.a
# MLX_FLAGS = -Lmlx -L/usr/lib/X11 -lXext -lX11

LIBFT = Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(INC) -o $(NAME) $(LIBFT)


$(LIBFT):
	make -C Libft

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

clean:
	rm -f ${OBJ}
	make -C Libft clean

fclean: clean
	rm -f ${NAME}
	make -C Libft fclean

re: fclean all

.PHONY: all clean fclean re
