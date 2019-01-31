

eecs getObj:eecs.o csapp.o getObj.o
	gcc -o eecs eecs.o csapp.o
	gcc -o getObj csapp.o getObj.o

csapp.o:csapp.h

.PHONY : clean
clean:
	-rm eecs getObj *.o
