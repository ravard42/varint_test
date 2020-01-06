CC = gcc
NAME = varint_test

FLAGS = -Wall -Wextra -Ofast
#FLAGS = -Wall -Wextra -ggdb -fsanitize=address

SRC = src/main.c\
		src/op.c\
		src/u64.c\
		src/find_prime.c\
		src/asn1_der.c\
	
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ../

INCL = -I ${LIBFT_DIR}/include -I include
LIB =  -lm -L ${LIBFT_DIR} -lft

all : $(NAME)

$(NAME) : ${LIBFT_DIR}/libft.a $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(INCL) $(LIB)

${LIBFT_DIR}/libft.a :
	make -C ${LIBFT_DIR}

%.o : %.c
	$(CC) -o $@ -c $< $(FLAGS) $(INCL)

clean : 
	rm -f $(OBJ)
	make -C ${LIBFT_DIR} fclean

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
