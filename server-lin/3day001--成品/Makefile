CC = gcc
SRC = ${wildcard *.c}
OBJS = ${patsubst %.c,%,$(SRC)}

all:$(OBJS)

%:%.c 
	    $(CC) -o $@ $^ init.c sqlite3.c thread.c work.c table.c -lpthread -ljson -lsqlite3

clean:
	    $(RM) $(OBJS) .*.sw?
