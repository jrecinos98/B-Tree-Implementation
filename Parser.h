#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include "Graph.h"
#include "B_Tree.h"

const std::string DELIMITER= ";";
const std::string separator= "________________________________________\n";
namespace Parse{
	class Parser{
		public:
			Parser();
 		    ~Parser();
  			void readFile();
  			void insertNewUser();
  			void printUserDetails();
       		void userExists();
       		void printTree(){userTree->printTree();}
       		void printGraph() const;
       		void recommendFriend();
       	private:
	  		//functions to build tree;
	  		int stringToInt(std::string s);
	  		void pushToQueue(Graph::Vertex* f);
	  		Person::User* createUser(std::string &userData, int location);
	  		Tree::BTree *userTree;
	  		Graph::List *friendList; 

	  		std::vector<int> marked;
	  		std::queue<int> pending;   
  };
}

#endif
