NAME = pipex
CC = cc 
HEAD = .
CFLAGS = -g3 -Wall -Werror -Wextra
SOURCES = main.c ini.c execution.c
		        
OBJECTS = $(SOURCES:.c=.o)

MAKE_LIBFT        =    make -s -C ./lib
LIBFT_A			=		./lib/libft.a

all: ${NAME}

$(NAME): $(OBJECTS)
	$(MAKE_LIBFT)
	${CC} ${CFLAGS} ${OBJECTS} ${LIBFT_A} -o ${NAME}
	
$(OBJECTS): $(SOURCES) 


.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@ -I $(HEAD)

clean	:
	rm -rf $(OBJECTS)

fclean :	clean
	rm -rf $(NAME)

re :	fclean all

.PHONY:	all	clean	fclean	re