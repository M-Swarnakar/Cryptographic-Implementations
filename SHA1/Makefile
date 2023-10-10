CC = gcc
CFLAG = -c

#SHA1 

SHA1: sha1_int_main.o sha1Main.o Sha1Padding.o
	$(CC) sha1_int_main.o sha1Main.o Sha1Padding.o -o sha1
sha1_int_main.o: sha1_int_main.c
	$(CC) $(CFLAG) sha1_int_main.c
sha1Main.o: sha1Main.c
	$(CC) $(CFLAG) sha1Main.c
Sha1Padding.o: Sha1Padding.c
	$(CC) $(CFLAG) Sha1Padding.c
 
#HMAC 
HMAC: hmac.o hmac_int_main.o sha1Main.o Sha1Padding.o
	$(CC) hmac_int_main.o hmac.o sha1Main.o Sha1Padding.o -o hmac
hmac.o: hmac.c
	$(CC) $(CFLAG) hmac.c
hmac_int_main.o: hmac_int_main.c hmac.h
	$(CC) $(CFLAG) hmac_int_main.c

#Clean the executable

CLEAN: 
	rm -rf *.o sha1 hmac
