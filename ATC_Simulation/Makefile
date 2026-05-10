CXX      = g++
CXXFLAGS = -std=c++17 -Wall
SFML     = -lsfml-graphics -lsfml-window -lsfml-system

all: radarTower atc_gui

radarTower: radarTower.cpp
	$(CXX) $(CXXFLAGS) -o radarTower radarTower.cpp

atc_gui: atc_gui.cpp
	$(CXX) $(CXXFLAGS) -o atc_gui atc_gui.cpp $(SFML)

clean:
	rm -f radarTower atc_gui
