# Compilador
CC = gcc

# Compilador Flags
CFLAGS = -Wall -fstack-protector-all -g -std=c99

# Nome do Programa
PROGRAM = ted

# Arquivos .c
sources := $(wildcard *.c)

# Arquivos .h
headers := $(wildcard *.h)

# Arquivos .o
objects := $(wildcard *.o)
# Dependencies
main.o: geo.h system.h paths.h qry.h svg.h yxxtree.h libraries.h argv.h
paths.o: paths.h
geo.o: rectangle.h line.h txt.h info.h geo.h paths.h yxxtree.h circle.h
rectangle.o:rectangle.h
circle.o : circle.h
line.o : line.h
svg.o: svg.h line.h circle.h rectangle.h yxxtree.h
list.o: list.h 
yxxtree.o: line.h txt.h yxxtree.h circle.h rectangle.h info.h queue.h
argv.o: argv.h
qry.o: qry.h yxxtree.h paths.h
queue.o:yxxtree.h info.h libraries.h queueCoord.h
info.o: info.h
inp.o: info.h queue.h libraries.h yxxtree.h
queueCoord.o: queueCoord.h
txt.o: "libraries.h"

$(PROGRAM): $(sources) $(headers)
	$(CC) $(CFLAGS) $(sources) $(headers) -o $(PROGRAM)
	
clean:
	rm $(objects) $(PROGRAM)

run:
	valgrind ./$ ted -e /home/util/Desktop/jgcjr_3/t1 -f /vasos-flores.geo -q /vasos-flores/002-dps.qry -o /home/util/Desktop/jgcjr_3/t1