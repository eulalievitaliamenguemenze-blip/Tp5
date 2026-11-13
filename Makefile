CC=gcc
CFLAGS=-std=c17 -Wall -Wextra -g
all: test_tp5
test_tp5: tris.c test_tp5.c
$(CC) $(CFLAGS) tris.c test_tp5.c -o test_tp5
clean:
rm -f test_tp5 mesures.csv
valgrind: test_tp5
valgrind --leak-check=full --show-leak-kinds=all ./test_tp5
