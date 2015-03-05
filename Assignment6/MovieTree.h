/* 
 * Assignment 5
 * Author: Sonia Szeton
 * Mentor: Derk Norton
 * Created on February 23, 2015, 3:43 PM
 */

#ifndef MOVIETREE_H
#define	MOVIETREE_H
#include <string>
#include <json.h>

struct MovieNode {
    int ranking;
    std::string title;
    int year;
    int quantity;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
    }

};

class MovieTree
{
    public:
        MovieTree();
        virtual ~MovieTree();
        void printMovieInventory();
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        void initJson();
        //use this to return the json object from the class when you are ready to write it to a file
        json_object* getJsonObject();
        
    protected:
    private:
        void deleteAll(MovieNode * node);
        void printMovieInventory(MovieNode * node);
        void insert(MovieNode *node, MovieNode *tree, json_object * traverseLog);
        MovieNode* deleteNode(MovieNode *node);
        MovieNode* searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog);
        int countMovieNodes(MovieNode *node);
        MovieNode *root;
        //including the json_object in the class makes it global within the class, much easier to work with
        json_object *Assignment6Output;
        int operation_counter;
};


#endif	/* MOVIETREE_H */

