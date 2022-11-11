DBG        = #-ggdb3
OPTFLAGS   = -Wall -Wextra -Wstrict-prototypes -Wmissing-prototypes $(DBG) -pedantic

SRC        = thread.c
TARGET     = thread
OBJ        = $(SRC:.c=.o)

default: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) -lpthread


clean:
	rm $(OBJ) $(TARGET)
