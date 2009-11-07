all: limpiar

limpiar: limpiar.c
	gcc -O2 limpiar.c -o limpiar

clean:
	rm *~ limpiar