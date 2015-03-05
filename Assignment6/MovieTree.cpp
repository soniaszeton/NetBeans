/* MovieTree.cpp implements functions in the header file
 * Assignment 5
 * Sonia Szeton
 * Mentor: Derk Norton
 * 2/23/15
 */

#include "MovieTree.h"
#include <iostream>
#include <string>
using namespace std;

MovieTree::MovieTree() {
    root = NULL;
    initJson();
}

MovieTree::~MovieTree() {
    deleteAll(root);
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity) {
    json_object *j_operation = json_object_new_object();
    json_object_object_add(Assignment6Output, to_string(operation_counter++).c_str(), j_operation);
    json_object *operation_name = json_object_new_string("add");
    json_object_object_add(j_operation, "operation", operation_name);
    json_object *operation_parameter = json_object_new_string(title.c_str());
    json_object_object_add(j_operation, "parameter", operation_parameter);
    json_object *operation_output = json_object_new_array();
    json_object_object_add(j_operation, "output", operation_output);
    MovieNode *new_node = new MovieNode;
    new_node->ranking = ranking;
    new_node->title = title;
    new_node->year = releaseYear;
    new_node->quantity = quantity;
    new_node->leftChild = NULL;
    new_node->rightChild = NULL;
    new_node->parent = NULL;
    if(root != NULL) {
        insert(new_node, root, operation_output);
    } else {
        root = new_node;
    }
    
}

void MovieTree::findMovie(string title) {
    MovieNode* found_movie = MovieTree::searchMovieTree(root, title, NULL);
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

void MovieTree::deleteAll(MovieNode* tree) {
    if (tree != NULL) {
        deleteAll(tree->leftChild);
        deleteAll(tree->rightChild);
        delete tree;
    }
}

void MovieTree::printMovieInventory() {
    printMovieInventory(root);
}

void MovieTree::printMovieInventory(MovieNode* tree) {
    if (tree != NULL) {
        printMovieInventory(tree->leftChild);
        cout << "Movie: " << tree->title << endl;
        printMovieInventory(tree->rightChild);
    }
}

void MovieTree::rentMovie(string title) {

    MovieNode *wanted_movie = searchMovieTree(root, title, NULL);
    if (wanted_movie != NULL) {
        if (wanted_movie->quantity > 0) {
            cout << "Movie has been rented." << endl;
            wanted_movie->quantity--;
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << wanted_movie->ranking << endl;
            cout << "Title:" << wanted_movie->title << endl;
            cout << "Year:" << wanted_movie->year << endl;
            cout << "Quantity:" << wanted_movie->quantity << endl;
             
        } else {
            cout << "Movie out of stock." << endl;
        }
    } else {
        cout << "Movie not found." << endl;
    }
    json_object *j_operation = json_object_new_object();
    json_object_object_add(Assignment6Output, to_string(operation_counter++).c_str(), j_operation);
    json_object *operation_name = json_object_new_string("rent");
    json_object_object_add(j_operation, "operation", operation_name);
    json_object *operation_parameter = json_object_new_string(title.c_str());
    json_object_object_add(j_operation, "parameter", operation_parameter);
    json_object *operation_output = json_object_new_int(wanted_movie->quantity);
    json_object_object_add(j_operation, "output", operation_output);
}

int MovieTree::countMovieNodes() {
    int num_movies = countMovieNodes(root);
    cout << num_movies << endl;
    json_object *j_operation = json_object_new_object();
    json_object_object_add(Assignment6Output, to_string(operation_counter++).c_str(), j_operation);
    json_object *operation_name = json_object_new_string("count");
    json_object_object_add(j_operation, "operation", operation_name);
    json_object *operation_output = json_object_new_int(num_movies);
    json_object_object_add(j_operation, "output", operation_output);
    return num_movies;
}

int MovieTree::countMovieNodes(MovieNode *tree) {
    int num_movies = 0;
    if (tree != NULL) {
        num_movies += countMovieNodes(tree->leftChild);
        num_movies += 1;
        num_movies += countMovieNodes(tree->rightChild);
    }
    return num_movies;
    
}

void MovieTree::initJson() {
    Assignment6Output = json_object_new_object();
    operation_counter = 1;
}

void MovieTree::deleteMovieNode(string title) {
    json_object *j_operation = json_object_new_object();
    json_object_object_add(Assignment6Output, to_string(operation_counter++).c_str(), j_operation);
    json_object *operation_name = json_object_new_string("delete");
    json_object_object_add(j_operation, "operation", operation_name);
    json_object *operation_parameter = json_object_new_string(title.c_str());
    json_object_object_add(j_operation, "parameter", operation_parameter);
    json_object *operation_output = json_object_new_array();
    json_object_object_add(j_operation, "output", operation_output);
    MovieNode* found_node = searchMovieTree(root, title, operation_output);
    root = deleteNode(found_node);
    
}

MovieNode* MovieTree::deleteNode(MovieNode *node) {
    if(node == NULL) {
        return root;
    }
    
}


json_object* MovieTree::getJsonObject() {
    return Assignment6Output;
}


MovieNode* MovieTree::searchMovieTree(MovieNode* tree, string title, json_object * traverseLog) {
    if (tree != NULL) {
        if(traverseLog != NULL) {
            json_object *j_title = json_object_new_string(tree->title.c_str());
            json_object_array_add(traverseLog, j_title);
        }
        if (title == tree->title)
            return tree;
        if (title < tree->title)
            return searchMovieTree(tree->leftChild, title, traverseLog);
        else
            return searchMovieTree(tree->rightChild, title, traverseLog);
    } else 
        return NULL;
}

void MovieTree::insert(MovieNode *new_node, MovieNode *tree, json_object * traverseLog) {
    string title = new_node->title;
    if(traverseLog != NULL) {
        json_object *j_title = json_object_new_string(tree->title.c_str());
        json_object_array_add(traverseLog, j_title);
    }
    if (title < tree->title) {
        if (tree->leftChild != NULL) {
            insert(new_node, tree->leftChild, traverseLog);
        } else {
            tree->leftChild = new_node;
            new_node->parent = tree;
        }
    } else if (title >= tree->title) {
        if (tree->rightChild != NULL) {
            insert(new_node, tree->rightChild, traverseLog);
        } else {
            tree->rightChild = new_node;
            new_node->parent = tree;
        }
    }
}