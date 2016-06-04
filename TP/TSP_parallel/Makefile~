src=$(wildcard *.c)
obj=$(src:.c=.o)
CFLAGS=-Wall -g -O3 -fopenmp
LDLIBS=-lm 
PRG=tsp
$(PRG): $(obj)
	  $(CC) -o $@ $^ $(LDLIBS)
clean:		   
		   -/bin/rm -f $(obj) $(PRG)
