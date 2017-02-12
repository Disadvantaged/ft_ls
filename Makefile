NAME = ft_ls

FLAGS = -Wall -Werror -Wextra -Ilibft/includes -Iincludes/

SRCS = src/main.c \
	   src/checker.c \
	   src/path_to_dir.c \
	   src/file_data.c \
	   src/sort.c \
	   src/algo.c \
	   src/free.c \
	   src/print.c
LIBFT_PATH = libft/

OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))

RM = rm -f

all: $(NAME)

$(OBJS): | obj

obj:
	@mkdir -p $@

obj/%.o: src/%.c
	$(CC) $(FLAGS) -c -o $@ $<

$(LIBFT_PATH)/libft.a:
	make -C $(LIBFT_PATH)

$(NAME): $(LIBFT_PATH)/libft.a $(OBJS)
	$(CC) $(OBJS) $(LIBFT_PATH)/libft.a -o $(NAME)
clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_PATH) clean
fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean
re: fclean all
