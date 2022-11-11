DBG        = #-ggdb3
OPTFLAGS   = -Wall -Wextra -Wstrict-prototypes -Wmissing-prototypes $(DBG) -pedantic -lstdc++

SRC        = mipirawprocess.c
TARGET     = mipirawprocess
OBJ        = $(SRC:.c=.o)

default: $(TARGET)

%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm $(OBJ) $(TA
