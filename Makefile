NAME	=	So_Long

SRCS	= 	get_next_line.c \
			get_next_line_utils.c \
			ft_split.c \
			main.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -I /usr/local/include $(CFLAGS) $(OBJS) -o $(NAME) -L /usr/local/lib -lmlx
