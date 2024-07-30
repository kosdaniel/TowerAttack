CXX = g++
CXX_FLAGS = -Wall -pedantic -Wextra -std=c++17

all: kosdani2

compile: kosdani2

run: kosdani2
	./kosdani2


kosdani2: build/CApplication.o build/CCoord.o build/CCoord.o build/CFireTower.o build/CFreezeTower.o build/CGame.o build/CGroundTroop.o build/CInterface.o build/CMap.o build/CShieldTroop.o build/CSniperTower.o build/CTower.o build/CTroop.o build/CFlyingTroop.o build/main.o build/CPlayer.o build/CTroopStore.o build/CTowerAI.o
	$(CXX) $(CXX_FLAGS) $^ -o $@

build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CXX_FLAGS) $< -c -o $@


clean:
	rm -rf kosdani2 build

doc: doc src/*.h
	doxygen Doxyfile

build/CApplication.o: src/CApplication.cpp src/CApplication.h
build/CCoord.o: src/CCoord.cpp src/CCoord.h
build/CFireTower.o: src/CFireTower.cpp src/CFireTower.h src/CTower.h \
 src/CCoord.h src/CTroop.h src/CMap.h
build/CFlyingTroop.o: src/CFlyingTroop.cpp src/CFlyingTroop.h src/CMap.h \
 src/CCoord.h src/CTroop.h
build/CFreezeTower.o: src/CFreezeTower.cpp src/CFreezeTower.h src/CTower.h \
 src/CCoord.h src/CTroop.h src/CMap.h
build/CGame.o: src/CGame.cpp src/CGame.h src/CTower.h src/CCoord.h src/CTroop.h \
 src/CMap.h src/CPlayer.h src/CInterface.h src/CTroopStore.h \
 src/CTowerAI.h src/constants.h
build/CGroundTroop.o: src/CGroundTroop.cpp src/CGroundTroop.h src/CTroop.h \
 src/CCoord.h src/CMap.h
build/CInterface.o: src/CInterface.cpp src/CInterface.h src/CMap.h src/CCoord.h \
 src/CTroopStore.h src/CTroop.h
build/CMap.o: src/CMap.cpp src/CMap.h src/CCoord.h src/constants.h
build/CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CInterface.h src/CMap.h \
 src/CCoord.h src/CTroopStore.h src/CTroop.h src/constants.h
build/CShieldTroop.o: src/CShieldTroop.cpp src/CShieldTroop.h \
 src/CGroundTroop.h src/CTroop.h src/CCoord.h src/CMap.h
build/CSniperTower.o: src/CSniperTower.cpp src/CSniperTower.h src/CTower.h \
 src/CCoord.h src/CTroop.h src/CMap.h
build/CTower.o: src/CTower.cpp src/CTower.h src/CCoord.h src/CTroop.h \
 src/CMap.h
build/CTowerAI.o: src/CTowerAI.cpp src/CTowerAI.h src/CTower.h src/CCoord.h \
 src/CTroop.h src/CMap.h src/CInterface.h src/CTroopStore.h \
 src/CFreezeTower.h src/CFireTower.h src/CSniperTower.h src/constants.h
build/CTroop.o: src/CTroop.cpp src/CTroop.h src/CCoord.h src/CMap.h
build/CTroopStore.o: src/CTroopStore.cpp src/CTroopStore.h src/CTroop.h \
 src/CCoord.h src/CMap.h src/CInterface.h src/CGroundTroop.h \
 src/CFlyingTroop.h src/CShieldTroop.h src/constants.h
build/main.o: src/main.cpp src/CInterface.h src/CMap.h src/CCoord.h \
 src/CTroopStore.h src/CTroop.h src/CPlayer.h src/CTowerAI.h src/CTower.h \
 src/CGame.h


