NAME = philo

SRCS = main validate init utils checker simulation routine eat_handler

SRC = $(addsuffix .c, $(addprefix src/, $(SRCS)))

OBJS = $(addsuffix .o, $(addprefix objs/, $(SRCS)))

all: $(NAME)

$(NAME): $(OBJS)
	gcc  -g -Wall -Wextra -Werror $(OBJS) -o $(NAME)

objs/%.o:	src/%.c
	@mkdir -p $(dir $@)
	@gcc -g -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -rf ./objs

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re