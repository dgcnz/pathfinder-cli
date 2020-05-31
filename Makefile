NAME = pathfinder
FILES = utils depth_first_search breadth_first_search best_first_search a_star_search hill_climbing

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
