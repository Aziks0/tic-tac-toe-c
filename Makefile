BINNAME = main

SRCDIR = src
INCLDIR = include
OBJDIR = obj
BINDIR = bin

CC = gcc
CFLAGS = -Wall -g
IFLAGS = -I ${INCLDIR}
SOURCES = ${wildcard ${SRCDIR}/*.c}
OBJECTS := ${SOURCES:${SRCDIR}/%.c=${OBJDIR}/%.o}

vpath %.c ${SRCDIR}
vpath %.o ${OBJDIR}
vpath %.h ${INCLDIR}

.PHONY: all debug release clean
all: debug

# Create the obj directory
${OBJDIR}:
	mkdir -p $@

# Create the bin directory
${BINDIR}:
	mkdir -p $@

# Compile sources
${OBJDIR}/%.o: ${SRCDIR}/%.c ${OBJDIR}
	${CC} ${CFLAGS} ${IFLAGS} -c -o $@ $<

# Build binary
debug: ${OBJECTS} ${BINDIR}
	${CC} ${CFLAGS} -o ${BINDIR}/${BINNAME} ${OBJECTS}

# Build binary with optimizations
release: CFLAGS += -O
release: ${OBJECTS} ${BINDIR}
	${CC} ${CFLAGS} -o ${BINDIR}/${BINNAME}_release ${OBJECTS}

clean:
	-rm -f ${OBJDIR}/* ${BINDIR}/*
