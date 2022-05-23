CC  = gcc -Wall -Wextra -I./inc -O2
OUT = ./bin/imd

all: ${OUT}
	${OUT} ./test.md

configure:
	# Make binaries directories
	mkdir -p obj/ bin/

clean:
	# Remove binaries
	rm -f ./bin/* ./obj/* *.stack-dump
	# Remove Compressed
	rm -f *.gz

# build
#
# install
#
# uninstall


# Files

${OUT}: ./obj/main.o
	${CC} -o ${OUT} ./obj/*.o

./obj/main.o: ./src/main.c
	${CC} -c -o ./obj/main.o ./src/main.c
