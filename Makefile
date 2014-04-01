# lotto luv makefile

PROGRAM = payout_engine

CC ?= gcc 
LD ?= ld
CFLAGS ?= -Wall -Werror
LDFLAGS ?= 

FILES += payout_engine.c

OBJS = payout_engine.o 

all: $(OBJS)
	$(LD) -r $(OBJS) $(LDFLAGS) -o $(PROGRAM).ro
	$(CC) $(PROGRAM).ro -o $(PROGRAM)
	@echo "done"

%.o: %.c
	$(CC) -c $(patsubst %.o, %.c, $(OBJS))
clean:
	rm -f $(OBJS)

distclean: clean

