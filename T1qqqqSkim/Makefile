include Makefile.arch

SOURCES=$(wildcard *.cc) $(wildcard ../MT2CORE/*.cc)

OBJECTS=$(SOURCES:.cc=.o)

LIB=libT1qqqqSkim.so

EXE = T1qqqqSkim.exe

$(LIB): $(OBJECTS)
	$(LD) $(LDFLAGS) $(SOFLAGS) $(OBJECTS) $(ROOTLIBS) -o $@

$(EXE): $(LIB) 
	echo "$(CXX) -o $@ $(LIB) $(ROOTLIBS) -Wl,-rpath,./"; \
	$(CXX) -o $@ $(LIB) $(ROOTLIBS) -Wl,-rpath,./	

%.o:  %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: 	$(EXE)
libs: 	$(LIB)
clean:
	rm -f *.o \
	rm -f *.d \
	rm -f *.so \
