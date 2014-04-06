CXX = gcc
CCFLAGS = -Wall -Werror -ansi -pedantic -fPIC -g
#fPIC : compile for all UNIX-based systems

LIBS = -lBibtexManager
LIBSDIR = -L/usr/lib/ -L./
#where are the libraries ( . : current folder)
INCLUDEDIR = -I. -I/usr/include/

LIBNAME = libBibtexManager.so
#binary of the library
LIBFILES = bibtexmanager types printLibrary getFromLibrary
SOURCELIBFILES = $(LIBFILES:=.c)
OBJECTLIBFILES = $(LIBFILES:=.o)

TARGET = main.exe
TARGETFILES = main 
SOURCETARGETFILE = $(TARGETFILES:=.c)
OBJECTTARGETFILE = $(TARGETFILES:=.o)

export LD_LIBRARY_PATH=`pwd` 

all: $(TARGET)

#$@ : $<
$(TARGET): $(OBJECTTARGETFILE) $(LIBNAME)
	@echo "\nGeneration of " $(TARGET)
	$(CXX) $(CCFLAGS) $(LIBSDIR) -o $(TARGET) $(OBJECTTARGETFILE) $(LIBS)

.c.o:
	@echo "\nGeneration of " $@ " from " $<
	$(CXX) $(INCLUDEDIR) $(CCFLAGS) -c -o $@ $<

$(LIBNAME): $(OBJECTLIBFILES)
	@echo "\nLibrary Generation named " $(LIBNAME)
	$(CXX) $(CCFLAGS) -shared -o $(LIBNAME) $(OBJECTLIBFILES)

clean:
	@echo "\n Cleaning current directory"
	rm -f *.o *~ 
