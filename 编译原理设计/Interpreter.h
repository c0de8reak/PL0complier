#pragma once
#include"stdafx.h"
using namespace std;

class Interpreter{
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
    *    OPR 0 14	ջ��ֵ�������Ļ,�������һ���ո�
    *    OPR 0 15	��Ļ�������
    *    OPR 0 16	�������ж���һ����������ջ��
    *
    private int LIT = 0;           //LIT 0 ��a ȡ����a��������ջջ��
    private int OPR = 1;        //OPR 0 ��a ִ�����㣬a��ʾִ��ĳ�����㣬�����Ǻ�������������ע��
    private int LOD = 2;        //LOD L ��a ȡ��������Ե�ַΪa�����ΪL���ŵ�����ջ��ջ��
    private int STO = 3;        //STO L ��a ������ջջ�������ݴ����������Ե�ַΪa����β�ΪL��
    private int CAL = 4;        //CAL L ��a ���ù��̣�ת��ָ�����ڵ�ַΪa����β�ΪL��
    private int INT = 5;         //INT 0 ��a ����ջջ��ָ������a
    private int JMP = 6;       //JMP 0 ��a������ת�Ƶ���ַΪa��ָ��
    private int JPC = 7;        //JPC 0 ��a ����ת��ָ�ת�Ƶ���ַΪa��ָ��
    private int RED = 8;       //RED L ��a �����ݲ������������Ե�ַΪa����β�ΪL��
    private int WRT = 9;      //WRT 0 ��0 ��ջ���������

?	������Ľṹ
�����洢�����洢��CODE���������P�Ĵ���
            ���ݴ洢��STACK��ջ��������̬�������ݿռ�
�ĸ��Ĵ�����
һ��ָ��Ĵ���I:��ŵ�ǰҪִ�еĴ���
һ��ջ��ָʾ���Ĵ���T��ָ������ջSTACK��ջ��
һ������ַ�Ĵ���B����ŵ�ǰ���й��̵���������STACK�е���ʼ��ַ
һ�������ַ�Ĵ���P�������һ��Ҫִ�е�ָ���ַ
�ü����û�й������õļĴ������������㶼Ҫ������ջSTACK��ջ��������Ԫ֮����У�����������ȡ��ԭ����������������������ջ��
?	���¼��
 RA
 SL
 DL

RA�����ص�ַ
SL������ù���ֱ�����Ļ��¼�׵�ַ
DL�������ߵĻ��¼�׵�ַ��
���̷��ؿ��Կ�����ִ��һ�������OPR����
ע�⣺��β�Ϊ���ò���붨���εĲ�ֵ

    */
	private:
     PerPcode IP;    //ָ��Ĵ���I����ŵ�ǰҪִ�еĴ���
     int T;      //ջ��ָʾ��T��ָ������ջSTACK��ջ��ջ�������Ԫ�أ�
     int B;      //��ַ�Ĵ���B����ŵ�ǰ���й��̵���������STACK�е���ʼ��ַ
     int P;      //�����ַ�Ĵ����������һ��Ҫִ�е�ָ��ĵ�ַ
     int stackSize=1000;
     int stack_increment=100;
     int max_stack_size=10000;
	 int *dataStack;     //���ݴ洢��STACK����ʼֵΪ1000
     AllPcode code;            //�洢��CODE���������P�Ĵ���
	public:
	Interpreter(){
			dataStack = new int[stackSize];
		}
     void setPcode(AllPcode code){    //��Pcode�еĴ���������ʼ��code
        this->code=code;
    }
     AllPcode getCode(){
        return code;
    }
     void interpreter(){
        P=0;
        B=0;
        T=0;
		dataStack[0] = dataStack[1] = dataStack[2] = 0;        //��������¼�еĶ�̬������̬�������ص�ַ��Ϊ0
        IP=code.getPcodeArray()[P];
        do{
            IP=code.getPcodeArray()[P];
            P++;
            switch(IP.getF()){
                case 0:
                    dataStack[T]=IP.getA();
                    T++;
                    break;
                case 1:
                    switch(IP.getA()){
                        case 0:                 //opr,0,0�˴�����
                            T=B;
                            P=dataStack[B+2];
                            B=dataStack[B];
							//if (T == 0)				//�����������ջʱ��ջ��Ϊ0��ʱ����ִ�н���
							//	return;
                            break;
                        case 1:                 //opr 0,1ȡ��ָ��
                            dataStack[T-1]=-dataStack[T-1];
                            break;
                        case 2:                 //opr0 ,2��ӣ���ԭ��������Ԫ����ȥ�����������ջ��
                            dataStack[T-2]=dataStack[T-1]+dataStack[T-2];
                            T--;
                            break;
                        case 3:
                            dataStack[T-2]=dataStack[T-2]-dataStack[T-1];
                            T--;
                            break;
                        case 4:
                            dataStack[T-2]=dataStack[T-1]*dataStack[T-2];
                            T--;
                            break;
                        case 5:
                            dataStack[T-2]=dataStack[T-2]/dataStack[T-1];
                            T--;
                            break;
                        case 6:
                            dataStack[T-1]=dataStack[T-1]%2;//(����Ϊ1)
                            break;
                        case 7:
                            break;
                        case 8:
                            if (dataStack[T - 1] == dataStack[T-2]){//�˴���ʹǰ�淢��ĳЩ������ΪJava�����ͺ�boolean���ǲ����Եȼ۵�
                                dataStack[T-2]=1;
                                T--;
                                break;
                            }
                            dataStack[T-2]=0;
                            T--;
                            break;
                        case 9:
                            if (dataStack[T - 1] != dataStack[T-2]){//�˴���ʹǰ�淢��ĳЩ������ΪJava�����ͺ�boolean���ǲ����Եȼ۵�
                                dataStack[T-2]=1;
                                T--;
                                break;
                            }
                            dataStack[T-2]=0;
                            T--;
                            break;
                        case 10:
                            if(dataStack[T-2]<dataStack[T-1]){
                                dataStack[T-2]=1;
                                T--;
                                break;
                            }
                            dataStack[T-2]=0;
                            T--;
                            break;
                        case 11:
                            if(dataStack[T-2]>=dataStack[T-1]){
                                dataStack[T-2]=1;
                                T--;
                                break;
                            }
                            dataStack[T-2]=0;
                            T--;
                            break;
                        case 12:
                            if(dataStack[T-2]>dataStack[T-1]){
                                dataStack[T-2]=1;
                                T--;
                                break;
                            }
                            dataStack[T-2]=0;
                            T--;
                            break;
                        case 13:
                            if(dataStack[T-2]<=dataStack[T-1]){
                                dataStack[T-2]=1;
                                T--;
                                break;
                            }
                            dataStack[T-2]=0;
                            T--;
                            break;
                        case 14:
                            cout << dataStack[T-1];
                            cout << "  ";     //���ڹ۲죬�����һ���ո�
                            break;
                        case 15:
                           cout << endl;
                            break;
                        case 16:
                            //Scanner s=new Scanner(System.in);
                            //dataStack[T]=s.nextInt();//�˴�����
							int temp;
							cin >> temp;
							dataStack[T] = temp;
                            T++;
                            break;
                    }
                    break;
                case 2:         //LOD L ��a ȡ��������Ե�ַΪa�����ΪL���ŵ�����ջ��ջ��
                    dataStack[T]=dataStack[IP.getA()+getBase(B,IP.getL())];
                    T++;
                    break;
                case 3://STO L ��a ������ջջ�������ݴ����������Ե�ַΪa����β�ΪL��
                    dataStack[IP.getA()+getBase(B,IP.getL())]=dataStack[T-1];
                    T--;
                    break;
                case 4: //CAL L ��a ���ù��̣�ת��ָ�����ڵ�ַΪa����β�ΪL��
                    dataStack[T]=B;
                    dataStack[T+1]=getBase(B,IP.getL());
                    dataStack[T+2]=P;
                    B=T;
                    P=IP.getA();
                    break;
                case 5:  //INT 0 ��a ����ջջ��ָ������a
                    T=T+IP.getA();
					if (code.getPcodeArray()[P - 2].getF() == code.getSTO())
					{
						for (int i = T - IP.getA(); i < T; i++)
						{
							dataStack[i] = dataStack[i + IP.getA() - 3];
						}
						B = B - IP.getA() + 3;
					}
                    break;
                case 6://JMP 0 ��a������ת�Ƶ���ַΪa��ָ��
                    P=IP.getA();
                    break;
                case 7: //JPC 0 ��a ����ת��ָ�ת�Ƶ���ַΪa��ָ��
                    if(dataStack[T-1]==0){
                        P=IP.getA();
                    }
					T--;
                    break;
            }
        }while(P!=0);

    }
	private:
		int getBase(int nowBp,int lev){
        int oldBp=nowBp;      //SL
        while(lev>0){
            oldBp=dataStack[oldBp+1];
            lev--;
        }
        return oldBp;
    }
};