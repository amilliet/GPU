
ARCH            := $(shell uname -s | tr a-z A-Z)

PROG	:=	sable

CFLAGS	:=	-g -O3 -std=c99 -Wno-deprecated-declarations -fopenmp
ifeq ($(ARCH),DARWIN)
CFLAGS	+=	-I /opt/local/include
LDFLAGS	+=	-L /opt/local/include
LDLIBS	+=	-framework GLUT -framework OpenGL -framework OpenCL
else
LDLIBS		:= -lOpenCL -lGL -lGLU -lglut -fopenmp -lm 
endif

.phony: default clean

default: $(PROG)

$(PROG): main.o display.o basic.o utile.o other_sequentielle.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

main.o: display.h basic.h

display.o: display.h

utile.o: utile.h parameter.h 

basic.o: basic.h parameter.h utile.h

other_sequentielle.o: other_sequentielle.h utile.h parameter.h

clean:
	rm -rf *.o $(PROG)
