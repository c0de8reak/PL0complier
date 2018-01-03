#ifndef TABLEROW_H
#define TABLEROW_H
#include<iostream>
#include<string>
using namespace std;

class TableRow{
	private:
		int type;			//��ʾ���������������
		int value;			//��ʾ�����������ֵ
		int level;			//Ƕ�ײ�Σ����ӦΪ3���������������Ƿ�С�ڵ��ڣ���SymbolTable�м��
		int address;		//���������Ƕ�׹��̻���ַ�ĵ�ַ
		int size;			//��ʾ������������������ռ�Ĵ�С��ʵ�����ڱ���������Ϊ�˷��㣬ͳһ��Ϊ4��,���ù�����SymTable�е�����enter������ 
		string name;		//�����������������
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
