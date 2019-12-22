CC = gcc
NAME = varint_test

FLAGS = -Wall -Wextra
#FLAGS = -Wall -Wextra -ggdb -fsanitize=address

SRC = src/main.c\
		src/op.c\
		src/u64.c\
		src/find_prime.c\
	
OBJ = $(SRC:.c=.o)

INCL = -I include -I libft/include
LIB =  -lm -L libft -lft
#INCL = -I libft/include -I include
#LIB =  -L ./libft -lft -lm

all : $(NAME)

$(NAME) : ./libft/libft.a $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(INCL) $(LIB)
#$(NAME) : $(OBJ)
#		$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(INCL) $(LIB)

./libft/libft.a :
	make -C libft

%.o : %.c
	$(CC) -o $@ -c $< $(FLAGS) $(INCL)

clean : 
	rm -f $(OBJ)
	make -C libft fclean

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
