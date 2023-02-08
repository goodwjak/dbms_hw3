# Define required macros here
SHELL= /bin/sh

#OBJS =  main.o factorial.o hello.o
CC= g++ 
DEBUGGER= gdb 

NAME=prog
IN= ./src/cleaned_ExternalMemorySort.cpp
OUT= ./build/${NAME} 
BIN= ./build/bin/${NAME}
CFLAG= -std=c++11 -O0  -Wall
INCLUDE=-I"/usr/local/include/"
LIBS=

#Generates unoptimized and debugable binary
run:${IN}
	${CC} ${CFLAG} -g ${IN} -o ${OUT} ${INCLUDE}  ${LIBS}
	${OUT}

build:${IN}	
	${CC} ${CFLAG} ${IN} -o ${BIN} ${INCLUDE}  ${LIBS}

debug:
	echo 'Building debugable executable'
	${CC} ${CFLAG} -g ${IN} -o ${OUT} ${INCLUDE} ${LIBS}
	${DEBUGGER} ${OUT}

release:${IN}
	${CC}  -O3 ${CFLAG} ${IN} -o ${BIN} ${INCLUDE}  ${LIBS}

clean:
	echo "Cleaning the debug/bin folders"
	rm ${OUT}
	rm ${BIN}

