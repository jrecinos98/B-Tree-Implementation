#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <queue>
#include <algorithm>
#include "Parser.h"
#include "User.h"
//#include "B_tree.h"
#include "Graph.h"

namespace Parse{
	Parser::Parser(){
		this->userTree= new Tree::BTree();
		this->friendList = new Graph::List();
	}
	Parser::~Parser(){

	}

	int Parser::stringToInt(std::string s){
		std::stringstream convert(s);
		int num=0;
		convert>>num;
		return num;

	}
	void cleanseInputStream(){
		std::cin.clear(); // reset failbit
		std::cin.ignore(INT_MAX, '\n'); //skip bad input
	}

	Person::User* Parser::createUser(std::string &userData, int location){
		//Perm is read as a string but we need int
		std::string permString= userData.substr(0, userData.find(DELIMITER));
		userData.erase(0, permString.length()+1);
		//convert string to an integer
		int perm= stringToInt(permString);
		std::string name= userData.substr(0,userData.find(DELIMITER));
		userData.erase(0,name.length()+1);
		std::string genre1= userData.substr(0,userData.find(DELIMITER));
		userData.erase(0,genre1.length()+1);
		std::string genre2= userData.substr(0,userData.find(DELIMITER));
		userData.erase(0,genre2.length()+1);
		Person::User* newUser= new Person::User(perm, name, genre1, genre2, location);
		return newUser;
	}

	void Parser::readFile(){
		std::ifstream infile;
		std::string filename;
		std::string userData;
		std::cout<<"\nEnter the name of the file:\n\n";
		std::cin>>filename;
		infile.open(filename.c_str());
		if(!infile){
			std::cout<<"\n----------------\nCAN'T OPEN FILE\n----------------\n";
			return;
		}
		size_t pos = 0;
		int friendPerm;
		Person::User *newUser;
		Graph::LinkList *userFriends; 
		//std::string pause="";
		while (std::getline (infile,userData) ){
			newUser= createUser(userData, friendList->getSize()); //Size because element hasn't been added yet
			userTree->insertUser(newUser);
			userFriends= new Graph::LinkList();
			userFriends->insert(newUser->getPerm());
			bool line_end= false;
			//Find friends
			while(!line_end){
				line_end=(pos = userData.find(DELIMITER)) == std::string::npos;
				friendPerm = stringToInt(userData.substr(0, pos));
				userFriends->insert(friendPerm);
				userData.erase(0,pos+1);				
				/*if(line_end){ 
					//The last friend is ignored since there is no DELIMITER at the end.
					userFriends->insert(stringToInt(userData));
				}*/
			}
			friendList->insertNew(userFriends);

		}
		cleanseInputStream();
		infile.close();
		std::cout<<separator<<"\nFILE READ SUCCESSFULLY.\n"<<separator;
		//std::cout<<*friendList;
	}


	void Parser::insertNewUser(){
		std::string name="";
		std::string permString="";
		std::string genre1="";
		std::string genre2="";
		std::string friendString="";
		Graph::LinkList *userFriends= new Graph::LinkList();

		std::cout<<"\nWhat is the user's perm number?\n\n";
		std::cin>>permString;
		cleanseInputStream();

		std::cout<<"\nWhat is the name of the user?\n\n";
		std::getline(std::cin, name);
		std::cout<<"\nInput the user's favorite movie genres:\n";
		std::cout<<"First favorite genre:\n\n";
		std::getline(std::cin,genre1);
		std::cout<<"Second favorite genre:\n\n";
		std::getline(std::cin,genre2);
		std::cout<<"\nEnter the perm number of the user's friends separated by a space:\n\n";
		std::getline (std::cin,friendString);
		//cleanseInputStream();

		//Create new User object here and push to tree

		Person::User *newUser= new Person::User(stringToInt(permString), name, genre1, genre2, friendList->getSize());
		userTree->insertUser(newUser);
		userFriends->insert(stringToInt(permString));
		std::stringstream ss(friendString);
		std::string friendPerm;
		std::vector<int> friendPerms;
		while(std::getline(ss, friendPerm, ' ')){
			int perm= stringToInt(friendPerm);
			userFriends->insert(perm);
			friendPerms.push_back(perm);
		}
		friendList->insertNew(userFriends);
		for(int i=0; i < friendPerms.size(); i++){
			Person::User* user= userTree->retrieveUser(friendPerms[i]);
			if(user != NULL){
				int index= user->getIndex();
				friendList->updateFriendList(index, stringToInt(permString));
			}
		}
		//std::cout<<*friendList;



	}

	void Parser::printUserDetails(){
		std::string perm;
		std::cout<<"\nWhat is the user's perm number?\n\n";
		std::cin>>perm;
		cleanseInputStream();
		Person::User* user= userTree->retrieveUser(stringToInt(perm));
		Graph::LinkList* friends; 

		if(user != NULL){
			friends= friendList->getFriends(user->getIndex());

			std::cout<<separator<<*user<<std::endl;
			std::cout<<user->getName()<<"'s friends: ";
			Graph::Vertex *temp= friends->getFirstFriend();
			while(temp != NULL){
				std::cout<<" "<<temp->getPerm();
				if(temp->getNext()!=NULL){
					std::cout<<" ->";
				}
				temp= temp->getNext();
			}
			std::cout<<std::endl;
		}
		else{
			std::cout<<separator<<"\nUSER NOT FOUND\n";
		}
	}

	void Parser::printGraph() const{
		std::cout<<*friendList<<std::endl;
	}

	void Parser::userExists(){
		std::cout<<"\nEnter the perm number of the person you are searching for:\n\n";
		int perm;
		std::cin>>perm;
		std::cout<<std::endl;
		//userTree->printTree();
		if(userTree->userExist(perm)){
			std::cout<<"USER EXISTS."<<std::endl;
		}
		else{
			std::cout<<separator<<"\nUSER DOES NOT EXIST."<<std::endl;
		}
		return;


	}
	void Parser::pushToQueue(Graph::Vertex *f){
		Graph::Vertex* temp=f;
		while(temp!=NULL){
			bool isMarked= std::find(marked.begin(), marked.end(),temp->getPerm()) != marked.end();
			if(!isMarked){
				pending.push(temp->getPerm());
			}
			temp= temp->getNext();
		

		}
		
	}
	void Parser::recommendFriend(){
		std::cout<<"\nEnter the perm number of a user to recommend friends: \n\n";
		int perm;
		std::cin>>perm;
		std::cout<<std::endl;
		cleanseInputStream();

		Person::User* user= userTree->retrieveUser(perm);
		if(user == NULL){
			std::cout<<separator<<"\nUSER NOT FOUND\n";
			return;
		}
		
		Graph::LinkList* friends= friendList->getFriends(user->getIndex());
		std::vector<Person::User*> recommended;

		//Mark the og user as visited
		marked.push_back(perm);

		//Push the user friends onto the queue
		pushToQueue(friends->getFirstFriend());
		
		while(!pending.empty()){
			int nextPerm= pending.front();

			pending.pop();

			//Mark friend as visited
			marked.push_back(nextPerm);
			Person::User* tempUser= userTree->retrieveUser(nextPerm);

			if (tempUser != NULL){
				Graph::LinkList* temp= friendList->getFriends(tempUser->getIndex());
				pushToQueue(temp->getFirstFriend());
				bool userFriend = friends->isFriend(nextPerm);

				if(!userFriend){
					bool firstGenre= (tempUser->getFirstGenre() == user->getFirstGenre() 
						 				|| tempUser->getSecondGenre()== user->getFirstGenre());

					bool secondGenre= (tempUser->getSecondGenre()== user->getSecondGenre() 
										|| tempUser->getFirstGenre() == user ->getSecondGenre());
					bool inList= std::find(recommended.begin(), recommended.end(), tempUser) == recommended.end();
					if( (firstGenre || secondGenre) && inList){

						recommended.push_back(tempUser);
					}
				}
			}

		}
		std::sort(recommended.begin(), recommended.end());
		std::cout<<"Recommended Friends:\n\n";
		for(int i =0; i < recommended.size(); i++){
			std::cout<<separator<<*recommended[i]<<std::endl;
		}
		marked.clear();


	}


	
  
}
