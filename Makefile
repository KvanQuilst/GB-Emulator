# Makefile for gbemu

SDIR		:= src
IDIR		:= include
ODIR		:= obs
CFILES	:= $(wildcard $(SDIR)/*.c)
OBJS		:= $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(CFILES))
CC			:= gcc
CFLAGS	:= -g -Wall -iquote $(IDIR)
LFLAGS	:= `sdl2-config --cflags --libs`

gbemu: $(ODIR) $(OBJS)
	$(CC) $(ODIR)/*.o -o $@ $(LFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $< 

$(ODIR):
	@mkdir $@

.PHONY clean:
clean:
	@rm -rf $(ODIR) gbemu
