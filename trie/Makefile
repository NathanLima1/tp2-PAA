folders = obj
CFLAGS = -O3 -Wall
OBJS = obj/trie.o obj/dp.o obj/solve.o obj/heuristica.o obj/graph.o
SRCS = main.c

TARGET = tp2

all: $(TARGET)

$(TARGET): $(folders) $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(OBJS)

obj/trie.o: src/trie.c include/trie.h
	$(CC) $(CFLAGS) -c src/trie.c -o $@

obj/dp.o: src/dp.c include/dp.h
	$(CC) $(CFLAGS) -c src/dp.c -o $@

obj/solve.o: src/solve.c include/solve.h include/dp.h include/trie.h include/graph.h
	$(CC) $(CFLAGS) -c src/solve.c -o $@

obj/heuristica.o: src/heuristica.c include/heuristica.h include/solve.h include/dp.h
	$(CC) $(CFLAGS) -c src/heuristica.c -o $@

obj/graph.o: src/graph.c include/graph.h
	$(CC) $(CFLAGS) -c src/graph.c -o $@

folders:
obj:
	mkdir -p obj

clean:
	rm -f obj/*.o $(TARGET)
	rm -r obj
