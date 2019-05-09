hotel : hotel.o getoccupier.o findfree.o freeroom.o addguest.o

hotel.o : hotel.h hotel.c

getoccupier.o : hotel.h getoccupier.h getoccupier.c

findfree.o : hotel.h findfree.h  findfree.c

freeroom.o : hotel.h freeroom.h  freeroom.c

addguest.o : hotel.h addguest.h getoccupier.h addguest.c

clean :
	rm *.o


