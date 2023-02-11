NAME	=	So_Long
PRINTF	=	ft_printf/libftprintf.a

SRCS	= 	get_next_line.c \
			get_next_line_utils.c \
			ft_split.c \
			helper_functions1.c \
			helper_functions2.c \
			helper_functions3.c \
			helper_functions4.c \
			mlx_work.c \
			main.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) -C ft_printf
			$(CC) $(CFLAGS) -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit $(OBJS) $(PRINTF) -o $(NAME)

clean:
			$(MAKE) clean -C ft_printf
			rm -f $(OBJS)

fclean:		clean
			$(MAKE) fclean -C ft_printf
			rm -f $(NAME)

re:			fclean all


