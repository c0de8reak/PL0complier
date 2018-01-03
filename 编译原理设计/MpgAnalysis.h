#pragma once
#include"stdafx.h"
#include<iostream>
#include<string>
#define symnum 35
using namespace std;
class MpgAnalysis{
  private:
	 static  const int PROG = 1;//program
	 static  const int BEG = 2;//begin
	 static  const int END = 3;//end
	 static  const int IF = 4;//if
	 static  const int THEN = 5;//then
	 static  const int ELS = 6;//else
	 static  const int CON = 7;//const
	 static  const int PROC = 8;//procdure
	 static  const int VAR = 9;//var
	 static  const int DO = 10;//do
	 static  const int WHI = 11;//while
	 static  const int CAL = 12;//call
	 static  const int REA = 13;//read
	 static  const int WRI = 14;//write
	 static  const int REP = 15;//repeat
	 static  const int ODD = 16;//  odd      ��keyWord��ÿ���ֵ��������ȵ�

	 static  const int EQU = 17;//"="
	 static  const int LES = 18;//"<"
	 static  const int LESE = 19;//"<="
	 static  const int LARE = 20;//">="
	 static  const int LAR = 21;//">"
	 static  const int NEQE = 22;//"<>"


	 static  const int ADD = 23;//"+"
	 static  const int SUB = 24;//"-"
	 static  const int MUL = 25;//"*"
	 static  const int DIV = 26;//"/"

	 static  const int SYM = 27;//��ʶ��
	 static  const int CONST = 28;//������������number

	 static  const int CEQU = 29;//":="

	 static  const int COMMA = 30;//","
	 static  const int SEMIC = 31;//";"
	 static  const int POI = 32;//"."
	 static  const int LBR = 33;//"("
	 static  const int RBR = 34;//")"
	 bool declbegsys[symnum];		//��ʾ������ʼ�ķ��ż���
	 bool statbegsys[symnum];		//��ʾ��俪ʼ�ķ��ŵļ���
	 bool facbegsys[symnum];		//��ʾ���ӿ�ʼ�ķ��ż���
	LexAnalysis *lex;
	 bool errorHapphen = false;
	 int rvLength = 1000;
	 RValue* rv = new RValue[rvLength];   //
	 int terPtr = 0;       //RValue�ĵ�����
	 int levMax = 3;       //���Ƕ�����
	 SymbolTable STable;       //���ű�
	 AllPcode  Pcode ;                 //���Ŀ�����


	 int level = 0;                //������Ϊ��0��
	 int address = 0;             //������������������Ϊ0
	 int addrIncrement = 1;//TabelRow�е�address�����������������̵Ķ����¼�����ű������ʹ�����ӣ�����Ϊʲô

	public:
	 MpgAnalysis(string filename){
		 /* ���÷��ż� */

		 for (int i = 0; i<symnum; i++)
		 {
			 declbegsys[i] = false;
			 statbegsys[i] = false;
			 facbegsys[i] = false;
		 }

		 /* ����������ʼ���ż� */
		 declbegsys[CON] = true;
		 declbegsys[VAR] = true;
		 declbegsys[PROC] = true;

		 /* ������俪ʼ���ż� */
		 statbegsys[BEG] = true;
		 statbegsys[CAL] = true;
		 statbegsys[IF] = true;
		 statbegsys[WHI] = true;
		 statbegsys[SYM] = true;
		 statbegsys[WRI] = true;
		 statbegsys[REA] = true;
		 /* �������ӿ�ʼ���ż� */
		 facbegsys[SYM] = true;
		 facbegsys[CONST] = true;		//����
		 facbegsys[LBR] = true;
		for (int i = 0; i<rvLength; i++){
			rv[i].setId(-2);
			rv[i].setValue("-2");
		}
		lex = new LexAnalysis(filename);
	}
	 /*
	 ������ʵ�ּ��ϵļ�������
	 */
	 int inset(int e, bool *s)
	 {
		 return s[e];
	 }
	 int addset(bool* sr, bool* s1, bool* s2, int n)
	 {
		 int i;
		 for (i = 0; i<n; i++)
		 {
			 sr[i] = s1[i] || s2[i];
		 }
		 return 0;
	 }

	 int subset(bool* sr, bool* s1, bool* s2, int n)
	 {
		 int i;
		 for (i = 0; i<n; i++)
		 {
			 sr[i] = s1[i] && (!s2[i]);
		 }
		 return 0;
	 }

	 int mulset(bool* sr, bool* s1, bool* s2, int n)
	 {
		 int i;
		 for (i = 0; i<n; i++)
		 {
			 sr[i] = s1[i] && s2[i];
		 }
		 return 0;
	 }
	 /*
	 * ���Ե�ǰ�����Ƿ�Ϸ�
	 *
	 * ���﷨�����������ںͳ��ڴ����ò��Ժ���test��
	 * ��鵱ǰ���ʽ�����˳����﷨��λ�ĺϷ���
	 *
	 * s1:	��Ҫ�ĵ��ʼ���
	 * s2:	���������Ҫ�ĵ��ʣ���ĳһ����״̬ʱ��
	 *      �ɻָ��﷨�����������������Ĳ��䵥�ʷ��ż���
	 * n:  	�����
	 */
	 void test(bool* s1, bool* s2, int n)
	 {
		 if (!inset(rv[terPtr].getId(), s1))
		 {
			 showError(n,"");
			 /* ����ⲻͨ��ʱ����ͣ��ȡ���ţ�ֱ����������Ҫ�ļ��ϻ򲹾ȵļ��� */
			 while ((!inset(rv[terPtr].getId(), s1)) && (!inset(rv[terPtr].getId(), s2)))
			 {
				 terPtr++;
			 }
		 }
	 }
	 void readLex(){
		 int tempId, tempLine;
		 string tempValue;
		string filename = "lex.txt";
		fstream infile(filename.data(),ios::in);	
		if (!infile)
		{
			cout << "�ʷ��м��ļ���ʧ�ܣ�" << endl;
			exit(0);
		}
		int i = 0;
		while (infile.peek() != EOF){
			if (infile.fail())
			{
				break;
			}
			infile >> tempId >> tempValue >> tempLine;
			rv[i].setId(tempId);
			rv[i].setValue(tempValue);
			rv[i].setLine(tempLine);
			i++;
		}
	}

	 void prog(){
		bool nxtlev[symnum];
		if (rv[terPtr].getId() == PROG){
			terPtr++;
			if (rv[terPtr].getId() != SYM){
				errorHapphen = true;
				showError(1, "");
			}
			else{
				terPtr++;
				if (rv[terPtr].getId() != SEMIC){
					errorHapphen = true;
					showError(0, "");
					return;
				}
				else{
					terPtr++;
					memcpy(nxtlev, declbegsys, symnum);
					nxtlev[BEG] = true;
					block(nxtlev);
				}
			}
		}
		else {
			errorHapphen = true;
			showError(2, "");
			return;
		}
	}

	 void block(bool* fsys){
		 bool nxtlev[symnum];
		int addr0 = address;      //��¼����֮ǰ�����������Ա�ָ�ʱ����
		int tx0 = STable.getTablePtr();       //��¼�������ֵĳ�ʼλ��
		int cx0;
		int  propos = 0;
		if (tx0>0){
			propos = STable.getLevelPorc(level);
			tx0 = tx0 - STable.getRow(propos).getSize();   //��¼����������Ŀ�ʼλ��
		}
		if (tx0 == 0){
			address = 3;      //ÿһ���ʼλ�õ������ռ�������ž�̬��SL����̬��DL���ͷ��ص�ַRA
		}
		else{
			//ÿһ���ʼλ�õ������ռ�������ž�̬��SL����̬��DL���ͷ��ص�ַRA
			//�����ŷ��βεĸ���
			address = 3 + STable.getAllTable()[propos].getSize();


		}


		//�ݴ浱ǰPcode.codePtr��ֵ����jmp,0,0��codePtr�е�λ�ã�����һ�����
		int tempCodePtr = Pcode.getCodePtr();
		Pcode.gen(Pcode.getJMP(), 0, 0);
		if (level > levMax)   //�������ж�Ƕ�ײ����
		{
			showError(31, "");		//����Ƕ�����
		}
		do{
			if (rv[terPtr].getId() == CON){//�˴�û��terPtr++
				condecl();
			} if (rv[terPtr].getId() == VAR){
				vardecl();
			} if (rv[terPtr].getId() == PROC){
				memcpy(nxtlev, fsys, sizeof(bool)* symnum);
				//nxtlev[PROC] = true;
				//nxtlev[BEG] = true;
				//nxtlev[SEMIC] = true;
				proc(nxtlev);
				level--;
			}
			memcpy(nxtlev, fsys, sizeof(bool)* symnum);
			nxtlev[BEG] = true;
			test(nxtlev, declbegsys, 21);   //Ӧ������俪ʼ��begin
		} while (inset(rv[terPtr].getId(), declbegsys));
		/*
		* ����������ɣ�������䴦���֣�֮ǰ���ɵ�jmp��0��0Ӧ����ת�����λ��
		*
		* */
		//����jmp��0��0����ת��ַ
		if (tx0>0){
			for (int i = 0; i<STable.getAllTable()[propos].getSize(); i++){
				Pcode.gen(Pcode.getSTO(), 0, STable.getAllTable()[propos].getSize() + 3 - 1 - i);
			}
		}
		Pcode.getPcodeArray()[tempCodePtr].setA(Pcode.getCodePtr());
		Pcode.gen(Pcode.getINT(), 0, address);        //���ɷ����ڴ�Ĵ���
		if (tx0 == 0){
			// STable.getRow(tx0).setValue(Pcode.getCodePtr());     //���������ڷ��ű��е�ֵ��Ϊ������ִ����俪ʼ��λ��
		}
		else {
			STable.getAllTable()[propos].setValue(Pcode.getCodePtr() - 1 - STable.getAllTable()[propos].getSize());     //���������ڷ��ű��е�ֵ��Ϊ������ִ����俪ʼ��λ��

		}
		//body��̷���Ϊ�ֺŻ�end
		memcpy(nxtlev, fsys, sizeof(bool)* symnum);   //ÿ�����ÿ����̷��ż��϶������ϲ��̷��ż��ϣ��Ա㲹��
		nxtlev[SEMIC] = true;
		nxtlev[END] = true;
		body(nxtlev);
		Pcode.gen(Pcode.getOPR(), 0, 0);      //�����˳����̵Ĵ��룬������������ֱ���˳�����
		memset(nxtlev, 0, sizeof(bool)* symnum);    //blockû�в��ȼ���
		test(fsys, nxtlev, 22);    //���������ŵ���ȷ��
		address = addr0;      //�ֳ���������ָ����ֵ
		STable.setTablePtr(tx0);	
	}

	 void condecl(){          //const��level�����������
		if (rv[terPtr].getId() == CON){
			terPtr++;
			myconst();
			while (rv[terPtr].getId() == COMMA){
				terPtr++;
				myconst();
			}
			if (rv[terPtr].getId() != SEMIC){
				errorHapphen = true;
				showError(0, "");
				//return;
			}
			else{
				terPtr++;
			}
		}
		else{
			errorHapphen = true;
			showError(-1, "");
			//return;
		}
	}

	 void myconst(){
		string name;
		int value;
		if (rv[terPtr].getId() == SYM){
			name = rv[terPtr].getValue();
			terPtr++;
			if (rv[terPtr].getId() == CEQU){
				terPtr++;
				if (rv[terPtr].getId() == CONST){
					value = atoi(rv[terPtr].getValue().data());
					if (STable.isNowExistSTable(name, level)){
						errorHapphen = true;
						showError(15, name);
					}
					STable.enterConst(name, level, value, address);
					//                   address+=addrIncrement;             //��¼���ű���ַ��1ָ����һ��
					terPtr++;
				}
			}
			else{
				errorHapphen = true;
				showError(3, "");
				//return;
			}
		}
		else {
			errorHapphen = true;
			showError(1, "");
			//return;
		}
	}

	 void vardecl(){
		string name;
		int value;
		if (rv[terPtr].getId() == VAR){
			terPtr++;
			if (rv[terPtr].getId() == SYM){
				name = rv[terPtr].getValue();
				if (STable.isNowExistSTable(name, level)){
					errorHapphen = true;
					showError(15, name);
				}
				STable.enterVar(name, level, address);
				address += addrIncrement;
				terPtr++;
				while (rv[terPtr].getId() == COMMA){
					terPtr++;
					if (rv[terPtr].getId() == SYM){
						name = rv[terPtr].getValue();
						if (STable.isNowExistSTable(name, level)){
							errorHapphen = true;
							showError(15, name);
						}
						STable.enterVar(name, level, address);
						address += addrIncrement;     //��ַ��1��¼���ű�
						terPtr++;
					}
					else{
						errorHapphen = true;
						showError(1, "");
						//return;
					}
				}
				if (rv[terPtr].getId() != SEMIC){
					errorHapphen = true;
					showError(0, "");
					//return;
				}
				else{
					terPtr++;
				}
			}
			else {
				errorHapphen = true;
				showError(1, "");
				//return;
			}

		}
		else{
			errorHapphen = true;
			showError(-1, "");
			//return;
		}
	}

	/* void proc(bool* fsys){
		if (rv[terPtr].getId() == PROC){
			terPtr++;
			//id();
			int count = 0;//������¼proc���βεĸ���
			int propos;// ��¼��proc�ڷ��ű��е�λ��
			if (rv[terPtr].getId() == SYM){
				string name = rv[terPtr].getValue();
				if (STable.isNowExistSTable(name, level)){
					errorHapphen = true;
					showError(15, name);
				}
				propos = STable.getTablePtr();
				STable.enterProc(rv[terPtr].getValue(), level, address);
				level++;                //levelֵ��һ����Ϊ�������ж�����ڸ��µ�proc�����
				terPtr++;
				if (rv[terPtr].getId() == LBR){
					terPtr++;
					//id();
					if (rv[terPtr].getId() == SYM){
						STable.enterVar(rv[terPtr].getValue(), level, 3 + count);      //3+count+1Ϊ�β��ڴ洢�ռ��е�λ��
						count++;
						STable.getAllTable()[propos].setSize(count);        //�ñ������ڷ��ű��е�size���¼�βεĸ���
						terPtr++;
						while (rv[terPtr].getId() == COMMA){
							terPtr++;
							if (rv[terPtr].getId() == SYM){
								STable.enterVar(rv[terPtr].getValue(), level, 3 + count);      //3+count+1Ϊ�β��ڴ洢�ռ��е�λ��
								count++;
								STable.getAllTable()[propos].setSize(count);        //�ñ������ڷ��ű��е�size���¼�βεĸ���
								terPtr++;
							}
							else{
								errorHapphen = true;
								showError(1, "");
								//return;
							}
						}
					}
					if (rv[terPtr].getId() == RBR){
						terPtr++;
						if (rv[terPtr].getId() != SEMIC){
							errorHapphen = true;
							showError(0, "");
							//return;
						}
						else{
							terPtr++;
							bool nxtlev[symnum];
							memcpy(nxtlev, fsys, sizeof(bool)* symnum);
							nxtlev[SEMIC] = true;
							block(nxtlev);   //ע��ȡ������level�Ĵ���
							while (rv[terPtr].getId() == SEMIC){
								terPtr++;
								nxtlev[PROC] = true;
								test(nxtlev, fsys, 20);  //����˵����ķ��Ų���ȷ��ӦΪ����˵����
								proc(nxtlev);
							}
						}
					}
					else{
						errorHapphen = true;
						showError(5, "");
						//return;
					}

				}
				else{
					errorHapphen = true;
					showError(4, "");
					//return;
				}
			}
			else{
				errorHapphen = true;
				showError(1, "");
				//return;
			}

		}
		else{
			errorHapphen = true;
			showError(-1, "");
			//return;
		}
	}*/
	 void proc(bool* fsys)
	 {
		 while(rv[terPtr].getId() == PROC){
			 terPtr++;
			 //id();
			 int count = 0;//������¼proc���βεĸ���
			 int propos;// ��¼��proc�ڷ��ű��е�λ��
			 if (rv[terPtr].getId() == SYM){
				 string name = rv[terPtr].getValue();
				 if (STable.isNowExistSTable(name, level)){
					 errorHapphen = true;
					 showError(15, name);
				 }
				 propos = STable.getTablePtr();
				 STable.enterProc(rv[terPtr].getValue(), level, address);
				 level++;                //levelֵ��һ����Ϊ�������ж�����ڸ��µ�proc�����
				 terPtr++;
			 }
			 else{
				 errorHapphen = true;
				 showError(1, "");
				 //return;
			 }
			 if (rv[terPtr].getId() == LBR)
			 {
				 terPtr++;
				 //id();	 
			 }
			 else{
				 errorHapphen = true;
				 showError(4, "");
				 //return;
			 }
			 if (rv[terPtr].getId() == SYM){
				 STable.enterVar(rv[terPtr].getValue(), level, 3 + count);      //3+count+1Ϊ�β��ڴ洢�ռ��е�λ��
				 count++;
				 STable.getAllTable()[propos].setSize(count);        //�ñ������ڷ��ű��е�size���¼�βεĸ���
				 terPtr++;
				 while (rv[terPtr].getId() == COMMA){
					 terPtr++;
					 if (rv[terPtr].getId() == SYM){
						 STable.enterVar(rv[terPtr].getValue(), level, 3 + count);      //3+count+1Ϊ�β��ڴ洢�ռ��е�λ��
						 count++;
						 STable.getAllTable()[propos].setSize(count);        //�ñ������ڷ��ű��е�size���¼�βεĸ���
						 terPtr++;
					 }
					 else{
						 errorHapphen = true;
						 showError(1, "");
						 //return;
					 }
				 }
			 }
			 if (rv[terPtr].getId() == RBR){
				 terPtr++;
				 }
			 else
			 {
				 errorHapphen = true;
				 showError(5, "");
				 //return;
			 }
			 if (rv[terPtr].getId() != SEMIC){
				 errorHapphen = true;
				 showError(0, "");
				 //return;
			 }
			 else
			 {
				 terPtr++;
			 }
			 bool nxtlev[symnum];
			 memcpy(nxtlev, fsys, sizeof(bool)* symnum);
			 nxtlev[SEMIC] = true;
			 block(nxtlev);   //ע��ȡ������level�Ĵ���
			 if (rv[terPtr].getId() == SEMIC){
				 terPtr++;
				 nxtlev[PROC] = true;
				 //nxtlev[BEG] = true;
				 test(nxtlev, fsys, 20);  //����˵����ķ��Ų���ȷ��ӦΪ����˵����
				 //proc(nxtlev);
			 }
		 }	 
	 }
	 void body(bool* fsys){
		 bool nxtlev[symnum];
		if (rv[terPtr].getId() == BEG){
			terPtr++;
			memcpy(nxtlev, fsys, sizeof(bool)*symnum);
			nxtlev[SEMIC] = true;
			nxtlev[END] = true;
			statement(nxtlev);
			while (rv[terPtr].getId() == SEMIC){
				terPtr++;
				statement(nxtlev);
			}
			if (rv[terPtr].getId() == END){
				terPtr++;
			}
			else{
				errorHapphen = true;
				showError(7, "");
				//return;
			}
		}
		else{
			errorHapphen = true;
			showError(6, "");
			//return;
		}
	}

	 void statement(bool* fsys){
		 bool nxtlev[symnum];
		if (rv[terPtr].getId() == IF){
			int cx1;
			memcpy(nxtlev, fsys, sizeof(bool)*symnum);
			nxtlev[THEN] = true;
			nxtlev[DO] = true;
			terPtr++;
			lexp(nxtlev);
			if (rv[terPtr].getId() == THEN){
				terPtr++;
	
			}
			else{
				errorHapphen = true;
				showError(8, "");
				//return;
			}
			cx1 = Pcode.getCodePtr();             //��cx1��¼jpc ��0��0������������һ����������Ŀ����룩��Pcode�еĵ�ַ������һ�����
			Pcode.gen(Pcode.getJPC(), 0, 0);  //��������ת��ָ�������boolֵΪ0ʱ��ת����ת��Ŀ�ĵ�ַ��ʱ��Ϊ0
			statement(fsys);
			Pcode.getPcodeArray()[cx1].setA(Pcode.getCodePtr());        //��ַ�����jpc��0��0�е�A����
			//Pcode.getPcodeArray()[cx2].setA(Pcode.getCodePtr());
			if (rv[terPtr].getId() == ELS){
				//Pcode.getPcodeArray()[cx1].setA(Pcode.getCodePtr());
				int cx2 = Pcode.getCodePtr();
				Pcode.gen(Pcode.getJMP(), 0, 0);
				terPtr++;
				statement(fsys);
				Pcode.getPcodeArray()[cx2].setA(Pcode.getCodePtr());
			}//û�ˣ�
		}
		else if (rv[terPtr].getId() == WHI){
			int cx1 = Pcode.getCodePtr();     //�����������ʽ��Pcode�еĵ�ַ
			terPtr++;
			memcpy(nxtlev, fsys, sizeof(bool)*symnum);
			nxtlev[DO] = true;
			lexp(nxtlev);
			int cx2 = Pcode.getCodePtr();     //����������תָ��ĵ�ַ���ڻ���ʱʹ�ã�������������������ת
			Pcode.gen(Pcode.getJPC(), 0, 0);
			if (rv[terPtr].getId() == DO){
				terPtr++;
				//statement();
			}
			else{
				errorHapphen = true;
				showError(9, "");
				//return;
			}
			statement(fsys);  //ѭ����
			Pcode.gen(Pcode.getJMP(), 0, cx1);    //���DO������������Ҫ��ת���������ʽ��������Ƿ�������������Ƿ����ѭ��
			Pcode.getPcodeArray()[cx2].setA(Pcode.getCodePtr());        //��������ת��ָ��
		}
		else if (rv[terPtr].getId() == CAL){
			terPtr++;
			//id();
			int count = 0;//�������鴫��Ĳ������趨�Ĳ����Ƿ����
			TableRow tempRow;
			if (rv[terPtr].getId() == SYM){
				if (STable.isPreExistSTable(rv[terPtr].getValue(), level)){        //���ű��д��ڸñ�ʶ��
					tempRow = STable.getRow(STable.getNameRow(rv[terPtr].getValue()));  //��ȡ�ñ�ʶ�������е�������Ϣ��������tempRow��
					if (tempRow.getType() == STable.getProc()) { //�жϸñ�ʶ�������Ƿ�Ϊprocedure��SymTable��procdure������proc��������ʾ��
						;
					}       //if����Ϊproc
					else{       //cal���Ͳ�һ�µĴ���
						errorHapphen = true;
						showError(11, "");
						//return;
					}
				}       //if���ű��д��ڱ�ʶ��
				else{           //cal δ��������Ĵ���
					errorHapphen = true;
					showError(10, "");
					//return;
				}
				terPtr++;
				if (rv[terPtr].getId() == LBR){
					terPtr++;
					if (rv[terPtr].getId() == RBR){
						terPtr++;
						Pcode.gen(Pcode.getCAL(), level - tempRow.getLevel(), tempRow.getValue());        //���ù����еı����ֳ��ɽ��ͳ�����ɣ�����ֻ����Ŀ�����,+3����ϸ˵��
					}
					else{
						memcpy(nxtlev, fsys, sizeof(bool)*symnum);
						//nxtlev[ADD] = true;
						//nxtlev[SUB] = true;
						nxtlev[COMMA] = true;
						nxtlev[RBR] = true;
						exp(nxtlev);
						count++;
						while (rv[terPtr].getId() == COMMA){
							terPtr++;
							exp(nxtlev);
							count++;
						}
						if (count != tempRow.getSize()){
							errorHapphen = true;
							showError(16, tempRow.getName());
							//return;
							//terPtr++;
						}
						Pcode.gen(Pcode.getCAL(), level - tempRow.getLevel(), tempRow.getValue());        //���ù����еı����ֳ��ɽ��ͳ�����ɣ�����ֻ����Ŀ�����,+3����ϸ˵��
						if (rv[terPtr].getId() == RBR){
							terPtr++;
						}
						else{
							errorHapphen = true;
							showError(5, "");
							//return;
							//terPtr++;
						}
					}
				}
				else{
					errorHapphen = true;
					showError(4, "");
					//return;
				}
			}
			else{
				errorHapphen = true;
				showError(1, "");
				//return;
			}

		}
		else if (rv[terPtr].getId() == REA){
			terPtr++;
			if (rv[terPtr].getId() == LBR)
			{
				terPtr++;
				//      id();
				if (rv[terPtr].getId() == SYM){
					if (!STable.isPreExistSTable((rv[terPtr].getValue()), level)){      //�����ж��ڷ��ű����ڱ���򱾲�֮ǰ�Ƿ��д˱���
						errorHapphen = true;
						showError(10, "");
						//return;

					}//if�ж��ڷ��ű����Ƿ��д˱���
					else{           //stoδ��������Ĵ���
						TableRow tempTable = STable.getRow(STable.getNameRow(rv[terPtr].getValue()));
						if (tempTable.getType() == STable.getVar()){       //�ñ�ʶ���Ƿ�Ϊ��������
							Pcode.gen(Pcode.getOPR(), 0, 16);         //OPR 0 16	�������ж���һ����������ջ��   //���ĺ������ڣ���ֱ����Ƕ�׵Ĳ������Ϊ������������
							Pcode.gen(Pcode.getSTO(), level - tempTable.getLevel(), tempTable.getAddress());  //STO L ��a ������ջջ�������ݴ����������Ե�ַΪa����β�ΪL��
						}//if��ʶ���Ƿ�Ϊ��������
						else{       //sto���Ͳ�һ�µĴ���
							errorHapphen = true;
							showError(12, "");
							//return;
						}
					}
					terPtr++;
					while (rv[terPtr].getId() == COMMA)
					{
						terPtr++;
						if (rv[terPtr].getId() == SYM)
						{
							if (!STable.isPreExistSTable((rv[terPtr].getValue()), level))
							{      //�����ж��ڷ��ű����Ƿ��д˱���
								errorHapphen = true;
								showError(10, "");
								//return;

							}//if�ж��ڷ��ű����Ƿ��д˱���
							else{           //stoδ��������Ĵ���
								TableRow tempTable = STable.getRow(STable.getNameRow(rv[terPtr].getValue()));
								if (tempTable.getType() == STable.getVar()){       //�ñ�ʶ���Ƿ�Ϊ��������
									Pcode.gen(Pcode.getOPR(), 0, 16);         //OPR 0 16	�������ж���һ����������ջ��   //���ĺ������ڣ���ֱ����Ƕ�׵Ĳ������Ϊ������������
									Pcode.gen(Pcode.getSTO(), level - tempTable.getLevel(), tempTable.getAddress());  //STO L ��a ������ջջ�������ݴ����������Ե�ַΪa����β�ΪL��
								}//if��ʶ���Ƿ�Ϊ��������
								else{       //sto���Ͳ�һ�µĴ���
									errorHapphen = true;
									showError(12, "");
									//return;
								}
							}
							terPtr++;
						}
						else{
							errorHapphen = true;
							showError(1, "");
							//return;
							terPtr++;
						}
					}
					
				}
				else{
					errorHapphen = true;
					showError(26, "");
				}
			}
			else{
				errorHapphen = true;
				showError(4, "");
				//return;
			}
			if (rv[terPtr].getId() == RBR){
				terPtr++;
			}
			else{
				errorHapphen = true;
				showError(5, "");
				while (!inset(rv[terPtr].getId(), fsys))
				{
					terPtr++;
				}
			}
		}
		else if (rv[terPtr].getId() == WRI){
			terPtr++;
			if (rv[terPtr].getId() == LBR){
				terPtr++;
				memcpy(nxtlev, fsys, sizeof(bool)*symnum);
				//nxtlev[ADD] = true;
				//nxtlev[SUB] = true;
				nxtlev[COMMA] = true;
				nxtlev[RBR] = true;
				exp(nxtlev);
				Pcode.gen(Pcode.getOPR(), 0, 14);         //���ջ����ֵ����Ļ
				while (rv[terPtr].getId() == COMMA){
					terPtr++;
					exp(nxtlev);
					Pcode.gen(Pcode.getOPR(), 0, 14);         //���ջ����ֵ����Ļ
				}

				Pcode.gen(Pcode.getOPR(), 0, 15);         //�������
				if (rv[terPtr].getId() == RBR){
					terPtr++;
				}
				else{
					errorHapphen = true;
					showError(5, "");
					//return;
					terPtr++;
				}
			}
			else{
				errorHapphen = true;
				showError(4, "");
				//return;
			}
		}
		else if (rv[terPtr].getId() == BEG){//����Ҳû��terPtr++;          //body������Ŀ�����
			memcpy(nxtlev, fsys, sizeof(bool)*symnum);
			nxtlev[SEMIC] = true;
			nxtlev[END] = true;
			body(nxtlev);
		}
		else if (rv[terPtr].getId() == SYM){      //��ֵ���
			string name = rv[terPtr].getValue();
			terPtr++;
			if (rv[terPtr].getId() == CEQU){
				terPtr++;
				memcpy(nxtlev, fsys, sizeof(bool)*symnum);
				//nxtlev[ADD] = true;
				//nxtlev[SUB] = true;
				exp(nxtlev);
				if (!STable.isPreExistSTable(name, level)){        //����ʶ���Ƿ��ڷ��ű��д���
					errorHapphen = true;
					showError(14, name);
					//return;
				}//if�ж��ڷ��ű����Ƿ��д˱���
				else{           //stoδ��������Ĵ���
					TableRow tempTable = STable.getRow(STable.getNameRow(name));
					if (tempTable.getType() == STable.getVar()){           //����ʶ���Ƿ�Ϊ��������
						Pcode.gen(Pcode.getSTO(), level - tempTable.getLevel(), tempTable.getAddress());  //STO L ��a ������ջջ�������ݴ������
					}////����ʶ���Ƿ�Ϊ��������
					else{       //���Ͳ�һ�µĴ���
						errorHapphen = true;
						showError(13, name);
						//return;
					}
				}
			}
			else{
				errorHapphen = true;
				showError(3, "");
				//return;
			}
		}
		else{
			errorHapphen = true;
			showError(1, "");
			//return;
		}
	}

	 void lexp(bool* fsys){
		 bool nxtlev[symnum];
		if (rv[terPtr].getId() == ODD){
			terPtr++;
			exp(fsys);
			Pcode.gen(Pcode.getOPR(), 0, 6);  //OPR 0 6	ջ��Ԫ�ص���ż�жϣ����ֵ��ջ��
		}
		else{
			memcpy(nxtlev, fsys, sizeof(bool)* symnum);
			nxtlev[EQU] = true;
			nxtlev[LES] = true;
			nxtlev[LESE] = true;
			nxtlev[LARE] = true;
			nxtlev[LAR] = true;
			nxtlev[NEQE] = true;
			exp(nxtlev);
			int loperator = lop();        //����ֵ��������Ŀ����룬����
			if (loperator != -1)
			{
				exp(fsys);
				if (loperator == EQU){
					Pcode.gen(Pcode.getOPR(), 0, 8);      //OPR 0 8	��ջ����ջ���Ƿ���ȣ�������ջԪ�أ����ֵ��ջ
				}
				else if (loperator == NEQE){
					Pcode.gen(Pcode.getOPR(), 0, 9);      //OPR 0 9	��ջ����ջ���Ƿ񲻵ȣ�������ջԪ�أ����ֵ��ջ
				}
				else if (loperator == LES){
					Pcode.gen(Pcode.getOPR(), 0, 10);     //OPR 0 10	��ջ���Ƿ�С��ջ����������ջԪ�أ����ֵ��ջ
				}
				else if (loperator == LESE){
					Pcode.gen(Pcode.getOPR(), 0, 13);     // OPR 0 13	��ջ���Ƿ�С�ڵ���ջ����������ջԪ�أ����ֵ��ջ
				}
				else if (loperator == LAR){
					Pcode.gen(Pcode.getOPR(), 0, 12);     //OPR 0 12	��ջ���Ƿ����ջ����������ջԪ�أ����ֵ��ջ
				}
				else if (loperator == LARE){
					Pcode.gen(Pcode.getOPR(), 0, 11);     //OPR 0 11	��ջ���Ƿ���ڵ���ջ����������ջԪ�أ����ֵ��ջ
				}
			}
		}
	}

	 void exp(bool* fsys)
	 {
		 bool nxtlev[symnum];
		int tempId = rv[terPtr].getId();//���ڱ���������
		if (rv[terPtr].getId() == ADD){
			terPtr++;
		}
		else if (rv[terPtr].getId() == SUB){
			terPtr++;
		}
		memcpy(nxtlev, fsys, sizeof(bool)* symnum);
		nxtlev[ADD] = true;
		nxtlev[SUB] = true;
		term(nxtlev);
		if (tempId == SUB){
			Pcode.gen(Pcode.getOPR(), 0, 1);      //  OPR 0 1	ջ��Ԫ��ȡ��
		}
		while (rv[terPtr].getId() == ADD || rv[terPtr].getId() == SUB){
			tempId = rv[terPtr].getId();
			terPtr++;
			term(nxtlev);
			if (tempId == ADD){
				Pcode.gen(Pcode.getOPR(), 0, 2);       //OPR 0 2	��ջ����ջ����ӣ�������ջԪ�أ����ֵ��ջ
			}
			else if (tempId == SUB){
				Pcode.gen(Pcode.getOPR(), 0, 3);      //OPR 0 3	��ջ����ȥջ����������ջԪ�أ����ֵ��ջ
			}
		}
	}

	 void term(bool* fsys){
		bool nxtlev[symnum];
		memcpy(nxtlev, fsys, sizeof(bool)* symnum);
		nxtlev[MUL] = true;
		nxtlev[DIV] = true;
		factor(nxtlev);
		while (rv[terPtr].getId() == MUL || rv[terPtr].getId() == DIV){
			int tempId = rv[terPtr].getId();
			terPtr++;
			factor(nxtlev);
			if (tempId == MUL){
				Pcode.gen(Pcode.getOPR(), 0, 4);       //OPR 0 4	��ջ������ջ����������ջԪ�أ����ֵ��ջ
			}
			else if (tempId == DIV){
				Pcode.gen(Pcode.getOPR(), 0, 5);      // OPR 0 5	��ջ������ջ����������ջԪ�أ����ֵ��ջ
			}
		}
	}

	 void factor(bool* fsys){
		 bool nxtlev[symnum];
		 test(facbegsys, fsys, 24);   /*������ӵĿ�ʼ����*/
		 while (inset(rv[terPtr].getId(), facbegsys))
		 {

			 if (rv[terPtr].getId() == CONST){
				 Pcode.gen(Pcode.getLIT(), 0, atoi(rv[terPtr].getValue().data()));    //�Ǹ�����,  LIT 0 a ȡ����a��������ջջ��
				 terPtr++;
			 }
			 else if (rv[terPtr].getId() == LBR){
				 terPtr++;
				 memcpy(nxtlev, fsys, sizeof(bool)* symnum);
				 nxtlev[RBR] = true;
				 exp(nxtlev);
				 if (rv[terPtr].getId() == RBR){
					 terPtr++;
				 }
				 else{
					 errorHapphen = true;
					 showError(5, "");
				 }
			 }
			 else if (rv[terPtr].getId() == SYM){
				 string name = rv[terPtr].getValue();
				 if (!STable.isPreExistSTable(name, level)){     //�жϱ�ʶ���ڷ��ű����Ƿ����
					 errorHapphen = true;
					 showError(10, "");
					// return;
				 }//if�ж��ڷ��ű����Ƿ��д˱���
				 else{           //δ��������Ĵ���
					 TableRow tempRow = STable.getRow(STable.getNameRow(name));
					 if (tempRow.getType() == STable.getVar()){ //��ʶ���Ǳ�������
						 Pcode.gen(Pcode.getLOD(), level - tempRow.getLevel(), tempRow.getAddress());    //������LOD L  ȡ��������Ե�ַΪa�����ΪL���ŵ�����ջ��ջ��
					 }
					 else if (tempRow.getType() == STable.getMyconst()){
						 Pcode.gen(Pcode.getLIT(), 0, tempRow.getValue());         //������LIT 0 a ȡ����a��������ջջ��
					 }
					 else{       //���Ͳ�һ�µĴ���
						 errorHapphen = true;
						 showError(12, "");  //��ʶ������Ϊ����
						// return;
					 }
				 }
				 terPtr++;
			 }
			 /*else {
				 errorHapphen = true;
				 showError(1, "");
			 }*/
			 memset(nxtlev, 0, sizeof(bool)* symnum);
			 nxtlev[LBR] = true;
			 test(fsys, nxtlev, 23); /* һ�����Ӵ�����ϣ������ĵ���Ӧ��fsys������ */
			 /* ������ǣ������ҵ���һ�����ӵĿ�ʼ��ʹ�﷨�������Լ���������ȥ */
		 }
	}

	 int lop(){
		string loperator;
		if (rv[terPtr].getId() == EQU){
			terPtr++;
			return EQU;
		}
		else if (rv[terPtr].getId() == NEQE){
			terPtr++;
			return NEQE;
		}
		else if (rv[terPtr].getId() == LES){
			terPtr++;
			return LES;
		}
		else if (rv[terPtr].getId() == LESE){
			terPtr++;
			return LESE;
		}
		else if (rv[terPtr].getId() == LAR){
			terPtr++;
			return LAR;
		}
		else if (rv[terPtr].getId() == LARE){
			terPtr++;
			return LARE;
		}
		return -1;
	}

	//  void id(){

	//    }
	 bool mgpAnalysis(){
		lex->bAnalysis();
		readLex();
		prog();
		return errorHapphen;
	}

	 void showtable(){
		 cout << "type,name,level,address,value,size" << endl;
		for (int i = 0; i<STable.getLength(); i++){
			cout << STable.getRow(i).getType() << "  " << STable.getRow(i).getName() << "  " << STable.getRow(i).getLevel() << "  " << STable.getRow(i).getAddress() << "  " << STable.getRow(i).getValue() <<
				"  " << STable.getRow(i).getSize() << endl;
		}
	}

	 void showPcode(){
		for (int i = 0; i<Pcode.getCodePtr(); i++){
			switch (Pcode.getPcodeArray()[i].getF()){
			case 0:
				cout << "LIT  ";
				break;
			case 1:
				cout << "OPR  ";
				break;
			case 2:
				cout << "LOD  ";
				break;
			case 3:
				cout << "STO  ";
				break;
			case 4:
				cout << "CAL  ";
				break;
			case 5:
				cout << "INT  ";
				break;
			case 6:
				cout << "JMP  ";
				break;
			case 7:
				cout << "JPC  ";
				break;
			case 8:
				cout << "RED  ";
				break;
			case 9:
				cout << "WRI  ";
				break;
			}
			cout << Pcode.getPcodeArray()[i].getL() << "  " << Pcode.getPcodeArray()[i].getA() << endl;
		}
	}

	 void showPcodeInStack(){
		Interpreter inter ;
		inter.setPcode(Pcode);
		for (int i = 0; i<inter.getCode().getCodePtr(); i++){
			switch (inter.getCode().getPcodeArray()[i].getF()){
			case 0:
				cout << "LIT  ";
				break;
			case 1:
				cout << "OPR  ";
				break;
			case 2:
				cout << "LOD  ";
				break;
			case 3:
				cout << "STO  ";
				break;
			case 4:
				cout << "CAL  ";
				break;
			case 5:
				cout << "INT  ";
				break;
			case 6:
				cout << "JMP  ";
				break;
			case 7:
				cout << "JPC  ";
				break;
			case 8:
				cout << "RED  ";
				break;
			case 9:
				cout << "WRI  ";
				break;

			}
			cout << inter.getCode().getPcodeArray()[i].getL() << "  " << inter.getCode().getPcodeArray()[i].getA() << endl;
		}


	}

	 void showError(int i, string name){
		switch (i){
		case -1:
			cout << "ERROR " << i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "wrong token" << endl;        //�������岻��const��ͷ,�������岻��var ��ͷ
			break;
		case 0:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  (rv[terPtr].getLine() - 1) <<  ":";
			cout << "Missing semicolon" << endl;        //ȱ�ٷֺ�
			break;
		case 1:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Identifier illegal" << endl;       //��ʶ�����Ϸ�
			break;
		case 2:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "The beginning of program must be 'program'" << endl;       //����ʼ��һ���ַ�������program
			break;
		case 3:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Assign must be ':='" << endl;       //��ֵû�ã�=
			break;
		case 4:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing '('" << endl;       //ȱ��������
			break;
		case 5:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing ')'" << endl;       //ȱ��������
			break;
		case 6:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing 'begin'" << endl;       //ȱ��begin
			break;
		case 7:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing 'end'" << endl;       //ȱ��end
			break;
		case 8:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing 'then'" << endl;       //ȱ��then
			break;
		case 9:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing 'do'" << endl;       //ȱ��do
			break;
		case 10:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Not exist " << "'" << rv[terPtr].getValue() << "'" << endl;       //call��write��read����У������ڱ�ʶ��
			break;
		case 11:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "'" << rv[terPtr].getValue() << "'" << "is not a procedure" << endl;       //�ñ�ʶ������proc����
			break;
		case 12:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "'" << rv[terPtr].getValue() << "'" << "is not a variable" << endl;       //read��write����У��ñ�ʶ������var����
			break;
		case 13:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "'" << name << "'" << "is not a variable" << endl;       //��ֵ����У��ñ�ʶ������var����
			break;
		case 14:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Not exist" << "'" << name << "'" << endl;       //��ֵ����У��ñ�ʶ��������
			break;
		case 15:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Already exist" << "'" << name << "'" << endl;       //�ñ�ʶ���Ѿ�����
			break;
		case 16:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Number of parameters of procedure " << "'" << name << "'" << "is incorrect" << endl;       //�ñ�ʶ���Ѿ�����
			break;
		}

	}
	 void interpreter(){
		if (errorHapphen){
			return;
		}
		Interpreter inter;
		inter.setPcode(Pcode);
		inter.interpreter();
	}
};