test_file = image.h5

dir_inc = /usr/include
dir_lib = /usr/lib/

dir_bin = .

INC = -I$(dir_inc)
LIB = -L$(dir_lib) -lhdf5_hl -lhdf5 -lz -lpng -lm

SRC1 = h5png.cc
SRC2 = h5png_main.cc
SRC3 = h5png_test.cc

OBJ1 = h5png.o
OBJ2 = h5png_main.o
OBJ3 = h5png_test.o

EXE1 = $(dir_bin)/h5png
EXE2 = $(dir_bin)/h5png_test

OBJs = $(OBJ1) $(OBJ2) $(OBJ3)
EXEs = $(EXE1) $(EXE2)

CXX = g++
CXX_FLAG = -g -Wall -std=c++0x
LINK_FLAG = -lstdc++ 

all:  $(EXEs) 

$(EXE1) : $(OBJ1) $(OBJ2)
	$(CXX) $(LINK_FLAG) -o $(EXE1) $(OBJ1) $(OBJ2) $(LIB)

$(EXE2) : $(OBJ1) $(OBJ3)
	$(CXX) $(LINK_FLAG) -o $(EXE2) $(OBJ1) $(OBJ3) $(LIB)

$(OBJ1) : $(SRC1)
	$(CXX) $(INC) $(CXX_FLAG) -c $(SRC1) -o $(OBJ1)

$(OBJ2) : $(SRC2)
	$(CXX) $(INC) $(CXX_FLAG) -c $(SRC2) -o $(OBJ2)
	
$(OBJ3) : $(SRC3)
	$(CXX) $(INC) $(CXX_FLAG) -c $(SRC3) -o $(OBJ3)

clean:
	rm -f $(OBJs) $(EXEs)

test:
	$(EXE2) $(test_file)
