
all: library cli


library: library.c dataloader.c dataloader.h
	gcc -shared -o libdataloader.so -fPIC library.c dataloader.c

cli: cli.c dataloader.c dataloader.h
	gcc -o dataloader_cli cli.c dataloader.c


install: library cli
	cp libdataloader.so /usr/local/lib/
	cp dataloader_cli /usr/local/bin/
