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

build: configure ${OUT}
	strip -s ${OUT}

install: clean build
	cp ${OUT} /usr/bin/imd

	mkdir -p /etc/imd/
	cp ./doc/* /etc/imd/

uninstall:
	rm /usr/bin/imd
	rm -r /etc/imd


# Files
${OUT}: ./obj/split.o ./obj/main.o ./obj/settings.o ./obj/reader.o ./obj/styling.o
	${CC} -o ${OUT} ./obj/*.o

./obj/main.o: ./src/main.c ./src/lessPrint.c ./src/rawPrint.c
	${CC} -c -o ./obj/main.o ./src/main.c

./obj/settings.o: ./src/settings.c
	${CC} -c -o ./obj/settings.o ./src/settings.c

./obj/reader.o: ./src/reader.c
	${CC} -c -o ./obj/reader.o ./src/reader.c

./obj/styling.o: ./src/styling.c
	${CC} -c -o ./obj/styling.o ./src/styling.c

./obj/split.o: ./src/split.c
	${CC} -c -o ./obj/split.o ./src/split.c
