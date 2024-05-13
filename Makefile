NAME		= minitalk

COREKIT_PATH = ./Corekit

INCLUDES = -I$(COREKIT_PATH)/includes

#TO DO rimettere le flag
FLAGS = -Wall -Werror -Wextra

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

#------------------MANDATORY PART------------------#

SERVER = server
CLIENT = client

SERVER_SRC = src/server.c
SERVER_OBJS = $(SERVER_SRC:%.c=%.o)

CLIENT_SRC = src/client.c
CLIENT_OBJS = $(CLIENT_SRC:%.c=%.o)

$(NAME) : $(SERVER) $(CLIENT)

all : $(NAME)

$(SERVER): $(SERVER_OBJS)
	@$(MAKE) -sC $(COREKIT_PATH)
	@cc $(FLAGS) $(INCLUDES) $(SERVER_OBJS) -L$(COREKIT_PATH) -lcorekit -o $(SERVER)
	@echo "$(GREEN)[MINITALK]:\t SERVER COMPILED$(RESET)"

$(CLIENT): $(CLIENT_OBJS)
	@$(MAKE) -sC $(COREKIT_PATH)
	@cc $(FLAGS) $(INCLUDES) $(CLIENT_OBJS) -L$(COREKIT_PATH) -lcorekit -o $(CLIENT)
	@echo "$(GREEN)[MINITALK]:\t CLIENT COMPILED$(RESET)"

#--------------------BONUS PART--------------------#

SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

SERVER_SRC_BONUS = src_bonus/server_bonus.c
SERVER_OBJS_BONUS = $(SERVER_SRC_BONUS:%.c=%.o)

CLIENT_SRC_BONUS = src_bonus/client_bonus.c
CLIENT_OBJS_BONUS = $(CLIENT_SRC_BONUS:%.c=%.o)

bonus : $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(SERVER_OBJS_BONUS)
	@$(MAKE) -sC $(COREKIT_PATH)
	@cc $(FLAGS) $(INCLUDES) $(SERVER_OBJS_BONUS) -L$(COREKIT_PATH) -lcorekit -o $(SERVER_BONUS)
	@echo "$(GREEN)[MINITALK]:\t SERVER COMPILED$(RESET)"

$(CLIENT_BONUS): $(CLIENT_OBJS_BONUS)
	@$(MAKE) -sC $(COREKIT_PATH)
	@cc $(FLAGS) $(INCLUDES) $(CLIENT_OBJS_BONUS) -L$(COREKIT_PATH) -lcorekit -o $(CLIENT_BONUS)
	@echo "$(GREEN)[MINITALK]:\t CLIENT COMPILED$(RESET)"

clean:
	@rm -fr *.o
	@rm -fr **/*.o
	@${MAKE} -C $(COREKIT_PATH) clean -s
	@echo "$(RED)[COREKIT]:\t COREKIT CLEAN$(RESET)"

fclean: clean
	@rm -f *.a
	@rm -f *.out
	@rm -f *.gch
	@rm -fr client
	@rm -fr server
	@rm -fr client_bonus
	@rm -fr server_bonus
	@rm -f $(NAME)
	@${MAKE} -C $(COREKIT_PATH) fclean -s
	@echo "$(RED)[COREKIT]:\t COREKIT FCLEAN$(RESET)"

re: fclean all

test: $(NAME)
	 ./server

val: re
	valgrind --leak-check=full --show-leak-kinds=all ./server_bonus

#COLORS

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m