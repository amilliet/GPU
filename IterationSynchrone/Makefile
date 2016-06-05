
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

$(PROG): main.o display.o eboulement.o utile.o vision_voisin.o vision_avant.o propagation.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

main.o: display.h eboulement.h vision_voisin.h vision_avant.h propagation.h

display.o: display.h

utile.o: utile.h parameter.h 

eboulement.o: eboulement.h parameter.h utile.h

propagation.o: utile.h parameter.h propagation.h

vision_voisin.o: vision_voisin.h utile.h parameter.h

vision_avant.o: vision_avant.h utile.h parameter.h

clean:
	rm -rf *.o $(PROG)
