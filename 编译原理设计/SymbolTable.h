#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include<iostream>
#include<string>
#include"TableRow.h"
/**
 * Created by 
 * ��δ�жϳ���Maxֵ�����Ĵ���
 * SymTable���ű�ÿһ�еľ��庬���TableRow
 */
class SymbolTable {
	private:
    int rowMax=10000;           //����
    int valueMax=100000;        //����������ֵ
    int levelMax=3;                 //����Ƕ�ײ��
    int addressMax=10000;       //����ַ��
    int myconst=1;                  //����������1��ʾ
    int var=2;                      //����������2��ʾ
    int proc=3;             //����������3��ʾ

    //TableRow�Ƿ��ű��е�ÿһ��
    //tablePtrָ����ű����Ѿ�����ֵ���һ�����һ��
    //length��ʾ���ű������룻�˶��������ݣ�ʵ���Ͽ�����tablePtr����ʾ
    TableRow* table=new TableRow[rowMax];          //rowMax��

    int tablePtr=0;
    int length=0;

	public:
    void setTablePtr(int tablePtr) {
        this->tablePtr = tablePtr;
    }
    //��ʼ����ȫ��Ϊ0
    SymbolTable(){
        for(int i=0;i<rowMax;i++){
            //table[i]=new TableRow();
            table[i].setAddress(0);
            table[i].setLevel(0);
            table[i].setSize(0);
            table[i].setType(0);
            table[i].setValue(0);
            table[i].setName("");
        }
    }

    int getVar() {
        return var;
    }

    int getMyconst() {
        return myconst;
    }

    int getProc() {
        return proc;
    }

    int getLength(){
        return length;
    }

    //��ȡ���ű��е�i��
    TableRow getRow(int i){
        return table[i];
    }
    /*
      *��¼���������ű�
      * ������
      * name��������
      * level�����ڲ��
      * value��ֵ
      * address����������ڲ�λ���ַ�ĵ�ַ
    */
     void enterConst(string name,int level,int value,int address){
        table[tablePtr].setName(name);
        table[tablePtr].setLevel(level);
        table[tablePtr].setValue(value);
        table[tablePtr].setAddress(address);
        table[tablePtr].setType(myconst);
        table[tablePtr].setSize(4);
        tablePtr++;
        length++;
    }



    /*
     *    ��¼���������ű�
     *  ����ͬ��
     *  ˵�������ڵ�¼���ű���������ڱ�������������������������е��ã���PL/0��֧�ֱ�������ʱ��ֵ�����Բ��������value
     *
    */
     void enterVar(string name,int level,int address){
        table[tablePtr].setName(name);
        table[tablePtr].setLevel(level);
        table[tablePtr].setAddress(address);
        table[tablePtr].setType(var);
        table[tablePtr].setSize(0);
        tablePtr++;
        length++;
    }
    //��¼���̽����ű�����ͬ��
     void enterProc(string name,int level,int address){
        table[tablePtr].setName(name);
        table[tablePtr].setLevel(level);
        table[tablePtr].setAddress(address);
        table[tablePtr].setType(proc);
        table[tablePtr].setSize(0);
        tablePtr++;
        length++;
    }

    //��lev��֮ǰ������lev�㣬����Ϊname�ı�����������������Ƿ񱻶��壬
    //ʹ�ñ����������������ʱ���øú���
    bool isPreExistSTable(string name,int lev){
        for(int i=0;i<length;i++){
            if(table[i].getName().compare(name)==0 &&table[i].getLevel()<=lev){
                return true;
            }
        }
        return false;
    }

    //��lev�㣬����Ϊname�ı�����������������Ƿ񱻶��壬
    //��������������������ʱ���øú���
    bool isNowExistSTable(string name,int lev){
        for(int i=0;i<length;i++){
            if(table[i].getName().compare(name)==0 &&table[i].getLevel()==lev){
                return true;
            }
        }
        return false;
    }


    //���ط��ű�������Ϊname���е��к�
     int  getNameRow(string name){
        for(int i=length-1;i>=0;i--){
            if(table[i].getName().compare(name)==0){
                return i;
            }
        }
        return -1;          //����-1��ʾ�����ڸ�����
    }
     int getTablePtr() {
        return tablePtr;
    }

     TableRow* getAllTable(){
        return table;
    }

    //���ұ���Ĺ����ڷ��ű��е�λ��
     int getLevelPorc(int level){
        for(int i=length-1;i>=0;i--){
            if(table[i].getType()==proc){
                return i;
            }
        }
        return -1;
    }

};

#endif
