CC = gcc
CFLAG = -c

SHA1: sha1_int_main.o sha1Main.o Sha1Padding.o
	$(CC) sha1_int_main.o sha1Main.o Sha1Padding.o -o sha1
sha1_int_main.o: sha1_int_main_.c
	$(CC) $(CFLAG) sha1_int_main.c
sha1Main.o: sha1Main.c
	$(CC) $(CFLAG) sha1Main.c
Sha1Padding.o: ShaPadding.c
	$(CC) $(CFLAG) ShaPadding.c

#Clean the executable

CLEAN: 
	rm -rf *.o sha1
