// wator-sim.cpp --- 
// 
// Filename: wator-sim.cpp
// Description: 
// Author: Denis Perepelyuk
// Student No.: C00259076
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Code:

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace std;

// ******************
// Defining constants
// ******************

// Program parameters
const int NUM_SHARK = 0;
const int NUM_FISH = 0;
const int FISH_BREED = 0;
const int SHARK_BREED = 0;
const int STARVE = 0;
const int GRID_SIZE = 0;
const int THREADS = 0;
const int ENERGY_GAIN = 0;

// Grid parameters
const int ROWS = 0;
const int COLUMNS = 0;


// Visualisation sizes
const int WINDOW_X_SIZE = 0;
const int WINDOW_Y_SIZE = 0;
const int CELL_X_SIZE = 0;
const int CELL_Y_SIZE = 0;

// Define colors
const sf::Color OCEAN_COLOUR = sf::Color(30, 30, 30);
const sf::Color FISH_COLOUR = sf::Color(0, 100, 255);
const sf::Color SHARK_COLOUR = sf::Color(255, 50, 50);

enum CellType {
    ocean,
    shark,
    fish
};

class Cell {
    private:
        CellType cellType;
        sf::Color colour;
        int xPos;
        int yPos;
    public:
        Cell() {}
        Cell(int x, int y, CellType type) {
            setCellType(type);
            setXPos(x);
            setYPos(y);
            setColour();
        }

        CellType getCellType() { return cellType; }
        int getXPos() { return xPos; }
        int getYPos() { return yPos; }
        sf::Color getColour() { return colour; }
        
        void setCellType(CellType ct) { cellType = ct; }
        void setXPos(int x) { xPos = x; }
        void setYPos(int y) { yPos = y; }
        void setColour() {
            CellType ct = getCellType();
            switch(ct) {
                case CellType::fish:
                    colour = FISH_COLOUR;
                    break;
                case CellType::shark:
                    colour = SHARK_COLOUR;
                    break;
                default:
                    colour = OCEAN_COLOUR;
                    break;  
            }
        }

};

Cell grid[ROWS][COLUMNS];

Cell* getAdjacentCells(int x, int y) {
    // Nedd to do something for edge of grid
    // Could use modulus for this
    Cell north = grid[x][y+1];
    Cell east = grid[x+1][y];
    Cell west = grid[x-1][y];
    Cell south = grid[x][y-1];

    Cell adjacentCells[4] = { north, east, west, south };
    return adjacentCells;
}

class Ocean: public Cell {
    private:
    public:
        Ocean(int x, int y) {
            setCellType(CellType::ocean);
            setXPos(x);
            setYPos(y);
            setColour();
        }
};

class SeaCreature: public Cell {
    private:
        int age;
        bool canBreed;
        bool moved;
    public:
        SeaCreature() {}
        int getAge() { return age; }
        bool getCanBreed() { return canBreed; }
        bool hasMoved() { return moved; }

        void setAge(int a) { age = a; }
        void move() {}
        void breed() {}
};



class Fish: public SeaCreature {
    private:
    public:
    Fish(int x, int y) {
        setCellType(CellType::fish);
        setXPos(x);
        setYPos(y);
        setColour();
    }
    void moveFish() {
        bool hasMoved = false;
        int x = getXPos();
        int y = getYPos();
        int direction = rand() % 4;
        Cell* adjacentCells = getAdjacentCells(x, y);
        
        for(int i = 0; i < 4; i++) {
            Cell ct = adjacentCells[i];

            if(ct.getCellType() == CellType::ocean) {       
                Cell temp = grid[x][y];
                Ocean o = Ocean(temp.getXPos(), temp.getYPos());
                grid[ct.getXPos()][ct.getYPos()] = o;
                grid[ct.getXPos()][ct.getXPos()] = temp; 
                
                if(getCanBreed()) {
                    setAge(0);
                    Fish f = Fish(ct.getXPos(), ct.getYPos());
                    grid[ct.getXPos()][ct.getXPos()] = f;
                }
                break;
            }
        }
    }
};

class Shark: public SeaCreature {
    private:
        int sharkBreed;
        int energy;
    public:
        Shark(int x, int y) {
            setCellType(CellType::shark);
            setXPos(x);
            setYPos(y);
            setColour();
        }

        void starve() {
            if (energy == 0) {
                // die -> set cell to ocean
            }
        }

        bool hasStarved() {
            if (energy == 0) {
                return true;
            }
        }

        void eat() {
            energy += ENERGY_GAIN;
            Ocean oc(getXPos(), getYPos());
        }
};

// initialise grid
void populate() {}

//
void serial(){
    srand(static_cast<unsigned>(time(nullptr)));
}


void parallel(){};
int main() {

    srand(static_cast<unsigned>(time(nullptr)));
    return 0;
}