CXX      = g++
CXXFLAGS = -std=c++17 -Wall

UNAME := $(shell uname -s)
ifeq ($(UNAME), Darwin)
    SFML_INC = -I/opt/homebrew/include
    SFML_LIB = -L/opt/homebrew/lib
else
    SFML_INC =
    SFML_LIB =
endif

SFML = $(SFML_INC) $(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system

all: radarTower atc_gui

radarTower: radarTower.cpp
	$(CXX) $(CXXFLAGS) -o radarTower radarTower.cpp

atc_gui: atc_gui.cpp
	$(CXX) $(CXXFLAGS) -o atc_gui atc_gui.cpp $(SFML)

clean:
	rm -f radarTower atc_gui
