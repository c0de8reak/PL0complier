#ifndef PERPCODE_H
#define PERPCODE_H
#include<iostream>
#include<string>
using namespace std;

class PerPcode{
	private:
		int F;
		int L;
		int A;
	public:
		PerPcode(){}
		PerPcode(int f,int l,int a){
			F = f;
			L = l;
			A = a;
		}
		void setF(int f){
			F = f;
		}
		
		void setL(int l){
			L = l;
		}
		
		void setA(int a){
			A = a;
		}
		int getF(){
			return F;
		}
		int getL(){
			return L;
		}
		int getA(){
			return A;
		}
};

#endif
