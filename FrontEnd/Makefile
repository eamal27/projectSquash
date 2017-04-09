CC=g++
CCFLAGS = -Wall -std=c++11 -g
IFLAGS = -I $(IDIR)
LIBS = 

# Subdirectories for different types of files
TDIR=.
ODIR=objs
SRCDIR=frontend/src
IDIR=frontend/include

CSRC=$(wildcard $(SRCDIR)/*.c)
CPPSRC=$(wildcard $(SRCDIR)/*.cpp)

SRC = $(CPPSRC) $(CCSRC)

CPPOBJS = $(patsubst %.cpp, %.o, $(CPPSRC))
COBJS = $(patsubst %.c, %.o, $(CSRC))

OBJS = $(CPPOBJS) $(COBJS)

# Target program name
TARGET=sqa.out

# function for selecting corresponding
# source file from object file

all: $(TDIR)/$(TARGET)

$(TDIR)/$(TARGET): $(CPPOBJS)
	echo $(CPPOBJS)
	$(CC) $(CCFLAGS) $(IFLAGS) $^ $(LIBS) -o $@

$(CPPOBJS): $(CPPSRC)
	$(CC) $(CCFLAGS) $(IFLAGS) -c $(patsubst %.o, %.cpp, $@) -o $@

clean:
	\rm $(OBJS)
	\rm $(TDIR)/$(TARGET)
