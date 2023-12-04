// wator-sim.cpp --- 
// 
// Filename: wator-sim.cpp
// Description: 
// Author: Denis Perepelyuk
// Student No.: C00259076

/**
* @file
* @author Denis Perepelyuk C00259076
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* @section DESCRIPTION
*
* Code that simulates the Wa-Tor problem. This program simulates both sequentially and concurrently.
*/

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
const int STARVE = 3;
const int GRID_SIZE = 100;
const int THREADS = 0;
const int ENERGY_GAIN = 0;

// Grid parameters
const int ROWS = 100;
const int COLUMNS = 100;

// Visualisation sizes
const int WINDOW_X_SIZE = 100;
const int WINDOW_Y_SIZE = 100;
const int CELL_X_SIZE = 10;
const int CELL_Y_SIZE = 10;

// Define colors
const sf::Color OCEAN_COLOUR = sf::Color(30, 30, 30);
const sf::Color FISH_COLOUR = sf::Color(0, 100, 255);
const sf::Color SHARK_COLOUR = sf::Color(255, 50, 50);

// Define SFML variables
sf::RenderWindow window;

// Enumeration for types of cell
enum CellType {
    ocean,
    shark,
    fish
}; 

/**
* @brief Base cell class
* @author Denis P
*
* Base Cell class that will represent a single cell of the simulation that will either contain a fish, shark or ocean cell.
*/
class Cell {
    private:
        CellType cellType;
        sf::Color colour;
        int xPos;
        int yPos;
    public:
        Cell() {}

        /**
         * Constructor that sets the base properties.
         *
         * @param x X position within the grid array
         * @param y Y position within the grid array
         * @param type Type of cell to be stored in array (fish, shark or ocean.
         */
        Cell(int x, int y, CellType type) {
            setCellType(type);
            setXPos(x);
            setYPos(y);
            setColour();
        }

        /**
             * Draws the cell a base colour depending on the type of cell it is.
             *
             * @param x X position within the grid array
             * @param y Y position within the grid array
         */
        void draw(int x, int y) {
            sf::RectangleShape gridCell(sf::Vector2f(CELL_X_SIZE, CELL_Y_SIZE));
            gridCell.setPosition(x * CELL_X_SIZE, y * CELL_Y_SIZE);
            gridCell.setFillColor(getColour());
            window.draw(gridCell);
        }

        /**
            * Returns the type of cell (fish, shark or ocean).
            *
        */
        CellType getCellType() { return cellType; }
        
        /**
            * Returns the x co-ordinate of the cell
            *
        */
        int getXPos() { return xPos; }

        /**
            * Returns the y co-ordinate of the cell
            *
        */
        int getYPos() { return yPos; }
        sf::Color getColour() { return colour; }
        
        void setCellType(CellType ct) { cellType = ct; }
        void setXPos(int x) { xPos = x; }
        void setYPos(int y) { yPos = y; }
        
        /**
            * Sets the colour of the cell based on it's CellType enum
            *
        */
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
        void move(int x, int y){}
};

// Grid composed of cells that will be rendered
Cell grid[ROWS][COLUMNS];

/**
* @brief Ocean class that represents water in the simulation
* @author Denis P
*
* Base Cell class that will represent a single cell of the simulation that will either contain a fish, shark or ocean cell.
*/
class Ocean: public Cell {
    private:
    public:
        /**
             * Constructor that sets the base properties.
             *
             * @param x X position within the grid array
             * @param y Y position within the grid array
         */
        Ocean(int x, int y) {
            setCellType(CellType::ocean);
            setXPos(x);
            setYPos(y);
            setColour();
        }
};

/**
* @brief Parent class of fish and shark
* @author Denis P
*
* Class that will represent both fish and sharks. It will be inherited from both respective classes
*/
class SeaCreature: public Cell {
    private:
        int age;
        bool canBreed;
        bool moved;
    public:
        SeaCreature() {
            setColour();
        }
        int getAge() { return age; }
        void setAge(int a) { age = a; }
        void move() {}
};

/**
* @brief Fish Class
* @author Denis P
*
* Class that will represent fish with its behavior and properties.
*/
class Fish: public SeaCreature {
    private:
    public:
        /**
             * Constructor of Fish class
             *
             * @param x X position within the grid array
             * @param y Y position within the grid array
         */
        Fish(int x, int y) {
            setCellType(CellType::fish);
            setXPos(x);
            setYPos(y);
            setColour();
        }

        /**
         * Contains logic of fish moving including breeding
         *
         * @param i X position within the grid array
         * @param j Y position within the grid array
         */
        void move(int i, int j) {
            int xShift = rand() % 3 - 1;  
            int yShift = rand() % 3 - 1;  

            int newXPos = (i + xShift + ROWS) % ROWS;
            int newYPos = (j + yShift + COLUMNS) % COLUMNS;

            if(grid[newXPos][newYPos].getCellType() == CellType::ocean) {
                setXPos(newXPos);
                setXPos(newYPos);

                if(getAge() >= FISH_BREED) {
                    grid[i][j] = Fish(i, j);
                }
                else {
                    grid[i][j] = Ocean(i, j);
                }
            }
            setAge(getAge() + 1);
        }
};

/**
* @brief Shark Class
* @author Denis P
*
* Class that will represent shark with its behavior and properties.
*/
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

        /**
             * Contains logic of fish moving including breeding
             *
             * @param i X position within the grid array
             * @param j Y position within the grid array
         */
        void move(int i, int j) {
            int xShift = rand() % 3 - 1;  
            int yShift = rand() % 3 - 1;  

            int newXPos = (i + xShift + ROWS) % ROWS;
            int newYPos = (j + yShift + COLUMNS) % COLUMNS;

            if(grid[newXPos][newYPos].getCellType() == CellType::ocean) {
                setXPos(newXPos);
                setXPos(newYPos);

                if (getEnergy() == 0) {
                    grid[i][j] = Ocean(i, j);   
                }

                else if(getAge() >= SHARK_BREED) {
                    grid[i][j] = Shark(i ,j);
                }
                else {
                    grid[i][j] = Ocean(i, j);
                }
            }
            else if (grid[newXPos][newYPos].getCellType() == CellType::fish) {
                setXPos(newXPos);
                setXPos(newYPos);
                grid[i][j] = Ocean(i, j);
                setEnergy(getEnergy() + 1);
            }
            setEnergy(getEnergy() - 1);
            setAge(getAge() + 1);
        }

        int getEnergy() {
            return energy;
        }

        int setEnergy(int e) {
            energy = e;
        }
};

/**
     * Populates and initialises grid
     *
*/
void populateGrid() {
    std::srand(std::time(nullptr));
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            int random = std::rand() % 3;
            Cell c;
            switch(random) {
                case 0:
                    c = Ocean(i, j);
                    break;
                case 1:
                    c = Fish(i, j);
                    break;
                default:
                    c = Shark(i, j);
                    break;
            }
            grid[i][j] = c;
        }
    }    
}

/**
     * Checks for window closing
     *
*/
void windowClosing() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
/**
     * Updates grid with movement of fish and shark cells
     *
*/
void updateGrid() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if(grid[i][j].getCellType() == CellType::fish || grid[i][j].getCellType() == CellType::shark){
                grid[i][j].move(i, j);
            }
        }
    }
}

/**
     * Renders the simulation and draws the cells
     *
*/
// 
void renderSim() {
    window.clear(sf::Color::Black);
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                grid[i][j].draw(i, j);
            }
        }
        window.display();
}

/**
     * Runs the simulation in serial
     *
*/
void sequential(){
    // Create window
    window.create(sf::VideoMode(GRID_SIZE * CELL_X_SIZE, GRID_SIZE * CELL_Y_SIZE), "Wa-Tor Simulation (Serial) - Denis Perepelyuk");

    populateGrid();
    
    while(window.isOpen()){
        windowClosing();
        updateGrid();
        renderSim();
    }
}

/**
     * Runs the simulation in parallel
     *
*/
# pragma omp parallel
void parallel(){
    // Create window
    window.create(sf::VideoMode(GRID_SIZE * CELL_X_SIZE, GRID_SIZE * CELL_Y_SIZE), "Wa-Tor Simulation (Serial) - Denis Perepelyuk");

    populateGrid();
    
    while(window.isOpen()){
        windowClosing();
        updateGrid();
        renderSim();
    }
}
/**
     * Main method
     *
*/
int main() {
    sequential();
    return 0;
}