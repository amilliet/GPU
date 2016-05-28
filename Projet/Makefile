
ARCH            := $(shell uname -s | tr a-z A-Z)

PROG	:=	sable

CFLAGS	:=	-g -O3 -std=c99 -Wno-deprecated-declarations
ifeq ($(ARCH),DARWIN)
CFLAGS	+=	-I /opt/local/include
LDFLAGS	+=	-L /opt/local/include
LDLIBS	+=	-framework GLUT -framework OpenGL -framework OpenCL
else
LDLIBS		:= -lOpenCL -lGL -lGLU -lglut -lm
endif

.phony: default clean

default: $(PROG)

$(PROG): main.o display.o other_sequentielle.o basic.o utile.o propagation.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

main.o: display.h other_sequentielle.h propagation.h basic.h

display.o: display.h

utile.o: utile.h parameter.h 

propagation.o: propagation.h parameter.h utile.h

basic.o: basic.h parameter.h utile.h

other_sequentielle.o: parameter.h other_sequentielle.h utile.h 

clean:
	rm -rf *.o $(PROG)
