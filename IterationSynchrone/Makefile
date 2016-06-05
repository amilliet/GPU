
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

$(PROG): main.o display.o eboulement.o utile.o visison_voisin.o visison_voisin_avant.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

main.o: display.h eboulement.h visison_voisin.h visison_voisin_avant.h

display.o: display.h

utile.o: utile.h parameter.h 

eboulement.o: eboulement.h parameter.h utile.h

visison_voisin.o: visison_voisin.h utile.h parameter.h

visison_voisin_avant.o: visison_voisin_avant.h utile.h parameter.h

clean:
	rm -rf *.o $(PROG)
