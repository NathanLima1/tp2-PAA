CC = gcc
CFLAGS = -Wall -O2 -I./src
OBJDIR = obj
LIBDIR = lib

folders = obj
OBJS = $(OBJDIR)/graph.o $(OBJDIR)/solve.o $(OBJDIR)/heuristica.o
SRCS = src/main.c

TARGET = tp2

all: $(TARGET)

$(TARGET): $(folders) $(OBJS) $(SRCS)
    $(CC) $(CFLAGS) -o $@ $(SRCS) $(OBJS)

$(folders):
    mkdir -p $(folders)

$(OBJDIR)/graph.o: src/graph.c src/graph.h
    $(CC) $(CFLAGS) -c src/graph.c -o $@

$(OBJDIR)/solve.o: src/solve.c src/solve.h src/graph.h
    $(CC) $(CFLAGS) -c src/solve.c -o $@

$(OBJDIR)/heuristica.o: src/heuristica.c src/heuristica.h src/solve.h src/graph.h
    $(CC) $(CFLAGS) -c src/heuristica.c -o $@

clean:
    rm -f $(OBJDIR)/*.o $(TARGET)
    rm -r $(folders)