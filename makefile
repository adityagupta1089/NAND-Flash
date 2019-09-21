IDIR=include
SDIR=src
ODIR=bin

CC=clang++
CFLAGS=-I $(IDIR) -std=c++14

DEPS = $(wildcard $(IDIR)/*.hpp)

_SOURCES = $(wildcard $(SDIR)/*.cpp)
SOURCES = $(filter-out $(SDIR)/main.cpp, $(_SOURCES))

_OBJ = $(SOURCES:.cpp=.o)
OBJ = $(patsubst $(SDIR)/%, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: $(OBJ)
	$(CC) -o $(ODIR)/main.o $(SDIR)/main.cpp $(OBJ) $(CFLAGS)

.PHONY: clean

install:
	make clean
	tar --exclude='*.tar.gz' \
		--exclude='\.\/.*' \
		--exclude='bin' \
		-zvcf 2015CSB1003.tar.gz .

clean:
	rm -f $(ODIR)/*.o core