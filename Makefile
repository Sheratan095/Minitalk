NAME		= minitalk

COREKIT_PATH = ./Corekit

INCLUDES = -I$(COREKIT_PATH)/includes

FLAGS = -Wall -Werror -Wextra

SRC		= src/server.c src/client.c src/utils.c

OBJS	= $(SRC:%.c=%.o)

$(NAME): $(SRC)
	@$(MAKE) -sC $(COREKIT_PATH)
	@cc $(FLAGS) $(INCLUDES) src/server.c src/utils.c -L$(COREKIT_PATH) -lcorekit -o server
	@echo "$(GREEN)[MINITALK]:\t SERVER COMPILED$(RESET)";
	@cc $(FLAGS) $(INCLUDES) src/client.c src/utils.c -L$(COREKIT_PATH) -lcorekit  -o client
	@echo "$(GREEN)[MINITALK]:\t CLIENT COMPILED$(RESET)";

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# bonus:
# 	${MAKE} -C libft bonus
# 	cc $(FLAGS) server_bonus.c -Llibft -lft -o server_bonus
# 	cc $(FLAGS) client_bonus.c -Llibft -lft -o client_bonus

all:$(NAME)

clean:
	@rm -fr *.o
	@rm -fr **/*.o
	@${MAKE} -C $(COREKIT_PATH) clean -s
	@echo "$(RED)[COREKIT]:\t COREKIT CLEAN$(RESET)"

fclean: clean
	@rm -f *.a
	@rm -f *.out
	@rm -f *.gch
	@rm -f $(NAME)
	@${MAKE} -C $(COREKIT_PATH) fclean -s
	@echo "$(RED)[COREKIT]:\t COREKIT FCLEAN$(RESET)"

re: fclean all

test: re
	 ./server

val: re
	valgrind --leak-check=full --show-leak-kinds=all ./server_bonus

#COLORS

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m