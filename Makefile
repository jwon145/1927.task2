CC      = colorgcc
CFLAGS  = -Wall -Werror
OBJS    = main.o dictionary.o
TARGET  = dict
DEBUG   = -g -fmudflap -lmudflap

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG)

dict: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(DEBUG)
	
clean:
	rm -f $(OBJS) $(TARGET) core

submit:
	yes yes | give cs1927 ass2 dictionary.c testing.txt
