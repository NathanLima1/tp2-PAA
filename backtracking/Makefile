folders = obj
OBJS = $(folders)/heuristica.o $(folders)/mochila.o $(folders)/solve.o
SRCS = main.c

TARGET = tp2

all: $(TARGET)

$(TARGET): $(folders) $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(OBJS)

$(folders):
	mkdir -p $(folders)

$(folders)/mochila.o: mochila.c mochila.h
	$(CC) $(CFLAGS) -c mochila.c -o $@

$(folders)/solve.o: solve.c solve.h mochila.h
	$(CC) $(CFLAGS) -c solve.c -o $@

$(folders)/heuristica.o: heuristica.c heuristica.h solve.h mochila.h
	$(CC) $(CFLAGS) -c heuristica.c -o $@

clean:
	rm -f $(folders)/*.o $(TARGET)
	rm -r $(folders)
