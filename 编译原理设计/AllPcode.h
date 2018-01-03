#ifndef ALLPCODE_H
#define ALLPCODE_H
#include<iostream>
#include<string>
#include"PerPcode.h"
using namespace std;

class AllPcode{
	 /*
    *    ����ľ�����ʽ��
    *    FLA
    *    ���У�F�δ���α������
    *    L�δ�����ò���˵����Ĳ��ֵ
    *    A�δ���λ��������Ե�ַ��
    *    ��һ��˵����
    *    INT��Ϊ�����õĹ��̣����������̣�������ջS�п�������������ʱA��Ϊ�������ݵ�Ԫ���������������������ݣ���L�κ�Ϊ0��
    *    CAL�����ù��̣���ʱA��Ϊ�����ù��̵Ĺ����壨������֮ǰһ��ָ���Ŀ�����������ڵ�ַ��
    *    LIT���������͵�����ջS��ջ������ʱA��Ϊ����ֵ��
    *    LOD���������͵�����ջS��ջ������ʱA��Ϊ��������˵�����е����λ�á�
    *    STO��������ջS��ջ����������ĳ��������Ԫ�У�A��Ϊ��������˵�����е����λ�á�
    *    JMP��������ת�ƣ���ʱA��Ϊת���ַ��Ŀ����򣩡�
    *    JPC������ת�ƣ�������ջS��ջ���Ĳ���ֵΪ�٣�0��ʱ����ת��A����ָĿ������ַ������˳��ִ�С�
    *    OPR����ϵ���������㣬A��ָ���������㣬����A=2�����������㡰������A��12�����ϵ���㡰>���ȵȡ��������ȡ������ջS��ջ������ջ����
    *
    *    OPR 0 0	���̵��ý�����,���ص��õ㲢��ջ
    *    OPR 0 1	ջ��Ԫ��ȡ��
    *    OPR 0 2	��ջ����ջ����ӣ�������ջԪ�أ����ֵ��ջ
    *    OPR 0 3	��ջ����ȥջ����������ջԪ�أ����ֵ��ջ
    *    OPR 0 4	��ջ������ջ����������ջԪ�أ����ֵ��ջ
    *    OPR 0 5	��ջ������ջ����������ջԪ�أ����ֵ��ջ
    *    OPR 0 6	ջ��Ԫ�ص���ż�жϣ����ֵ��ջ��
    *    OPR 0 7
    *    OPR 0 8	��ջ����ջ���Ƿ���ȣ�������ջԪ�أ����ֵ��ջ
    *    OPR 0 9	��ջ����ջ���Ƿ񲻵ȣ�������ջԪ�أ����ֵ��ջ
    *    OPR 0 10	��ջ���Ƿ�С��ջ����������ջԪ�أ����ֵ��ջ
    *    OPR 0 11	��ջ���Ƿ���ڵ���ջ����������ջԪ�أ����ֵ��ջ
    *    OPR 0 12	��ջ���Ƿ����ջ����������ջԪ�أ����ֵ��ջ
    *    OPR 0 13	��ջ���Ƿ�С�ڵ���ջ����������ջԪ�أ����ֵ��ջ
    *    OPR 0 14	ջ��ֵ�������Ļ
    *    OPR 0 15	��Ļ�������
    *    OPR 0 16	�������ж���һ����������ջ��
    */
	private:
     static const int LIT = 0;           //LIT 0 ��a ȡ����a��������ջջ��
     static const int OPR = 1;        //OPR 0 ��a ִ�����㣬a��ʾִ��ĳ�����㣬�����Ǻ�������������ע��
     static const int LOD = 2;        //LOD L ��a ȡ��������Ե�ַΪa�����ΪL���ŵ�����ջ��ջ��
     static const int STO = 3;        //STO L ��a ������ջջ�������ݴ����������Ե�ַΪa����β�ΪL��
     static const int CAL = 4;        //CAL L ��a ���ù��̣�ת��ָ�����ڵ�ַΪa����β�ΪL��
     static const int INT = 5;         //INT 0 ��a ����ջջ��ָ������a
     static const int JMP = 6;       //JMP 0 ��a������ת�Ƶ���ַΪa��ָ��
     static const int JPC = 7;        //JPC 0 ��a ����ת��ָ�ת�Ƶ���ַΪa��ָ��
     static const int RED = 8;       //RED L ��a �����ݲ������������Ե�ַΪa����β�ΪL��
     static const int WRT = 9;      //WRT 0 ��0 ��ջ���������

     int MAX_PCODE=10000;
     int codePtr=0;          //ָ����һ����Ҫ�����Ĵ������AllPcode�еĵ�ַ


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
