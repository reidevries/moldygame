CC=g++
CFLAGS=-lraylib -lglfw -lGL -lopenal -lm -pthread -ldl
CWARNINGS=-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

all: bin_linux64

bin_linux64: $(obj)
	$(CC) -o $@ $^ $(CFLAGS) $(CWARNINGS)
	
clean:
	rm -f $(obj) bin_linux64
