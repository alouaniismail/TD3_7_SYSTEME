LDFLAGS=-L.
LDLIBS=-lutils
CFLAGS+= -D_GNU_SOURCE 

libutils.a: utils.o
	ar r $@ $?

clean:
	rm -f *~ *.o libutils.a
