CFLAGS =
CC     = cc -Wall -Wextra -O2 -std=gnu18 ${CFLAGS}
OUT    = /usr/bin/imd
SRC    = /etc/imd/src

build:
	${CC} -o ${OUT} \
	${SRC}/main.c \
	${SRC}/reader.c \
	${SRC}/settings.c \
	${SRC}/split.c \
	${SRC}/styling.c \
	${SRC}/useful.c \
	${SRC}/menu.c

	strip -s ${OUT}
