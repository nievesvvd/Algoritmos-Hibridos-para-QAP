CXX = g++
OBJ = obj
INC = include
BIN = bin
LIB = lib
SRC = src
CXXFLAGS =-Wall -g -std=c++11 -c -O1


$(BIN)/main:$(OBJ)/main.o $(OBJ)/funciones.o $(OBJ)/AGG.o $(OBJ)/data.o $(OBJ)/random_ppio.o #$(OBJ)/dos_timer.o
	$(CXX) -o $(BIN)/main $^

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/funciones.h $(INC)/AGG.h $(INC)/data.h
	$(CXX) $(CXXFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)

$(OBJ)/AGG.o: $(SRC)/AGG.cpp $(INC)/AGG.h $(INC)/data.h $(INC)/random_ppio.h $(INC)/funciones.h
	$(CXX) $(CXXFLAGS) $(SRC)/AGG.cpp -o $(OBJ)/AGG.o -I$(INC)

$(OBJ)/funciones.o: $(SRC)/funciones.cpp $(INC)/funciones.h $(INC)/data.h $(INC)/random_ppio.h
	$(CXX) $(CXXFLAGS) $(SRC)/funciones.cpp -o $(OBJ)/funciones.o -I$(INC)

$(OBJ)/data.o: $(SRC)/data.cpp $(INC)/data.h
	$(CXX) $(CXXFLAGS) $(SRC)/data.cpp -o $(OBJ)/data.o -I$(INC)

$(OBJ)/random_ppio.o: $(SRC)/random_ppio.cpp $(INC)/random_ppio.h
	$(CXX) $(CXXFLAGS) $(SRC)/random_ppio.cpp -o $(OBJ)/random_ppio.o -I$(INC)

clean:
	rm $(OBJ)/*; rm $(BIN)/main;