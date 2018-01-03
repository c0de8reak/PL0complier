#ifndef TABLEROW_H
#define TABLEROW_H
#include<iostream>
#include<string>
using namespace std;

class TableRow{
	private:
		int type;			//表示常量、变量或过程
		int value;			//表示常量或变量的值
		int level;			//嵌套层次，最大应为3，不在这里检查其是否小于等于，在SymbolTable中检查
		int address;		//相对于所在嵌套过程基地址的地址
		int size;			//表示常量，变量，过程所占的大小，实际上在本编译器中为了方便，统一设为4了,设置过程在SymTable中的三个enter函数中 
		string name;		//变量、常量或过程名
	public: 
	 int  getType(){
        return type;
    }

     int getValue(){
        return value;
    }

     int getLevel(){
        return level;
    }

     int getAddress(){
        return address;
    }

     int getSize(){
        return size;
    }

     string getName(){
        return name;
    }

     void setType(int t){
        type=t;
    }

     void setValue(int v){
        value=v;
    }

     void setLevel(int L){
        level=L;
    }

     void setAddress(int a){
        address=a;
    }

     void setSize(int s){
        size=s;
    }

     void setName(string s){
        name=s;
    } 
};

#endif 
