#ifndef CHTABLE_H
#define CHTABLE_H
#include<string>
using namespace std;
class ChTable{
	private:
		string keyWord[16]; 
		int symLength=100;
		string *symTable;
		int conLength=100;
		string *constTable;
	public:
		ChTable(){
			string temp[16]={ "program", "begin", "end", "if", "then", "else", "const", "procedure",
				"var", "do", "while", "call", "read", "write", "repeat", "odd" };
			for (int i = 0; i < 16; i++)
			{
				keyWord[i] = temp[i];
			}
			symTable = new string[symLength];
			constTable = new string[conLength];
		}
		string* getKeyWord(){
			return keyWord;
		}
		string* getSymTable(){
			return symTable;
		}
		string* getConstTable(){
			return constTable;
		}	
		int getsymLength(){
			return symLength;
		}
		int getconstLength(){
			return conLength;
		}
}; 
#endif
