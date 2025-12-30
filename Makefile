
all: easylogin-cli


#library: library.c dataloader.c dataloader.h
#	gcc -shared -o libdataloader.so -fPIC library.c dataloader.c

easylogin-cli: cli.c dataloader.c dataloader.h
	gcc -std=c17 -Wall -Werror -o easylogin-cli cli.c dataloader.c


install: easylogin-cli
	#cp libdataloader.so /usr/local/lib/
	cp easylogin-cli /usr/local/bin/
