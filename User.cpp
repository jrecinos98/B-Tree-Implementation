#include <iostream>
#include <string>
#include "User.h"

namespace Person{
	User::User(int perm_number, std::string name, std::string genre1, std::string genre2, int location){
		this->name=name;
		this->genre1= genre1;
		this->genre2=genre2;
		this->perm_number= perm_number;
		this->location= location;
	}
	User::~User(){

	}
	std::ostream& operator << (std::ostream& out, const User& u){
		out<<"\nUser: "<< u.getName()<<std::endl;
		out<<"Perm: "<<u.getPerm()<<std::endl;
		out<<"Genres: "<<u.getFirstGenre()<<" || " <<u.getSecondGenre()<<std::endl;
		return out;
	}
}
