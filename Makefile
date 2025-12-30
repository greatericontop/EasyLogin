
all: easylogin.so easylogin-cli


easylogin.so: library.c dataloader.c dataloader.h
	gcc -std=c17 -Wall -Werror -shared -fPIC -o easylogin.so library.c dataloader.c

easylogin-cli: cli.c dataloader.c dataloader.h
	gcc -std=c17 -Wall -Werror -o easylogin-cli cli.c dataloader.c


install: easylogin.so easylogin-cli
	cp easylogin.so /lib/x86_64-linux-gnu/security
	cp easylogin-cli /usr/local/bin/
