TARGET = libdp-framework.a

SRC = ./src
INC = ./include
OBJ = ./obj
LIB = ./lib

INCLUDES = -I./include

CPPFLAGS = $(INCLUDES) -O0 -g -Wall -c

HEADERS = $(INC)/dp_events.h $(INC)/dp_peripherals.h $(INC)/dp_bb4io.h $(INC)/dp_ping4.h $(INC)/dp_count4.h $(INC)/dp_adc812.h $(INC)/dp_dc2.h
OBJECTS = $(OBJ)/dp_events.o $(OBJ)/dp_peripherals.o $(OBJ)/dp_bb4io.o $(OBJ)/dp_ping4.o $(OBJ)/dp_count4.o $(OBJ)/dp_adc812.o $(OBJ)/dp_dc2.o

.PHONY: all
all: $(TARGET)

$(TARGET) : $(OBJECTS)
	ar rcs $(LIB)/$@ $(OBJECTS)

$(OBJ)/%.o: $(SRC)/%.cpp $(HEADERS)
	g++ $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(LIB)/* $(OBJ)/*


