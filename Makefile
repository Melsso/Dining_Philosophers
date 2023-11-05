NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror
OBJ_DIR = obj/
SRC_DIR = src/

SRC		:=  utils.c \
			main.c \
			threads.c \
			thread_utils.c \
			parsing.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
HEADER = -I ./include


all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< -o $@ $(HEADER) $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	clear

clean:
	rm -rf $(OBJ_DIR)
	clear

fclean: clean
	rm -f $(NAME)
	clear

re: fclean all

.PHONY: all clean fclean re
