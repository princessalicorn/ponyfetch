//Peliminary Configurability for ponyfetch. You can change any value here and then re-compile the program
//If there are a limited number of options for a value, the potential options will be listed and explained here.

//Includes
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <fstream>

/*
Lines for the ascii art. You can put anything here.
Just keep and mind you need to put an escape charecter (\) before using a ".
Also make sure all lines have an equal width, or the labels will appear incorrectly.
*/
namespace ascii_lines
{
    std::string line1 = "         ,--, ";
    std::string line2 = "  _ ___/ /\\|  ";
    std::string line3 = " ;( )__, )    ";
    std::string line4 = "; //   \'--;   ";
    std::string line5 = "  \\     |     ";
    std::string line6 = "   ^    ^     ";
};

/*
Labels you will use for each of the 6 lines
Just keep and mind you need to put an escape charecter (\) before using a ".
*/
namespace labels
{
    std::string label1 = "Distro: ";
    std::string label2 = "Kernel: ";
    std::string label3 = "Shell: ";
    std::string label4 = "Uptime: ";
    std::string label5 = "Desktop: ";
    std::string label6 = "Terminal: ";
};
