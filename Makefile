NAME = minichat

SRCS =	$(wildcard ./src/*.cpp) \
		$(wildcard ./classes/*.cpp) \
		./main.cpp \

CC = g++

LDFLAGS = -pthread  -lpthread

CFLAGS = -g -Wall -Wextra

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
