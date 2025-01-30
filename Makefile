CC = g++
CFLAGS = -Wall -Wextra -O2
TARGET = postfix_eval
SRC = postfix_eval.cc
HEADERS = deque.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
