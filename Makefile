NAME = pathfinder
FILES = utils

SRC = $(addprefix src/,$(addsuffix .cpp, $(FILES)))

HEADER_PATH = include
FLAGS = -Wall -Wextra -Werror -std=c++17
CC = g++

all: $(NAME)

$(NAME):
	$(CC) -o $(NAME) $(FLAGS) $(SRC) main.cpp -I$(HEADER_PATH) 

clean:
	/bin/rm -f $(NAME)

fclean:
	/bin/rm -f $(NAME)

re: fclean all
