#ifndef RVALUE_H
#define RVALUE_H
#include<iostream>
#include<string>
using namespace std;

class RValue{
	private:
		int id;
		int line;
		string value;
	public:
		void setId(int _id){
			id = _id; 
		} 
		
		void setValue(string _value){
			value = _value;
		}
		
		void setLine(int _line){
			line = _line;
		}
		
		int getId(){
			return id;
		}
		
		int getLine(){
			return line;
		}
		
		string getValue(){
			return value;
		}
}; 

#endif
