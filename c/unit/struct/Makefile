all:
	gcc main.c struct.c -o app

app_so:
	make so;
	gcc main.c -L. -lstruct -o app

app_a:
	make a;
	gcc main.c -L. -lstruct --static -o app

so:
	gcc -fPIC --shared struct.c -o libstruct.so

a:
	gcc -c struct.c
	ar rs libstruct.a struct.o

clean:
	rm -rf app
	rm -rf *.o
	rm -rf *.so
	rm -rf *.a
