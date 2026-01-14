NAME = fraction
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = Fraction.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
