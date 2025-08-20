CC = cc
CFLAGS = -Wall -Wextra -Werror

all: 
	make -C ./lib/libft/
	make -C ./lib/ft_printf/
	$(CC) $(CFLAGS) ./source/server.c -o server -L./lib/ft_printf -lftprintf -L./lib/libft -lft
	$(CC) $(CFLAGS) ./source/client.c -o client -L./lib/ft_printf -lftprintf -L./lib/libft -lft

bonus:
	make -C ./lib/libft/
	make -C ./lib/ft_printf/
	$(CC) $(CFLAGS) ./source/server_bonus.c -o server -L./lib/ft_printf -lftprintf -L./lib/libft -lft
	$(CC) $(CFLAGS) ./source/client_bonus.c -o client -L./lib/ft_printf -lftprintf -L./lib/libft -lft
clean:
	make clean -C ./lib/ft_printf
	make clean -C ./lib/libft

fclean: clean
	make fclean -C ./lib/ft_printf
	make fclean -C ./lib/ft_printf
	rm -f server client

re: fclean all
