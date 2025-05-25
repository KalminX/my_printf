# Makefile

CC = gcc
CFLAGS = -Wall -Wextra
SRC = main.c custom_print.c
OBJ = $(SRC:.c=.o)
TARGET = custom_print_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all

test: custom_print.o test.o
	$(CC) $(CFLAGS) -o test_runner custom_print.o test.o

run_test: test
	./test_runner

