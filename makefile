CFLAGS =
CC     = cc -Wall -Wextra -I./inc -O2 -std=gnu18 ${CFLAGS}
OUT    = ./bin/imd
VER    = 2.6

all: configure ${OUT}
	${OUT} ./test.md

test: configure ${OUT}
	${OUT} .

configure:
	# Make binaries directories
	mkdir -p obj/ bin/

	# gen conf.h
	python3 ./conf.py

	# gen vinfo.h
	./genversion ${VER}

clean:
	# Remove binaries
	rm -f ./bin/* ./obj/* *.stack-dump
	# Remove Compressed
	rm -f *.gz

	# Remove unneeded Files
	rm ./inc/conf.h ./inc/vinfo.h -f

build: configure ${OUT}
	strip -s ${OUT}

	gzip imd.1 -k

uninstall:
	rm /usr/bin/imd
	rm /usr/bin/imd-rebuild
	rm -r /etc/imd

	rm /usr/share/man/man1/imd.1.gz

# Files
${OUT}: ./obj/useful.o ./obj/menu.o ./obj/split.o ./obj/main.o ./obj/settings.o ./obj/reader.o ./obj/styling.o
	${CC} -o ${OUT} ./obj/*.o

./obj/main.o: ./src/main.c ./src/lessPrint.c ./src/rawPrint.c
	${CC} -c -o ./obj/main.o ./src/main.c

./obj/settings.o: ./src/settings.c
	${CC} -c -o ./obj/settings.o ./src/settings.c

./obj/reader.o: ./src/reader.c
	${CC} -c -o ./obj/reader.o ./src/reader.c

./obj/styling.o: ./src/styling.c ./src/syntax.c
	${CC} -c -o ./obj/styling.o ./src/styling.c

./obj/split.o: ./src/split.c
	${CC} -c -o ./obj/split.o ./src/split.c

./obj/menu.o: ./src/menu.c
	${CC} -c -o ./obj/menu.o ./src/menu.c

./obj/useful.o: ./src/useful.c
	${CC} -c -o ./obj/useful.o ./src/useful.c
