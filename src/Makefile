folders = obj
OBJS = $(folders)/graph.o $(folders)/solve.o $(folders)/heuristica.o
SRCS = main.c

TARGET = tp2

all: $(TARGET)

$(TARGET): $(folders) $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(OBJS)

$(folders):
	mkdir -p $(folders)

$(folders)/graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c -o $@

$(folders)/solve.o: solve.c solve.h graph.h
	$(CC) $(CFLAGS) -c solve.c -o $@

$(folders)/heuristica.o: heuristica.c heuristica.h solve.h graph.h
	$(CC) $(CFLAGS) -c heuristica.c -o $@

clean:
	rm -f $(folders)/*.o $(TARGET)
	rm -r $(folders)
