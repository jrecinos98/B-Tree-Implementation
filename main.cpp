#include <iostream>
#include <fstream>
#include <climits>
#include "Parser.h"

using namespace std;

void cleanseStream(){
	std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

void printOperations(){
	std::cout<<"\n1) Read File.\n"
	     	 <<"2) Input a New User.\n"
	   		 <<"3) Find a User.\n"
	    	 <<"4) Find a User's Details.\n"
	    	 <<"5) Recommend Friends.\n"
	    	 <<"6) Exit Program.\n"
	    	 <<std::endl;
	std::cout<<"Which operation do you want to make?\n\n";
}

int main(int argc, char* arg[]){
	int input=-1;
	string separator= "________________________________________\n";
	Parse::Parser Reader;
	cout<<"\nHello! Welcome to the friend suggester:\n";
	while(input != 6){
		printOperations();
   		std::cin>> input;
   		while(input > 6 || input <= 0 || cin.fail()){
   			if(!cin) // or if(cin.fail())
				{
				   // user didn't input a number
				   cin.clear(); // reset failbit
				   cin.ignore(INT_MAX, '\n'); //skip bad input
				   // next, request user reinput
				}
	      cout<<"\nWRONG OPERATION! Please select only valid options:\n";
	      printOperations();
	      cin>> input;
	    }
	    switch(input){
	    	case 1:
	    	{	
				Reader.readFile();
				break;
	    	}
	    	case 2:
	    	{

	    		Reader.insertNewUser();
	    		cout<<separator;
	    		break;
	    	}
	    	case 3:
	    	{
	    		Reader.userExists();
	    		cout<<separator;
	    		break;

	    	}
	    	case 4:
	    	{
	    		Reader.printUserDetails();	    		
	    		cout<<separator;
	    		break;
	    	}
	    	case 5:
	    	{
	    		Reader.recommendFriend();
	    		cout<<separator;
	    		break;
	    	}

	    }
		
	}
  
}
