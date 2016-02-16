CC = gcc
CFLAGS = -Wall -g -O0
SRC = ${wildcard *.c}
OBJS = ${patsubst %.c,%,$(SRC)}

all:$(OBJS)

%:%.c 
	    $(CC) $(CFLAGS) -o server server.c init.c sqlite3.c thread.c table.c -lpthread -ljson -lsqlite3

clean:
	    $(RM) $(OBJS) .*.sw?
