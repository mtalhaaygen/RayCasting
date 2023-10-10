SRCS			=	ft_strlen.c \
			ft_strcmp.c \
			ft_strchr.c \
		
# BONUS			=	ft_lstnew.c \
# 		ft_lstadd_front.c \
# 		ft_lstsize.c \
# 		ft_lstlast.c \
# 		ft_lstadd_back.c \
# 		ft_lstdelone.c \
# 		ft_lstclear.c \
# 		ft_lstiter.c \
# 		ft_lstmap.c
OBJS			= $(SRCS:.c=.o)
# BONUS_OBJS		= $(BONUS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

# bonus: $(OBJS) $(BONUS_OBJS)
# 	ar r $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	rm -f *.o

fclean: clean
	rm -f *.a

re: fclean all

.PHONY: all clean fclean re
