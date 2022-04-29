NAME = libft.a
LIST = ft_strcmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_split.c ft_memset.c ft_striteri.c ft_itoa.c ft_strmapi.c ft_bzero.c ft_substr.c ft_strtrim.c ft_strnstr.c ft_strchr.c ft_calloc.c ft_strdup.c ft_memmove.c ft_memchr.c ft_strrchr.c ft_strncmp.c ft_memcmp.c ft_memcpy.c ft_strjoin.c ft_atoi.c ft_strlen.c ft_strlcat.c ft_strlcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS = ft_lstmap.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c
OBJ = ${LIST:.c=.o}
OBJB = ${BONUS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $?

%.o : %.c ./libft.h
	gcc -Wall -Werror -Wextra -c $< -o $@

bonus : $(NAME)
	$(MAKE) OBJ="$(OBJB)"

clean :
	rm -f $(OBJ) $(OBJB)

so :
	gcc -Wall -Werror -Wextra -nostartfiles -c $(LIST) $(BONUS)
	gcc -nostartfiles -shared -o libft.so $(OBJ) $(OBJB)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
