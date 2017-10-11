NAME = fdf

SRC = srcs/main.c srcs/lib.c srcs/pars.c srcs/event.c srcs/clear.c srcs/gnl.c srcs/bmp.c

FLAGS = -Wall -Wextra -Werror

SRC2 = main.o lib.o pars.o event.o clear.o gnl.o bmp.o

all: $(NAME)

%.o : %.c
	gcc -c -o $@ $^

$(NAME): $(SRC)
	@echo "mpinson" > auteur
	@make -C ./libft all
	@make -C ./minilibx_macos all
	@cp ./minilibx_macos/libmlx.a ./lib
	@cp ./libft/libft.a ./lib
	gcc  $(FLAGS) -I ./include/  -L./lib  -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(SRC)
	@afplay musique/enclume.mp3 &


clean:
	/bin/rm -f $(SRC2)
	@make -C ./libft clean
	@make -C ./minilibx_macos clean
	@afplay musique/destruction.mp3 &

fclean: clean
	/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all
