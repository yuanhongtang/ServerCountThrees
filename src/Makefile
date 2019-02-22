# Name: David Tang
# Course: CIS145 Introduction to DevOps
# CRN: 45595
# Date: 2/19/2019
# Assignment: Makefile - Build and Launch ServerCountThrees

CC=gcc
ODIR=../build

runCount3s: ServerCountThrees 
	cp ../data/threesData.bin $(ODIR)
	$(ODIR)/ServerCountThrees
	

ServerCountThrees: ServerCountThrees.o readInt32BitLE.o
	cp ServerCountThrees.o readInt32BitLE.o ../build
	$(CC) -o $(ODIR)/ServerCountThrees $(ODIR)/ServerCountThrees.o $(ODIR)/readInt32BitLE.o

ServerCountThrees.o: init readInt32BitLE.h
	cp ServerCountThrees.c readInt32BitLE.h $(ODIR)
	$(CC) -c $(ODIR)/ServerCountThrees.c $(ODIR)/readInt32BitLE.h 


readInt32BitLE.o: init readInt32BitLE.c
	cp readInt32BitLE.c $(ODIR) 
	$(CC) -c $(ODIR)/readInt32BitLE.c 

init: 
	mkdir $(ODIR)


.PHONY: clean
clean:
	rm -rf *.o *.gch $(ODIR)
