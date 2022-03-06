GCC			= g++
GUIPATH 	= lib/sfml
OUTPUT		= build/editor
MAINFILE	= main.cpp
SOURCES	 	= $(wildcard src/*.cpp)
DEMOFILE	= documents/file.txt

GUIINC	= $(GUIPATH)/include
GUILIB = $(GUIPATH)/lib

INCS	= -I$(GUIINC) -Isrc
LIBS	= -L$(GUILIB) -lsfml-graphics -lsfml-window -lsfml-system

MAINOBJ = $(MAINFILE:.cpp=.o)
LINKOBJ = $(SOURCES:.cpp=.o)

$(OUTPUT): $(MAINOBJ) $(LINKOBJ)
	$(GCC) build/$(MAINOBJ) $(patsubst %,build/%,$(LINKOBJ)) $(INCS) $(LIBS) -o $(OUTPUT)
	export LD_LIBRARY_PATH=$(GUILIB) && ./build/editor $(DEMOFILE)

.cpp.o:
	$(GCC) -g -c $< -o build/$@ $(INCS)

clean:
	rm -f build/*