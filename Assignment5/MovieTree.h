/* 
 * Assignment 5
 * Author: Sonia Szeton
 * Mentor: Derk Norton
 * Created on February 23, 2015, 3:43 PM
 */

#ifndef MOVIETREE_H
#define	MOVIETREE_H
#include <string>

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
    protected:
    private:
        void deleteAll(MovieNode * node);
        void printMovieInventory(MovieNode * node);
        void insert(MovieNode *node, MovieNode *tree);
        MovieNode* searchMovieTree(MovieNode * node, std::string title);
        MovieNode *root;
};


#endif	/* MOVIETREE_H */

