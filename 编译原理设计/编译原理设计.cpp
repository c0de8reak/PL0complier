// ����ԭ�����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	string filename;
	cout << ">Please input filename:" << endl;
	cout << ">>";
	cin >> filename;
	MpgAnalysis mp(filename);
	if (!mp.mgpAnalysis()){
		cout << ">compile succeed!" << endl;
		string choice;
		cout << ">Please input your choice:" << endl;
		cout << ">1.run now  " << "2.show PCode  " << "3.show Symbol Table" << endl;
		cout << ">>";
		cin >> choice;
		if (choice.compare("1") == 0) {
			cout << "running..." << endl;
			mp.interpreter();
		}
		else if (choice.compare("2") ==0){
			cout << "The following is PCode:" << endl;
			mp.showPcodeInStack();
		}
		else if (choice.compare("3") == 0){
			cout << "The following is Symbol Table:" << endl;
			mp.showtable();
		}
	}
}

