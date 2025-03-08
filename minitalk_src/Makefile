# Program names
SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

# Compiler flags and cleanup
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

# Source files
SRC1 = mandatory/server.c mandatory/client.c mandatory/helpers.c
SRC2 = bonus/server_bonus.c bonus/client_bonus.c bonus/helpers_bonus.c

# Object files
OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

# Mandatory Object Files
SERVER_OBJ = mandatory/server.o mandatory/helpers.o
CLIENT_OBJ = mandatory/client.o mandatory/helpers.o

# Bonus Object Files
SERVER_BONUS_OBJ = bonus/server_bonus.o bonus/helpers_bonus.o
CLIENT_BONUS_OBJ = bonus/client_bonus.o bonus/helpers_bonus.o

# All target (builds mandatory)
all: $(SERVER) $(CLIENT)

# Compile server
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER)

# Compile client
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT)

# Bonus target
bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

# Compile server bonus
$(SERVER_BONUS): $(SERVER_BONUS_OBJ)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) -o $(SERVER_BONUS)

# Compile client bonus
$(CLIENT_BONUS): $(CLIENT_BONUS_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) -o $(CLIENT_BONUS)

# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	$(RM) $(OBJ1) $(OBJ2)

# Clean up object files and executables
fclean: clean
	$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

# rebuild 
re: fclean all

.PHONY: all clean fclean re bonus
