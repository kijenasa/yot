PROG = yot
SRC  = ${PROG}.c
OBJ  = ${SRC:.c=.o}

CC = cc
INCS =
LIBS = -lgit2

LDFLAGS = ${LIBS}
CFLAGS = -Wall -Wextra ${INCS}

INSTALL_DIR = /usr/local/bin

all: ${PROG}

${PROG}: ${OBJ}
	${CC} -o $@ ${LDFLAGS} ${OBJ}

%.o: %.c
	${CC} -c $< ${CFLAGS}

install: ${PROG}
	sudo mkdir -p ${INSTALL_DIR}
	sudo install -m 755 ${PROG} ${INSTALL_DIR}/

clean:
	-rm ${OBJ} ${PROG}

.PHONY: all clean
