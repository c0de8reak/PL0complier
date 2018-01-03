#ifndef ALLPCODE_H
#define ALLPCODE_H
#include<iostream>
#include<string>
#include"PerPcode.h"
using namespace std;

class AllPcode{
	 /*
    *    代码的具体形式：
    *    FLA
    *    其中：F段代表伪操作码
    *    L段代表调用层与说明层的层差值
    *    A段代表位移量（相对地址）
    *    进一步说明：
    *    INT：为被调用的过程（包括主过程）在运行栈S中开辟数据区，这时A段为所需数据单元个数（包括三个连接数据）；L段恒为0。
    *    CAL：调用过程，这时A段为被调用过程的过程体（过程体之前一条指令）在目标程序区的入口地址。
    *    LIT：将常量送到运行栈S的栈顶，这时A段为常量值。
    *    LOD：将变量送到运行栈S的栈顶，这时A段为变量所在说明层中的相对位置。
    *    STO：将运行栈S的栈顶内容送入某个变量单元中，A段为变量所在说明层中的相对位置。
    *    JMP：无条件转移，这时A段为转向地址（目标程序）。
    *    JPC：条件转移，当运行栈S的栈顶的布尔值为假（0）时，则转向A段所指目标程序地址；否则顺序执行。
    *    OPR：关系或算术运算，A段指明具体运算，例如A=2代表算术运算“＋”；A＝12代表关系运算“>”等等。运算对象取自运行栈S的栈顶及次栈顶。
    *
    *    OPR 0 0	过程调用结束后,返回调用点并退栈
    *    OPR 0 1	栈顶元素取反
    *    OPR 0 2	次栈顶与栈顶相加，退两个栈元素，结果值进栈
    *    OPR 0 3	次栈顶减去栈顶，退两个栈元素，结果值进栈
    *    OPR 0 4	次栈顶乘以栈顶，退两个栈元素，结果值进栈
    *    OPR 0 5	次栈顶除以栈顶，退两个栈元素，结果值进栈
    *    OPR 0 6	栈顶元素的奇偶判断，结果值在栈顶
    *    OPR 0 7
    *    OPR 0 8	次栈顶与栈顶是否相等，退两个栈元素，结果值进栈
    *    OPR 0 9	次栈顶与栈顶是否不等，退两个栈元素，结果值进栈
    *    OPR 0 10	次栈顶是否小于栈顶，退两个栈元素，结果值进栈
    *    OPR 0 11	次栈顶是否大于等于栈顶，退两个栈元素，结果值进栈
    *    OPR 0 12	次栈顶是否大于栈顶，退两个栈元素，结果值进栈
    *    OPR 0 13	次栈顶是否小于等于栈顶，退两个栈元素，结果值进栈
    *    OPR 0 14	栈顶值输出至屏幕
    *    OPR 0 15	屏幕输出换行
    *    OPR 0 16	从命令行读入一个输入置于栈顶
    */
	private:
     static const int LIT = 0;           //LIT 0 ，a 取常量a放入数据栈栈顶
     static const int OPR = 1;        //OPR 0 ，a 执行运算，a表示执行某种运算，具体是何种运算见上面的注释
     static const int LOD = 2;        //LOD L ，a 取变量（相对地址为a，层差为L）放到数据栈的栈顶
     static const int STO = 3;        //STO L ，a 将数据栈栈顶的内容存入变量（相对地址为a，层次差为L）
     static const int CAL = 4;        //CAL L ，a 调用过程（转子指令）（入口地址为a，层次差为L）
     static const int INT = 5;         //INT 0 ，a 数据栈栈顶指针增加a
     static const int JMP = 6;       //JMP 0 ，a无条件转移到地址为a的指令
     static const int JPC = 7;        //JPC 0 ，a 条件转移指令，转移到地址为a的指令
     static const int RED = 8;       //RED L ，a 读数据并存入变量（相对地址为a，层次差为L）
     static const int WRT = 9;      //WRT 0 ，0 将栈顶内容输出

     int MAX_PCODE=10000;
     int codePtr=0;          //指向下一条将要产生的代码的在AllPcode中的地址


     PerPcode* pcodeArray=new PerPcode[MAX_PCODE];
	public:
     AllPcode(){
        for(int i=0;i<MAX_PCODE;i++){
            pcodeArray[i]=PerPcode(-1,-1,-1);
        }
    }

     void gen(int f,int l,int a){
        pcodeArray[codePtr].setF(f);
        pcodeArray[codePtr].setL(l);
        pcodeArray[codePtr].setA(a);
        codePtr++;
    }

     int getCodePtr(){
        return codePtr;
    }

     int getOPR() {
        return OPR;
    }

     int getLIT() {
        return LIT;
    }

     int getLOD() {
        return LOD;
    }

     int getSTO() {
        return STO;
    }

     int getCAL() {
        return CAL;
    }

     int getINT() {
        return INT;
    }

     int getJMP() {
        return JMP;
    }

     int getJPC() {
        return JPC;
    }

     int getRED() {
        return RED;
    }

     int getWRT() {
        return WRT;
    }

     PerPcode* getPcodeArray() {
        return pcodeArray;
    }

};

#endif
