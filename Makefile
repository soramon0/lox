CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
NAME = shell
SRC = main.c $(shell find ./src -depth -maxdepth 1 -type f -name "*.c")
LIBS = -lreadline
OBJ = $(SRC:.c=.o)
LIBFT_NAME = src/libft/libft.a

all: $(NAME)

libft: $(LIBFT_NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME) $(LIBS)

$(LIBFT_NAME):
	$(MAKE) -C ./src/libft

run: re
	./$(NAME)


clean:
	$(MAKE) -C src/libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C src/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
