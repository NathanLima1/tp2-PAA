CC = gcc
CFLAGS = -Wall -O2 -I./src
OBJDIR = obj
LIBDIR = lib

folders = obj
OBJS = $(OBJDIR)/graph.o $(OBJDIR)/bf.o
SRCS = main.c

TARGET = tp2

all: $(TARGET)

$(TARGET): $(folders) $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(OBJS)

$(folders):
	mkdir -p $(folders)

$(OBJDIR)/graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c -o $@

$(OBJDIR)/bf.o: bf.c bf.h
	$(CC) $(CFLAGS) -c bf.c -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
	rm -r $(folders)
