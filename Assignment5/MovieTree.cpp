/* MovieTree.cpp implements functions in the header file
 * Assignment 5
 * Sonia Szeton
 * Mentor: Derk Norton
 * 2/23/15
 */

#include "MovieTree.h"
#include <iostream>
using namespace std;

MovieTree::MovieTree() {
    root = NULL;
}

MovieTree::~MovieTree() {
    deleteAll(root);
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity) {
    MovieNode *new_node = new MovieNode;
    new_node->ranking = ranking;
    new_node->title = title;
    new_node->year = releaseYear;
    new_node->quantity = quantity;
    new_node->leftChild = NULL;
    new_node->rightChild = NULL;
    if(root != NULL) {
        insert(new_node, root);
    } else {
        root = new_node;
    }
    
}

void MovieTree::findMovie(string title) {
    MovieNode* found_movie = MovieTree::searchMovieTree(root, title);
    if (found_movie != NULL) {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << found_movie->ranking << endl;
        cout << "Title:" << found_movie->title << endl;
        cout << "Year:" << found_movie->year << endl;
        cout << "Quantity:" << found_movie->quantity << endl;
    } else {
        cout << "Movie not found." << endl;
    }
}

void MovieTree::deleteAll(MovieNode* node) {
    if (node != NULL) {
        deleteAll(node->leftChild);
        deleteAll(node->rightChild);
        delete node;
    }
}

void MovieTree::printMovieInventory() {
    printMovieInventory(root);
}

void MovieTree::printMovieInventory(MovieNode* node) {
    if (node != NULL) {
        printMovieInventory(node->leftChild);
        cout << "Movie: " << node->title << endl;
        printMovieInventory(node->rightChild);
    }
}

void MovieTree::rentMovie(string title) {
    MovieNode *wanted_movie = searchMovieTree(root, title);
    if (wanted_movie != NULL) {
        if (wanted_movie->quantity > 0) {
            cout << "Movie has been rented." << endl;
            wanted_movie->quantity--;
            findMovie(title);
        } else {
            cout << "Movie out of stock." << endl;
        }
    } else {
        cout << "Movie not found." << endl;
    }
}

MovieNode* MovieTree::searchMovieTree(MovieNode* node, string title) {
    if (node != NULL) {
        if (title == node->title)
            return node;
        if (title < node->title)
            return searchMovieTree(node->leftChild, title);
        else
            return searchMovieTree(node->rightChild, title);
    } else return NULL;
}

void MovieTree::insert(MovieNode *new_node, MovieNode *tree) {
    string title = new_node->title;
    if (title < tree->title) {
        if (tree->leftChild != NULL) {
            insert(new_node, tree->leftChild);
        } else {
            tree->leftChild = new_node;
        }
    } else if (title >= tree->title) {
        if (tree->rightChild != NULL) {
            insert(new_node, tree->rightChild);
        } else {
            tree->rightChild = new_node;
        }
    }
}