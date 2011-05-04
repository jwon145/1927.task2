CC      = colorgcc
CFLAGS  = -Wall -Werror
OBJS    = main.o dictionary.o
TARGET  = dict

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

textbuffer: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
	
clean:
	rm -f $(OBJS) $(TARGET) core

submit:
	yes yes | give cs1927 ass2 dictionary.c testing.txt
