CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
NAME		=	ft_ls
DIR_LFT		=	libft/
LFT			=	$(DIR_LFT)libft.a
DIR_INC		=	includes/
DIR_SRC		=	src/
FILES_INC	=	ft_ls.h
FILES		=	alternate.c				\
				directory.c				dump.c				\
				error_constructor.c		error_handler.c		\
				file.c					filenameList.c		\
				fileTree.c				insert.c			\
				insertByAccessTime.c	insertByModTime.c	\
				insertByName.c			insertWithoutOrder.c\
				lstat.c				\
				main.c					parseFlags.c		\
				reader.c				
OBJECTS		=	$(addprefix $(DIR_SRC),$(FILES:.c=.o))
SRC			=	$(addprefix $(DIR_SRC),$(FILES))
INCLUDES	= 	-I $(DIR_INC) -I $(DIR_LFT)$(DIR_INC)
HEADER		=	$(addprefix $(DIR_INC), $(FILES_INC))

.PHONY: all clean fclean re

all:		$(NAME)
			@cp $(NAME) test/test/
			@cp $(NAME) test/try/
			@cp $(NAME) test/rus/

$(NAME):	$(OBJECTS) $(SRC) $(DIR_INC)ft_ls.h
			@make -C $(DIR_LFT)
			$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LFT) $(INCLUDES) 

%.o:%.c $(HEADER)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
			@make -C $(DIR_LFT) clean
			@echo clean
			rm -rf $(OBJECTS)

fclean:	clean
			@echo fclean
			rm -rf $(NAME)

re:		fclean all
