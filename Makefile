NAME = minishell
NAME_CH = checker
DIR_OBJ = obj
LIST = main1.c ft_split_bonus.c ft_splitpath_bonus.c ft_is_sep_or_spec_sign.c ft_set_redir.c \
               ft_pipe_helper.c ft_cmd_bonus.c ft_cmd_bonus_utils.c ft_heredoc.c ft_pipex2.c\
               ft_heredoc_helper.c ft_split_helper_bonus.c parser.c ft_pipex.c ft_free.c ft_env.c  ft_env2.c\
               ft_signals.c ft_dup.c ft_env_utils.c ft_free_del_env.c ft_insert_var.c \
               ft_insert_var1.c ft_insert_var_helper.c ft_utils.c parser_utils.c\
               ft_split_bonus_utils.c ft_split_bonus_strs.c ft_buildin.c ft_buildin2.c ft_buildin3.c\
               ft_validate_spec_funcs.c ft_validate_spec_order.c

OBJ = $(addprefix $(DIR_OBJ)/, $(LIST:.c=.o))

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : ./libft/libft.a $(OBJ)
	gcc -g $(OBJ) -lreadline \
	-L${HOME}/.brew/Cellar/readline/8.1.2/lib/ \
    -I${HOME}/.brew/Cellar/readline/8.1.2/include/ \
    $(FLAGS) -L./libft -lft -o $(NAME)

./libft/libft.a :
	$(MAKE) bonus -C ./libft

//.SILENT:
$(DIR_OBJ)/%.o : %.c ./minishell.h
	mkdir -p $(DIR_OBJ)
	gcc  -g -c $(FLAGS) $< -o  $@ \

clean :
	$(MAKE) clean -C ./libft
	rm -rf $(DIR_OBJ)

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)


re : fclean all

.PHONY : all clean fclean re libft
