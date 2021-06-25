CC = gcc
CFLAGS = -Wall
SRC = chiffrement.c dechiffrement.c main.c 
OBJ = $(SRC:.c=.o)
EXEC =  main chiffrement dechiffrement

all: ${EXEC}

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o ${EXEC}

clean:
	@rm -rf *.o main