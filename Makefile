NAME_CLIENT = client1

NAME_SERVER = client2

SRCS1 = $(wildcard ./src/client1/*.cpp)

SRCS2 = $(wildcard ./src/client2/*.cpp)

CC = g++

CFLAGS = -Wall -Wextra

$(NAME_CLIENT): $(SRCS)


