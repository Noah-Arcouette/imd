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

${OUT}: ./obj/main.o ./obj/settings.o ./obj/reader.o ./obj/styling.o
	${CC} -o ${OUT} ./obj/*.o

./obj/main.o: ./src/main.c
	${CC} -c -o ./obj/main.o ./src/main.c

./obj/settings.o: ./src/settings.c
	${CC} -c -o ./obj/settings.o ./src/settings.c

./obj/reader.o: ./src/reader.c
	${CC} -c -o ./obj/reader.o ./src/reader.c

./obj/styling.o: ./src/styling.c
	${CC} -c -o ./obj/styling.o ./src/styling.c
