CC = g++
CFLAGS = -Wall -Wextra -O2
TARGET = postfix_eval

all: $(TARGET)

$(TARGET): postfix_eval.cc
	$(CC) $(CFLAGS) -o $(TARGET) postfix_eval.cc

clean:
	rm -f $(TARGET)
