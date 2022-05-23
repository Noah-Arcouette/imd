CC   = gcc -Wall -Wextra -I./inc -O2
OUT  = ./bin/imd

all: configure ${OUT}
	${OUT} ./test.md

configure:
	# Make binaries directories
	mkdir -p obj/ bin/

	# Run conf.py
	python3 ./conf.py

clean:
	# Remove binaries
	rm -f ./bin/* ./obj/* *.stack-dump
	# Remove Compressed
	rm -f *.gz

	# Remove unneeded Files
	rm ./inc/conf.h -f

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


# User should never run
test: ./conf.py
	./conf.py
