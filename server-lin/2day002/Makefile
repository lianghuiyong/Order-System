# Makefile
#

#CROSS_COMPILE = arm-linux-gnu-

CC = $(CROSS_COMPILE)gcc

ifdef CROSS_COMPILE
TARGET = /opt/filesystem
endif

DEBUG = -g -O0 -Wall

CFLAGS += $(DEBUG)

PROGS = ${patsubst %.c, %, ${wildcard *.c}} 

all : $(PROGS)

install: $(PROGS)
ifdef CROSS_COMPILE
	mkdir $(TARGET)/root/long_term/list -p
	cp $(PROGS) $(TARGET)/root/long_term/list -f
endif
% : %.c
	$(CC)  $(CFLAGS)  $< -o $@

.PHONY: uninstall clean dist

uninstall :
ifdef CROSS_COMPILE
	cd $(TARGET)/root/long_term/list && rm -f $(PROGS)
endif

clean : uninstall
	- rm -f $(PROGS) core *.gz

dist: clean
	tar czf ../farsight_list_demo1.0.tar.gz *.c ../list_example
	
