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
#include <json.h>
#include "MovieTree.h"

using namespace std;

int main(int argc, char** argv) {

    // Opens the file from the command line argument
    string input_filename = argv[1];
    ifstream input_file;
    input_file.open(input_filename);
    if (!input_file.is_open()) {
        cout << "Input File not found." << endl;
        return 0;
    }
    
    string output_filename = argv[2];
    ofstream output_file;
    output_file.open(output_filename);
    if (!output_file.is_open()) {
        cout << "Output File not found." << endl;
        return 0;
    }
    

    int ranking;
    string title;
    int year;
    int quantity;

    MovieTree *tree = new MovieTree();

    string wanted_movie;
    string movie_to_rent;
    string movie_to_delete;
    
    string line;
    string element;
    while(getline(input_file, line)) {
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
    input_file.close();

    string user_command;

    while (true) {
        cout << "======Main Menu=====" << endl;
        cout << "1. Rent a movie" << endl;
        cout << "2. Print the inventory" << endl;
        cout << "3. Delete movie" << endl;
        cout << "4. Count movies" << endl;
        cout << "5. Quit" << endl;
        getline(cin, user_command);

        switch (stoi(user_command)) {
            case 1:
            {
                cout << "Enter title:" << endl;
                getline(cin, movie_to_rent);
                tree->rentMovie(movie_to_rent);
                break;
            }
            case 2:
            {
                tree->printMovieInventory();
                break;
            }
            case 3:
            {
                cout << "Enter title" << endl;
                getline(cin, movie_to_delete);
                tree->deleteMovieNode(movie_to_delete);
                break;
            }
            case 4:
            {
                tree->countMovieNodes();
                break;
            }
            case 5:
            {
                json_object *jObject = tree->getJsonObject();
                output_file << json_object_to_json_string_ext(jObject, JSON_C_TO_STRING_PRETTY) << endl;
                cout << "Goodbye!" << endl;
                return 0;
            }
            default:
            {
                cout << "Pick a value from the above list" << endl;
            }
        }
    }
    output_file.close();
    return 0;
}

