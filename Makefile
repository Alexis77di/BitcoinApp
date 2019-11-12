#Makefile
OBJS = bitcoinApp.o hashtable.o hashwallet.o linkedlist.o
SOURCE = bitcoinApp.cpp hashtable.cpp hashwallet.cpp linkedlist.cpp
HEADER = headers.h hahstable.h hashwallet.h linkedlist.h
OUT = bitcoin
FLAGS = -g -c

# -g option enables debugging mode
# -c flag generates object code for separate files

all: $(OBJS)
	g++ -g bitcoinApp.cpp hashtable.cpp hashwallet.cpp linkedlist.cpp
	mv a.out $(OUT)

# create / compile the individual files separately
bitcoinApp.o: bitcoinApp.cpp
	$(CC) $(FLAGS) bitcoinApp.cpp

hashtable.o: hashtable.cpp
	$(CC) $(FLAGS) hashtable.cpp
hashwallet.o: hashwallet.cpp
	$(CC) $(FLAGS) hashwallet.cpp
linkedlist.o: linkedlist.cpp
	$(CC) $(FLAGS) linkedlist.cpp

# cleaning
clean:
	rm -f $(OBJS) $(OUT)

# accounting
count:
	wc $(SOURCE) $(HEADER)

