CFLAGS=-Wall -g

CC=gcc

PROGRAMM=ex26_yr

SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: $(PROGRAMM)

$(PROGRAMM): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAMM)

clean:
	rm -f $(PROGRAMM) *.o

test:
	@echo "=======================Test 1 without any arguments \
	=========================="
	./$(PROGRAMM) || true
	@echo "=======================Test 2 (search with AND) \
	========================"
	./$(PROGRAMM) time sit Hel
	@echo "=======================Test 3 (2-nd search with AND) \
	========================"
	./$(PROGRAMM) sit Hel
	@echo "=======================Test 4 (search with OR) \
	========================"
	./$(PROGRAMM) time sit Hel -o bad
	@echo "=======================Test 5 (2-nd search with AND) \
	========================"
	./$(PROGRAMM) time -o sit Hel bad
	@echo "=======================Test 6 (3-rd search with AND) \
	========================"
	./$(PROGRAMM) -o time sit Hel bad

