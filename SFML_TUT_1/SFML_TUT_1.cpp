// Project:         SFML_TUT_1
// Author:          Carlos Rodriguez
// Date:            March, 3, 2022
// Purpose:         Create a visual representation of a bubble sort
//                  

#include <iostream>
#include <SFML\Graphics.hpp>
#include <random>
#include <windows.h>
#include <vector>

// Global Variables
const int screenHeight = 600;                               // default starting screen height
const int screenWidth = 600;                                // default starting screen width
const int widthBlock = 5;                                   // width of the blocks also controls the amount of blocks
const int amountOfBlocks = screenWidth / widthBlock;        // adding a const fixed error 
std::vector<sf::RectangleShape> vBars;                      // vector list of block objects


// Forward Declarations
int RandomGen(int, int);                                    // random number generator
void CreateBars();                                          // Create our blocks

using namespace sf;

int main()
{
    sf::RenderWindow window(VideoMode(screenWidth, screenHeight), "SFML Practice", Style::Close | Style::Resize);        // Create a window object with predefined attributes

    CreateBars();

    
    while (window.isOpen())                                                                         // loop while window is open
    {
        Event evnt;                                                                                 // create an Event object named evnt
        while (window.pollEvent(evnt))                                                              // while the window
        {
            switch (evnt.type)                                                                      // switch case for event types
            {
            case Event::Closed:                                                                     // if event is Closed
                window.close();                                                                     // close the window
                break;                                                                              

            case Event::Resized:                                                                    // if the event desired is to resize
                printf("New Window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);  // print out the new updated sizes
                break;

            case Event::TextEntered:                                                                // if the keyboard is used case event
                if (evnt.text.unicode < 128)                                                        // make sure the text is shorter than 128 ASCII
                    printf("%c", evnt.text.unicode);

            default:
                break;
                
            }

        }
       
        // on space bar press
        if (Keyboard::isKeyPressed(sf::Keyboard::Key::Space))       
        {  
            
            for (int i = 0; i < vBars.size(); i++)                  // draw our inital blocks
            {
                window.draw(vBars[i]);

            }
            window.display();
            
            RectangleShape tempBlock;
            
            for (int y = 0; y < vBars.size(); y++) {
                for (int x = 0; x < vBars.size() - 1; x++) {
                    if (vBars[x].getSize().y > vBars[x + 1].getSize().y) {          // if first block is larger than next 
                        window.clear();                                     

                        // temp block to swap places for out bubble sort in vector list
                        tempBlock = vBars[x];                                      
                        vBars[x] = vBars[x + 1];
                        vBars[x + 1] = tempBlock;

                        // set new pos of the block based on its new block data in vector list
                        vBars[x].setPosition(x* widthBlock, screenHeight);          
                        vBars[x + 1].setPosition((x+1) * widthBlock, screenHeight); 

                        // set red color for the moving block
                        vBars[x+1].setFillColor(sf::Color::Red);

                        // draw all of the items in vBars vector
                        for (int i = 0; i < vBars.size(); i++)
                        {
                            window.draw(vBars[i]);
                        }
                        window.display();                             // display the drawings to screen
                        vBars[x+1].setFillColor(sf::Color::Green);    // change the color back to green
                    }
                }
            }
        }
    }

    return 0;
}

int RandomGen(int iMin, int iMax)
{
    std::random_device rd;								// non-deterministic generator
    std::mt19937 gen(rd());								// to seed mersenne twister.
    std::uniform_int_distribution<> dist(iMin, iMax);	// distribute results inside center rect

    return dist(gen);								    // return random # between iMin and iMax
}


void CreateBars() {
    for (int i = 0; i < amountOfBlocks; i++)
    {
        float blockHeight = -1*(float(RandomGen(1, screenHeight)));                         // create random block height and set it to a negative number

        RectangleShape block(Vector2f(float(screenWidth / amountOfBlocks), (blockHeight))); // create a block

        block.setPosition(float(i * (screenWidth / amountOfBlocks)), screenHeight);         // set position of the block based on the i varible and using screenHeight
        block.setFillColor(sf::Color::Green);                                               // default Green color

        vBars.push_back(block);                                                             // push back bars into vector list
    }
}