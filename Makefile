NAME = pipex

NAMEB = pipex_bonus

SRCS = ft_split.c  ft_strjoin.c pipex.c splitpath.c path.c main.c\
		pipex_utils.c get_next_line_utils.c get_next_line.c

SRCB = ft_split_bonus.c  ft_strjoin_bonus.c pipex_bonus.c \
		main_bonus.c splitpath_bonus.c path_bonus.c \
		pipex_utils_bonus.c get_next_line_utils_bonus.c get_next_line_bonus.c 

CC = cc
CFLAGS = -Wall -Wextra -Werror 

OBJS = $(SRCS:.c=.o)
OBJB = $(SRCB:.c=.o)

all : $(NAME)

bonus : $(NAMEB)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -g

$(NAMEB): $(OBJB)
	$(CC) $(CFLAGS) $(OBJB) -o $@ -g

%.o : %.c
	$(CC) $(CFLAGS) $< -c -g
clean:
	@rm -f $(OBJS) $(OBJB) 
fclean: clean
	@rm -f $(NAME) $(NAMEB)
re: fclean all

