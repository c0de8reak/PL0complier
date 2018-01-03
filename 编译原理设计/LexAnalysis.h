#ifndef LEXANALYSIS_H
#define LEXANALYSIS_H
#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include"ChTable.h"
#include"RValue.h" 

class LexAnalysis{
	//keyWord={"program","begin","end","if","then","else","const","procedure","var","do","while","call","read","write","repeat","odd"};
	private:
	 static const int NUL = 0; //   NULL
     static const int PROG=1;//program
     static const int BEG=2;//begin
     static const int END=3;//end
     static const int IF=4;//if
     static const int THEN=5;//then
     static const int ELS=6;//else
     static const int CON=7;//const
     static const int PROC=8;//procdure
     static const int VAR=9;//var
     static const int DO=10;//do
     static const int WHI=11;//while
     static const int CAL=12;//call
     static const int REA=13;//read
     static const int WRI=14;//write
     static const int REP=15;//repeat
     static const int ODD=16;//  ODD      和keyWord中每个字的序号是相等的


     static const int EQU=17;//"="
     static const int LES=18;//"<"
     static const int LESE=19;//"<="
     static const int LARE=20;//">="
     static const int LAR=21;//">"
     static const int NEQE=22;//"<>"


     static const int ADD=23;//"+"
     static const int SUB=24;//"-"
     static const int MUL=25;//"*"
     static const int DIV=26;//"/"

     static const int SYM=27;//标识符
     static const int CONST=28;//常量

     static const int CEQU=29;//":="

     static const int COMMA=30;//","
     static const int SEMIC=31;//";"
     static const int POI=32;//"."
     static const int LBR=33;//"("
     static const int RBR=34;//")"


     ChTable ct;
     RValue rv;
     string *keyWord=ct.getKeyWord();
     string *symTable=ct.getSymTable();
     int symLength=ct.getsymLength();
     string* constTable=ct.getConstTable();
     int conLength=ct.getconstLength();

     char ch=' ';
     string strToken;
     string filename;
     char* buffer;
     int buffer_length;
     int searchPtr=0;
     int line=1;
     bool errorHappen=false;
	 int err = 0;				//错误的个数
	public:
     LexAnalysis(string _filename){
        for(int i=0;i<symLength;i++){
            symTable[i]="";
        }
        for(int j=0;j<conLength;j++){
            constTable[j]="";
        }
        filename=_filename;
    }

    /**
     * 预处理函数：
     * 功能：读取源文件内容到字符数组buffer中去，包括换行符
     * */
     char* preManage(){
        fstream infile(filename.data(),ios::in);
        if(!infile)
        {
        	cout << "打开文件失败！" << endl;
        	exit(0);
		}
            //  
        char temp1[101];
        string temp2 ="";
        while(infile.peek()!= EOF){
			infile.getline(temp1,100);
			if(infile.fail())
			{
				break;
			}
			temp2.append(temp1);
			temp2.append(1,'\n');
        }
        //buffer = (char *)temp2.c_str();
        buffer_length = temp2.length();
		buffer = new char[buffer_length];
		strcpy(buffer, temp2.c_str());
        infile.close();
        return buffer;
        }
        
     char getChar(){
        if(searchPtr<buffer_length){
            ch=buffer[searchPtr];
            searchPtr++;
        }
		//cout << ch << endl; 
        return ch;
    }


     void getBC(){
        while( (ch==' '||ch=='\t'||ch=='\n')&&(searchPtr<buffer_length)){
            if(ch=='\n'){
                line++;
            }
            getChar();
        }
    }

     string concat(){
        strToken.append(1,ch);
        return strToken;
    }

     bool isLetter(){
        if((ch<='z')&&(ch>='a')||(ch<='Z')&&(ch>='A')){
            return true;
        }
        return false;
    }

     bool isDigit(){
        if((ch<='9')&&(ch>='0')){
            return true;
        }
        return false;
    }

     int reserve(){
        for(int i=0;i<16;i++){
            if(keyWord[i].compare(strToken)==0){
                return i+1;
            }
        }
        return 0;
    }

     void retract(){
        searchPtr--;
        ch=' ';
    }

     int insertId(){
        for(int i=0;i<symLength;i++){
            if(symTable[i].compare("")==0){        //注意后期修改********** 
                symTable[i]=strToken;
                return i;
            }
        }
        return -1;//表示symTable已经满了
    }

     int insertConst(){
        for(int i=0;i<conLength;i++){
            if(constTable[i].compare("")==0){		//注意后期修改********** 
                constTable[i]=strToken;
                return i;
            }
        }
        return -1;//constTable已经满了
    }
    //上面的所有函数参考书上的伪码程序即可

     void showError(){
		err = err + 1;
       	cout << endl;
		cout << "ERROR 24 in line " << line << ":";
		cout << "Exist illegal symbol ,cannot recognize the word " << endl;       //存在非法符号
    }

    /**
     * 字符识别函数
     * 功能：通过读取buffer数组中的单个字符进行识别源程序中的各个元素，每次识别一个元素
     * @return 识别出的字符的属性：RV.getId()是属性，RV.getValue()是值，RV.getLine()是所在行号
     * */
     RValue analysis(){
        int code,value;
        strToken="";
        getChar();
        getBC();//经过此步，如果ch=='\n'，则肯定是到达了文件末尾
        if(ch=='\n'){
            rv.setId(-1);
            rv.setValue("-1");
            rv.setLine(line);
            return rv;
        }
        if(isLetter()){
            while((isLetter()||isDigit())){
                concat();
                getChar();
            }
            retract();
            code=reserve();
            if(code==0){
                value=insertId();
                rv.setId(SYM);
                rv.setValue(symTable[value]);
                rv.setLine(line);
                return rv;
            }
            else {
                rv.setId(code);
                rv.setValue("-");
                rv.setLine(line);
                return rv;
            }
        }else if(isDigit()){
            while(isDigit()){
                concat();
                getChar();
            }
            retract();
            value=insertConst();
            rv.setId(CONST);
            rv.setValue(constTable[value]);
            rv.setLine(line);
            return rv;
        }else if(ch=='='){
            rv.setId(EQU);
            rv.setValue("-");
            rv.setLine(line);
            return rv;
        }else if(ch=='+'){
            rv.setId(ADD);
            rv.setValue("-");
            rv.setLine(line);
            return rv;
        }else if(ch=='-'){
            rv.setId(SUB);
            rv.setValue("-");
            rv.setLine(line);
            return rv;
        } else if(ch=='*'){
            rv.setId(MUL);
            rv.setValue("-");
            rv.setLine(line);
            return rv;
        }else if(ch=='/'){
            rv.setId(DIV);
            rv.setValue("/");  //可能有错 
            rv.setLine(line);
            return rv;
        }else if(ch=='<'){
            getChar();
            if(ch=='='){
                rv.setId(LESE);
                rv.setValue("-");
                rv.setLine(line);
                return rv;
            }else if(ch=='>'){
                rv.setId(NEQE);
                rv.setValue("-");
                rv.setLine(line);
                return rv;
            }else{
                retract();
                rv.setId(LES);
                rv.setValue("-");
                rv.setLine(line);
                return rv;
            }
        }else if(ch=='>'){
            getChar();
            if(ch=='='){
                rv.setId(LARE);
                rv.setValue("-");
                rv.setLine(line);
                return rv;
            }else{
                retract();
                rv.setId(LAR);
                rv.setValue("-");
                rv.setLine(line);
                return rv;
            }
        }else if(ch==','){
            rv.setId(COMMA);
            rv.setValue("-");
            rv.setLine(line);
            return rv;
        }else if(ch==';'){
            rv.setId(SEMIC);
            rv.setValue("-");
            rv.setLine(line);
            return rv;
        }else if(ch=='.'){
            rv.setId(POI);
            rv.setValue("-");
            rv.setLine(line);
            return rv;
        }else if(ch=='('){
            rv.setId(LBR);
            rv.setValue("-");
            rv.setLine(line);
            return rv;
        }else if(ch==')'){
            rv.setId(RBR);
            rv.setValue("-");
            rv.setLine(line);
            return rv;
        }else if(ch==':'){
            getChar();
            if(ch=='='){
                rv.setId(CEQU);
                rv.setValue("-");
                rv.setLine(line);
                return rv;
            }else{
                retract();
            }
        }
		else
		{
			//errorHappen = true;
			showError();
			rv.setId(NUL);
			rv.setValue("-");
			rv.setLine(line);
			return rv;
		}
    }


/**
 * 循环识别出所有字符并输出到文件lex.txt中
 * */
     int bAnalysis(){
        preManage();
        RValue temp;
        string str="lex.txt";
        fstream outfile(str.data(),ios::out);
         if(!outfile)
        {
        	cout << "打开文件失败！" << endl;
        	exit(0);
		}
        while(searchPtr<buffer_length){
        	
            temp=analysis();
           /* string tempId=string.valueOf(temp.getId()),tempLine=string.valueOf(temp.getLine());
                myout.write(bid);
                myout.write(' ');
                myout.write(bname);
                myout.write(' ');
                myout.write(bline);
                myout.write('\n');
            }catch(IOException e){
                e.printStackTrace();
            }*/
            outfile << temp.getId() << " " << temp.getValue() << " " << temp.getLine() << endl;
        }//while
        outfile.close();
		return err;
        /*if(errorHappen==true){
            showError();
        }*/
    }
};
#endif
