folders = obj
OBJS = $(folders)/graph.o $(folders)/dp.o $(folders)/heuristica.o
SRCS = main.c

TARGET = tp2

all: $(TARGET)

$(TARGET): $(folders) $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(OBJS)

$(folders):
	mkdir -p $(folders)

$(folders)/graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c -o $@

$(folders)/dp.o: dp.c dp.h graph.h
	$(CC) $(CFLAGS) -c dp.c -o $@

$(folders)/heuristica.o: heuristica.c heuristica.h dp.h graph.h
	$(CC) $(CFLAGS) -c heuristica.c -o $@

clean:
	rm -f $(folders)/*.o $(TARGET)
	rm -r $(folders)
