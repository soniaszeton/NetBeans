/* 
 * Assignment 5
 * Author: Sonia Szeton
 * Mentor: Derk Norton
 * Created on February 23, 2015, 3:03 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MovieTree.h"

using namespace std;

int main(int argc, char** argv) {

    // Opens the file from the command line argument
    string data_filename = argv[1];
    ifstream file;
    file.open(data_filename);
    if (!file.is_open()) {
        cout << "File not found." << endl;
        return 0;
    }
    int ranking;
    string title;
    int year;
    int quantity;

    MovieTree *tree = new MovieTree();

    string wanted_movie;
    string movie_to_rent;
    
    string line;
    string element;
    while(getline(file, line)) {
        stringstream lineStream(line);
        getline(lineStream,element,',');
        ranking = stoi(element);
        getline(lineStream, title, ',');
        getline(lineStream, element, ',');
        year = stoi(element);
        getline(lineStream, element);
        quantity = stoi(element);
        
        tree->addMovieNode(ranking, title, year, quantity);
               
    }
    file.close();

    string user_command;

    while (true) {
        cout << "======Main Menu=====" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Quit" << endl;
        getline(cin, user_command);

        switch (stoi(user_command)) {
            case 1:
            {
                cout << "Enter title:" << endl;
                getline(cin, wanted_movie);
                tree->findMovie(wanted_movie);
                break;
            }
            case 2:
            {
                cout << "Enter title:" << endl;
                getline(cin, movie_to_rent);
                tree->rentMovie(movie_to_rent);
                break;
            }
            case 3:
            {
                tree->printMovieInventory();
                break;
            }
            case 4:
            {
                cout << "Goodbye!" << endl;
                return 0;
            }
            default:
            {
                cout << "Pick a value from the above list" << endl;
            }
        }
    }

    return 0;
}

