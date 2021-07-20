CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
NAME		=	ft_ls
DIR_LFT		=	libft/
LFT			=	$(DIR_LFT)libft.a
DIR_INC		=	includes/
DIR_SRC		=	src/
FILES_INC	=	ft_ls.h
FILES		=	alternate.c					directory.c			\
				directoryHandlers.c			\
				display.c					display2.c			\
				displayDirHeader.c	\
				displayFile.c				\
				displayFileMode.c			\
				dump.c						\
				error_constructor.c			error_handler.c		\
				file.c						filenameList.c		\
				fileTree.c					\
				flagsHandle.c				flagsParse1.c		\
				flagsParse2.c				flagsSetSort.c		\
				flagsSetters1.c				flagsSetters2.c		\
				flagsSetters3.c				flagsGetters.c		\
				insert.c					\
				insertByAccessTime.c		insertByModTime.c	\
				insertByName.c				insertHandlers.c	\
				insertWithoutOrder.c		\
				lstat.c						\
				main.c						majorMinor.c		\
				meta.c						\
				reader.c
OBJECTS		=	$(addprefix $(DIR_SRC),$(FILES:.c=.o))
SRC			=	$(addprefix $(DIR_SRC),$(FILES))
INCLUDES	= 	-I $(DIR_INC) -I $(DIR_LFT)$(DIR_INC)
HEADER		=	$(addprefix $(DIR_INC), $(FILES_INC))

.PHONY: all clean fclean re

all:		$(NAME)
			@cp $(NAME) test/

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
