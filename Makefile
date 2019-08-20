CC = gcc
RM = rm -rf

CFLAGS =  \
		 -I$(INCDIR)\

LDLIBS =-lmlx\
		-framework OpenGL\
		-framework AppKit
LDFLAGS	=

INCDIR = ./
SRCSDIR = 
SRCS = main.c draw.c init.c graphics.c key_event.c julia.c tricorne.c mandelbrot.c\
multimandelbrot2.c ship.c complex.c mouse_event.c set_color.c set_palette.c
OBJS = $(SRCS:.c=.o)
TARGET = fractol

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo 'making executable'
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)
	@echo DONE!

$(OBJS): %.o: $(SRCSDIR)%.c $(INCDIR)/frctl.h
	$(CC) -c $< $(CFLAGS) 

$(INCDIR)/frctl.h:

.PHONY: clean
clean:
	@echo deliting object files
	@$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	@echo deliting executable file
	@$(RM) $(TARGET)

.PHONY: re
re:	fclean all
