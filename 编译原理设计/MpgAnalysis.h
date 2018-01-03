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
	 static  const int ODD = 16;//  odd      和keyWord中每个字的序号是相等的

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

	 static  const int SYM = 27;//标识符
	 static  const int CONST = 28;//常量，即数字number

	 static  const int CEQU = 29;//":="

	 static  const int COMMA = 30;//","
	 static  const int SEMIC = 31;//";"
	 static  const int POI = 32;//"."
	 static  const int LBR = 33;//"("
	 static  const int RBR = 34;//")"
	 bool declbegsys[symnum];		//表示声明开始的符号集合
	 bool statbegsys[symnum];		//表示语句开始的符号的集合
	 bool facbegsys[symnum];		//表示因子开始的符号集合
	LexAnalysis *lex;
	 bool errorHapphen = false;
	 int rvLength = 1000;
	 RValue* rv = new RValue[rvLength];   //
	 int terPtr = 0;       //RValue的迭代器
	 int levMax = 3;       //最大嵌套深度
	 SymbolTable STable;       //符号表
	 AllPcode  Pcode ;                 //存放目标代码


	 int level = 0;                //主程序为第0层
	 int address = 0;             //主程序或变量的声明是为0
	 int addrIncrement = 1;//TabelRow中的address的增量，常量、过程的定义登录进符号表均不会使其增加，但是为什么

	public:
	 MpgAnalysis(string filename){
		 /* 设置符号集 */

		 for (int i = 0; i<symnum; i++)
		 {
			 declbegsys[i] = false;
			 statbegsys[i] = false;
			 facbegsys[i] = false;
		 }

		 /* 设置声明开始符号集 */
		 declbegsys[CON] = true;
		 declbegsys[VAR] = true;
		 declbegsys[PROC] = true;

		 /* 设置语句开始符号集 */
		 statbegsys[BEG] = true;
		 statbegsys[CAL] = true;
		 statbegsys[IF] = true;
		 statbegsys[WHI] = true;
		 statbegsys[SYM] = true;
		 statbegsys[WRI] = true;
		 statbegsys[REA] = true;
		 /* 设置因子开始符号集 */
		 facbegsys[SYM] = true;
		 facbegsys[CONST] = true;		//数字
		 facbegsys[LBR] = true;
		for (int i = 0; i<rvLength; i++){
			rv[i].setId(-2);
			rv[i].setValue("-2");
		}
		lex = new LexAnalysis(filename);
	}
	 /*
	 用数组实现集合的集合运算
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
	 * 测试当前符号是否合法
	 *
	 * 在语法分析程序的入口和出口处调用测试函数test，
	 * 检查当前单词进入和退出该语法单位的合法性
	 *
	 * s1:	需要的单词集合
	 * s2:	如果不是需要的单词，在某一出错状态时，
	 *      可恢复语法分析继续正常工作的补充单词符号集合
	 * n:  	错误号
	 */
	 void test(bool* s1, bool* s2, int n)
	 {
		 if (!inset(rv[terPtr].getId(), s1))
		 {
			 showError(n,"");
			 /* 当检测不通过时，不停获取符号，直到它属于需要的集合或补救的集合 */
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
			cout << "词法中间文件打开失败！" << endl;
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
		int addr0 = address;      //记录本层之前的数据量，以便恢复时返回
		int tx0 = STable.getTablePtr();       //记录本层名字的初始位置
		int cx0;
		int  propos = 0;
		if (tx0>0){
			propos = STable.getLevelPorc(level);
			tx0 = tx0 - STable.getRow(propos).getSize();   //记录本本层变量的开始位置
		}
		if (tx0 == 0){
			address = 3;      //每一层最开始位置的三个空间用来存放静态连SL、动态连DL、和返回地址RA
		}
		else{
			//每一层最开始位置的三个空间用来存放静态连SL、动态连DL、和返回地址RA
			//紧接着放形参的个数
			address = 3 + STable.getAllTable()[propos].getSize();


		}


		//暂存当前Pcode.codePtr的值，即jmp,0,0在codePtr中的位置，用来一会回填
		int tempCodePtr = Pcode.getCodePtr();
		Pcode.gen(Pcode.getJMP(), 0, 0);
		if (level > levMax)   //必须先判断嵌套层层数
		{
			showError(31, "");		//超过嵌套深度
		}
		do{
			if (rv[terPtr].getId() == CON){//此处没有terPtr++
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
			test(nxtlev, declbegsys, 21);   //应该是语句开始符begin
		} while (inset(rv[terPtr].getId(), declbegsys));
		/*
		* 声明部分完成，进入语句处理部分，之前生成的jmp，0，0应当跳转到这个位置
		*
		* */
		//回填jmp，0，0的跳转地址
		if (tx0>0){
			for (int i = 0; i<STable.getAllTable()[propos].getSize(); i++){
				Pcode.gen(Pcode.getSTO(), 0, STable.getAllTable()[propos].getSize() + 3 - 1 - i);
			}
		}
		Pcode.getPcodeArray()[tempCodePtr].setA(Pcode.getCodePtr());
		Pcode.gen(Pcode.getINT(), 0, address);        //生成分配内存的代码
		if (tx0 == 0){
			// STable.getRow(tx0).setValue(Pcode.getCodePtr());     //将本过程在符号表中的值设为本过程执行语句开始的位置
		}
		else {
			STable.getAllTable()[propos].setValue(Pcode.getCodePtr() - 1 - STable.getAllTable()[propos].getSize());     //将本过程在符号表中的值设为本过程执行语句开始的位置

		}
		//body后继符号为分号或end
		memcpy(nxtlev, fsys, sizeof(bool)* symnum);   //每个后继每个后继符号集合都包含上层后继符号集合，以便补救
		nxtlev[SEMIC] = true;
		nxtlev[END] = true;
		body(nxtlev);
		Pcode.gen(Pcode.getOPR(), 0, 0);      //生成退出过程的代码，若是主程序，则直接退出程序
		memset(nxtlev, 0, sizeof(bool)* symnum);    //block没有补救集合
		test(fsys, nxtlev, 22);    //检测后续符号的正确性
		address = addr0;      //分程序结束，恢复相关值
		STable.setTablePtr(tx0);	
	}

	 void condecl(){          //const的level是无意义的吗
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
					//                   address+=addrIncrement;             //登录符号表后地址加1指向下一个
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
						address += addrIncrement;     //地址加1登录符号表
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
			int count = 0;//用来记录proc中形参的个数
			int propos;// 记录本proc在符号表中的位置
			if (rv[terPtr].getId() == SYM){
				string name = rv[terPtr].getValue();
				if (STable.isNowExistSTable(name, level)){
					errorHapphen = true;
					showError(15, name);
				}
				propos = STable.getTablePtr();
				STable.enterProc(rv[terPtr].getValue(), level, address);
				level++;                //level值加一，因为其后的所有定义均在该新的proc中完成
				terPtr++;
				if (rv[terPtr].getId() == LBR){
					terPtr++;
					//id();
					if (rv[terPtr].getId() == SYM){
						STable.enterVar(rv[terPtr].getValue(), level, 3 + count);      //3+count+1为形参在存储空间中的位置
						count++;
						STable.getAllTable()[propos].setSize(count);        //用本过程在符号表中的size域记录形参的个数
						terPtr++;
						while (rv[terPtr].getId() == COMMA){
							terPtr++;
							if (rv[terPtr].getId() == SYM){
								STable.enterVar(rv[terPtr].getValue(), level, 3 + count);      //3+count+1为形参在存储空间中的位置
								count++;
								STable.getAllTable()[propos].setSize(count);        //用本过程在符号表中的size域记录形参的个数
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
							block(nxtlev);   //注意取消参数level的传递
							while (rv[terPtr].getId() == SEMIC){
								terPtr++;
								nxtlev[PROC] = true;
								test(nxtlev, fsys, 20);  //过程说明后的符号不正确，应为过程说明符
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
			 int count = 0;//用来记录proc中形参的个数
			 int propos;// 记录本proc在符号表中的位置
			 if (rv[terPtr].getId() == SYM){
				 string name = rv[terPtr].getValue();
				 if (STable.isNowExistSTable(name, level)){
					 errorHapphen = true;
					 showError(15, name);
				 }
				 propos = STable.getTablePtr();
				 STable.enterProc(rv[terPtr].getValue(), level, address);
				 level++;                //level值加一，因为其后的所有定义均在该新的proc中完成
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
				 STable.enterVar(rv[terPtr].getValue(), level, 3 + count);      //3+count+1为形参在存储空间中的位置
				 count++;
				 STable.getAllTable()[propos].setSize(count);        //用本过程在符号表中的size域记录形参的个数
				 terPtr++;
				 while (rv[terPtr].getId() == COMMA){
					 terPtr++;
					 if (rv[terPtr].getId() == SYM){
						 STable.enterVar(rv[terPtr].getValue(), level, 3 + count);      //3+count+1为形参在存储空间中的位置
						 count++;
						 STable.getAllTable()[propos].setSize(count);        //用本过程在符号表中的size域记录形参的个数
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
			 block(nxtlev);   //注意取消参数level的传递
			 if (rv[terPtr].getId() == SEMIC){
				 terPtr++;
				 nxtlev[PROC] = true;
				 //nxtlev[BEG] = true;
				 test(nxtlev, fsys, 20);  //过程说明后的符号不正确，应为过程说明符
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
			cx1 = Pcode.getCodePtr();             //用cx1记录jpc ，0，0（就是下面这一条语句产生的目标代码）在Pcode中的地址，用来一会回填
			Pcode.gen(Pcode.getJPC(), 0, 0);  //产生条件转移指令，条件的bool值为0时跳转，跳转的目的地址暂时填为0
			statement(fsys);
			Pcode.getPcodeArray()[cx1].setA(Pcode.getCodePtr());        //地址回填，将jpc，0，0中的A回填
			//Pcode.getPcodeArray()[cx2].setA(Pcode.getCodePtr());
			if (rv[terPtr].getId() == ELS){
				//Pcode.getPcodeArray()[cx1].setA(Pcode.getCodePtr());
				int cx2 = Pcode.getCodePtr();
				Pcode.gen(Pcode.getJMP(), 0, 0);
				terPtr++;
				statement(fsys);
				Pcode.getPcodeArray()[cx2].setA(Pcode.getCodePtr());
			}//没了？
		}
		else if (rv[terPtr].getId() == WHI){
			int cx1 = Pcode.getCodePtr();     //保存条件表达式在Pcode中的地址
			terPtr++;
			memcpy(nxtlev, fsys, sizeof(bool)*symnum);
			nxtlev[DO] = true;
			lexp(nxtlev);
			int cx2 = Pcode.getCodePtr();     //保存条件跳转指令的地址，在回填时使用，仍是条件不符合是跳转
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
			statement(fsys);  //循环体
			Pcode.gen(Pcode.getJMP(), 0, cx1);    //完成DO后的相关语句后，需要跳转至条件表达式处，检查是否符合条件，即是否继续循环
			Pcode.getPcodeArray()[cx2].setA(Pcode.getCodePtr());        //回填条件转移指令
		}
		else if (rv[terPtr].getId() == CAL){
			terPtr++;
			//id();
			int count = 0;//用来检验传入的参数和设定的参数是否相等
			TableRow tempRow;
			if (rv[terPtr].getId() == SYM){
				if (STable.isPreExistSTable(rv[terPtr].getValue(), level)){        //符号表中存在该标识符
					tempRow = STable.getRow(STable.getNameRow(rv[terPtr].getValue()));  //获取该标识符所在行的所有信息，保存在tempRow中
					if (tempRow.getType() == STable.getProc()) { //判断该标识符类型是否为procedure，SymTable中procdure类型用proc变量来表示，
						;
					}       //if类型为proc
					else{       //cal类型不一致的错误
						errorHapphen = true;
						showError(11, "");
						//return;
					}
				}       //if符号表中存在标识符
				else{           //cal 未定义变量的错误
					errorHapphen = true;
					showError(10, "");
					//return;
				}
				terPtr++;
				if (rv[terPtr].getId() == LBR){
					terPtr++;
					if (rv[terPtr].getId() == RBR){
						terPtr++;
						Pcode.gen(Pcode.getCAL(), level - tempRow.getLevel(), tempRow.getValue());        //调用过程中的保存现场由解释程序完成，这里只产生目标代码,+3需详细说明
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
						Pcode.gen(Pcode.getCAL(), level - tempRow.getLevel(), tempRow.getValue());        //调用过程中的保存现场由解释程序完成，这里只产生目标代码,+3需详细说明
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
					if (!STable.isPreExistSTable((rv[terPtr].getValue()), level)){      //首先判断在符号表中在本层或本层之前是否有此变量
						errorHapphen = true;
						showError(10, "");
						//return;

					}//if判断在符号表中是否有此变量
					else{           //sto未定义变量的错误
						TableRow tempTable = STable.getRow(STable.getNameRow(rv[terPtr].getValue()));
						if (tempTable.getType() == STable.getVar()){       //该标识符是否为变量类型
							Pcode.gen(Pcode.getOPR(), 0, 16);         //OPR 0 16	从命令行读入一个输入置于栈顶   //层差的含义所在？？直接用嵌套的层次数作为参数不可以吗？
							Pcode.gen(Pcode.getSTO(), level - tempTable.getLevel(), tempTable.getAddress());  //STO L ，a 将数据栈栈顶的内容存入变量（相对地址为a，层次差为L）
						}//if标识符是否为变量类型
						else{       //sto类型不一致的错误
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
							{      //首先判断在符号表中是否有此变量
								errorHapphen = true;
								showError(10, "");
								//return;

							}//if判断在符号表中是否有此变量
							else{           //sto未定义变量的错误
								TableRow tempTable = STable.getRow(STable.getNameRow(rv[terPtr].getValue()));
								if (tempTable.getType() == STable.getVar()){       //该标识符是否为变量类型
									Pcode.gen(Pcode.getOPR(), 0, 16);         //OPR 0 16	从命令行读入一个输入置于栈顶   //层差的含义所在？？直接用嵌套的层次数作为参数不可以吗？
									Pcode.gen(Pcode.getSTO(), level - tempTable.getLevel(), tempTable.getAddress());  //STO L ，a 将数据栈栈顶的内容存入变量（相对地址为a，层次差为L）
								}//if标识符是否为变量类型
								else{       //sto类型不一致的错误
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
				Pcode.gen(Pcode.getOPR(), 0, 14);         //输出栈顶的值到屏幕
				while (rv[terPtr].getId() == COMMA){
					terPtr++;
					exp(nxtlev);
					Pcode.gen(Pcode.getOPR(), 0, 14);         //输出栈顶的值到屏幕
				}

				Pcode.gen(Pcode.getOPR(), 0, 15);         //输出换行
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
		else if (rv[terPtr].getId() == BEG){//这里也没有terPtr++;          //body不生成目标代码
			memcpy(nxtlev, fsys, sizeof(bool)*symnum);
			nxtlev[SEMIC] = true;
			nxtlev[END] = true;
			body(nxtlev);
		}
		else if (rv[terPtr].getId() == SYM){      //赋值语句
			string name = rv[terPtr].getValue();
			terPtr++;
			if (rv[terPtr].getId() == CEQU){
				terPtr++;
				memcpy(nxtlev, fsys, sizeof(bool)*symnum);
				//nxtlev[ADD] = true;
				//nxtlev[SUB] = true;
				exp(nxtlev);
				if (!STable.isPreExistSTable(name, level)){        //检查标识符是否在符号表中存在
					errorHapphen = true;
					showError(14, name);
					//return;
				}//if判断在符号表中是否有此变量
				else{           //sto未定义变量的错误
					TableRow tempTable = STable.getRow(STable.getNameRow(name));
					if (tempTable.getType() == STable.getVar()){           //检查标识符是否为变量类型
						Pcode.gen(Pcode.getSTO(), level - tempTable.getLevel(), tempTable.getAddress());  //STO L ，a 将数据栈栈顶的内容存入变量
					}////检查标识符是否为变量类型
					else{       //类型不一致的错误
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
			Pcode.gen(Pcode.getOPR(), 0, 6);  //OPR 0 6	栈顶元素的奇偶判断，结果值在栈顶
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
			int loperator = lop();        //返回值用来产生目标代码，如下
			if (loperator != -1)
			{
				exp(fsys);
				if (loperator == EQU){
					Pcode.gen(Pcode.getOPR(), 0, 8);      //OPR 0 8	次栈顶与栈顶是否相等，退两个栈元素，结果值进栈
				}
				else if (loperator == NEQE){
					Pcode.gen(Pcode.getOPR(), 0, 9);      //OPR 0 9	次栈顶与栈顶是否不等，退两个栈元素，结果值进栈
				}
				else if (loperator == LES){
					Pcode.gen(Pcode.getOPR(), 0, 10);     //OPR 0 10	次栈顶是否小于栈顶，退两个栈元素，结果值进栈
				}
				else if (loperator == LESE){
					Pcode.gen(Pcode.getOPR(), 0, 13);     // OPR 0 13	次栈顶是否小于等于栈顶，退两个栈元素，结果值进栈
				}
				else if (loperator == LAR){
					Pcode.gen(Pcode.getOPR(), 0, 12);     //OPR 0 12	次栈顶是否大于栈顶，退两个栈元素，结果值进栈
				}
				else if (loperator == LARE){
					Pcode.gen(Pcode.getOPR(), 0, 11);     //OPR 0 11	次栈顶是否大于等于栈顶，退两个栈元素，结果值进栈
				}
			}
		}
	}

	 void exp(bool* fsys)
	 {
		 bool nxtlev[symnum];
		int tempId = rv[terPtr].getId();//用于保存正负号
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
			Pcode.gen(Pcode.getOPR(), 0, 1);      //  OPR 0 1	栈顶元素取反
		}
		while (rv[terPtr].getId() == ADD || rv[terPtr].getId() == SUB){
			tempId = rv[terPtr].getId();
			terPtr++;
			term(nxtlev);
			if (tempId == ADD){
				Pcode.gen(Pcode.getOPR(), 0, 2);       //OPR 0 2	次栈顶与栈顶相加，退两个栈元素，结果值进栈
			}
			else if (tempId == SUB){
				Pcode.gen(Pcode.getOPR(), 0, 3);      //OPR 0 3	次栈顶减去栈顶，退两个栈元素，结果值进栈
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
				Pcode.gen(Pcode.getOPR(), 0, 4);       //OPR 0 4	次栈顶乘以栈顶，退两个栈元素，结果值进栈
			}
			else if (tempId == DIV){
				Pcode.gen(Pcode.getOPR(), 0, 5);      // OPR 0 5	次栈顶除以栈顶，退两个栈元素，结果值进栈
			}
		}
	}

	 void factor(bool* fsys){
		 bool nxtlev[symnum];
		 test(facbegsys, fsys, 24);   /*检测因子的开始符号*/
		 while (inset(rv[terPtr].getId(), facbegsys))
		 {

			 if (rv[terPtr].getId() == CONST){
				 Pcode.gen(Pcode.getLIT(), 0, atoi(rv[terPtr].getValue().data()));    //是个数字,  LIT 0 a 取常量a放入数据栈栈顶
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
				 if (!STable.isPreExistSTable(name, level)){     //判断标识符在符号表中是否存在
					 errorHapphen = true;
					 showError(10, "");
					// return;
				 }//if判断在符号表中是否有此变量
				 else{           //未定义变量的错误
					 TableRow tempRow = STable.getRow(STable.getNameRow(name));
					 if (tempRow.getType() == STable.getVar()){ //标识符是变量类型
						 Pcode.gen(Pcode.getLOD(), level - tempRow.getLevel(), tempRow.getAddress());    //变量，LOD L  取变量（相对地址为a，层差为L）放到数据栈的栈顶
					 }
					 else if (tempRow.getType() == STable.getMyconst()){
						 Pcode.gen(Pcode.getLIT(), 0, tempRow.getValue());         //常量，LIT 0 a 取常量a放入数据栈栈顶
					 }
					 else{       //类型不一致的错误
						 errorHapphen = true;
						 showError(12, "");  //标识符不能为过程
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
			 test(fsys, nxtlev, 23); /* 一个因子处理完毕，遇到的单词应在fsys集合中 */
			 /* 如果不是，报错并找到下一个因子的开始，使语法分析可以继续运行下去 */
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
			cout << "wrong token" << endl;        //常量定义不是const开头,变量定义不是var 开头
			break;
		case 0:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  (rv[terPtr].getLine() - 1) <<  ":";
			cout << "Missing semicolon" << endl;        //缺少分号
			break;
		case 1:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Identifier illegal" << endl;       //标识符不合法
			break;
		case 2:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "The beginning of program must be 'program'" << endl;       //程序开始第一个字符必须是program
			break;
		case 3:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Assign must be ':='" << endl;       //赋值没用：=
			break;
		case 4:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing '('" << endl;       //缺少左括号
			break;
		case 5:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing ')'" << endl;       //缺少右括号
			break;
		case 6:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing 'begin'" << endl;       //缺少begin
			break;
		case 7:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing 'end'" << endl;       //缺少end
			break;
		case 8:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing 'then'" << endl;       //缺少then
			break;
		case 9:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Missing 'do'" << endl;       //缺少do
			break;
		case 10:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Not exist " << "'" << rv[terPtr].getValue() << "'" << endl;       //call，write，read语句中，不存在标识符
			break;
		case 11:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "'" << rv[terPtr].getValue() << "'" << "is not a procedure" << endl;       //该标识符不是proc类型
			break;
		case 12:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "'" << rv[terPtr].getValue() << "'" << "is not a variable" << endl;       //read，write语句中，该标识符不是var类型
			break;
		case 13:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "'" << name << "'" << "is not a variable" << endl;       //赋值语句中，该标识符不是var类型
			break;
		case 14:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Not exist" << "'" << name << "'" << endl;       //赋值语句中，该标识符不存在
			break;
		case 15:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Already exist" << "'" << name << "'" << endl;       //该标识符已经存在
			break;
		case 16:
			cout << "ERROR " <<  i <<  " " <<  "in line " <<  rv[terPtr].getLine() <<  ":";
			cout << "Number of parameters of procedure " << "'" << name << "'" << "is incorrect" << endl;       //该标识符已经存在
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