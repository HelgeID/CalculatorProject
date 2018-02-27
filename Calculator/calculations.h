/*EN This program is for training and testing, so it works on the principle of "as is"!*/
/*RU Эта программа представляет собой обучение и тестирование, поэтому работает по принципу "как есть"!*/
/*UA Ця програма являє собою навчання і тестування, тому працює за принципом "як є"!*/

#if !defined CALCULATIONS_H
#define CALCULATIONS_H

#define sNull "0"
#define sEmpty ""
#define cADD '+'
#define cSUB '-'
#define cMUL '*'
#define cDIV '/'

#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>
using std::string;

namespace out {
	std::basic_string <char> snumber;
	char* operation_msg;
	char* memory_msg;
}

class Calculations
{
	private:
		std::basic_string <char> snumber, mnumber, pre_result;
		std::basic_string <char> buff_1, buff_2;
		bool buffFlag, overflowFlag, keylockFlag;
		bool percentf, reciprocf, sqrtf;
		char act_opr;//write operations: +,-,*,/

		bool equalFlag, operationFlag, digitFlag;

		template <typename T> std::basic_string <char> toStringFull(T, const unsigned int);
		template <typename T> std::basic_string <char> toString(T);
		template <typename T> T fromString(std::basic_string <char>);

		bool& preActiveEqual(bool);
		bool& preActiveOperation(bool);
		bool& preActiveDigit(bool);

		std::basic_string <char> ccalculations(std::basic_string <char>);
		
		void gotoxy(const int, const int);
		void console_information(char*, std::basic_string <char>, int, int);

	private:
		bool isDigit(const char symbol) {
			return (symbol>=0x30&&symbol<=0x39);
		}
		bool isOperation(const char symbol) {
			if (!(symbol>=0x2A&&symbol<=0x2F))
				return false;
			try {
				if (symbol!=0x2C&&symbol!=0x2E)
					throw 0;
			}
			catch(...) {
				return true;
			}
			return false;
		}
		bool isEqual(const char symbol) {
			if (symbol==0x3D)
				return true;
			else
				return false;
		}
		bool isSymbol(const char symbol) {
			size_t length=snumber.length();
			bool flag(false);
			for (size_t i(0); i<length; ++i) {
				if (symbol==snumber[i]) {
					flag=true;
					break;
				}
			}
			return flag;
		}

	public:
		explicit Calculations(void):snumber(sNull), mnumber(sNull), pre_result(sNull), equalFlag(0), operationFlag(0), digitFlag(0) {
			out::snumber=snumber;
			out::operation_msg=sEmpty;
			out::memory_msg=sEmpty;
			buff_1=sNull;
			buff_2=sNull;
			buffFlag=false;
			overflowFlag=false;
			keylockFlag=false;
			act_opr=0x0;

			percentf=0;
			reciprocf=0;
			sqrtf=0;
		}

		~Calculations(void) {
		}
		
		void debug(const char*);

		void control_number(std::basic_string <char>&);
		void enter_data(char);
		void enter_memory_data(char);
		void back_digit();
		void sign_number();
		void reset_data();
		void reset_number();
		void reciproc_number();
		void percent_number();
		void sqrt_number();

		//use functions for keyboard:
		void ONE_processing()		{if (!keylockFlag) enter_data('1'); return;};
		void TWO_processing()		{if (!keylockFlag) enter_data('2'); return;};
		void THREE_processing()		{if (!keylockFlag) enter_data('3'); return;};
		void FOUR_processing()		{if (!keylockFlag) enter_data('4'); return;};
		void FIVE_processing()		{if (!keylockFlag) enter_data('5'); return;};
		void SIX_processing()		{if (!keylockFlag) enter_data('6'); return;};
		void SEVEN_processing()		{if (!keylockFlag) enter_data('7'); return;};
		void EIGHT_processing()		{if (!keylockFlag) enter_data('8'); return;};
		void NINE_processing()		{if (!keylockFlag) enter_data('9'); return;};
		void ZERO_processing()		{if (!keylockFlag) enter_data('0'); return;};
		void POINT_processing()		{if (!keylockFlag) enter_data(','); return;};
		void ADD_processing()		{if (!keylockFlag) enter_data(cADD); return;};
		void SUB_processing()		{if (!keylockFlag) enter_data(cSUB); return;};
		void MUL_processing()		{if (!keylockFlag) enter_data(cMUL); return;};
		void DIV_processing()		{if (!keylockFlag) enter_data(cDIV); return;};
		void SIGN_processing()		{if (!keylockFlag) sign_number(); return;};
		void EQUAL_processing()		{if (!keylockFlag) enter_data('='); return;};
		void RECIPROC_processing()	{if (!keylockFlag) reciproc_number(); return;};
		void PERCENT_processing()	{if (!keylockFlag) percent_number(); return;};
		void SQRT_processing()		{if (!keylockFlag) sqrt_number(); return;};
		void BACK_processing()		{if (!keylockFlag) back_digit(); return;};
		void CE_processing()		{reset_number(); return;};
		void C_processing()			{reset_data(); return;};
		void MC_processing()		{if (!keylockFlag) enter_memory_data('c'); return;};
		void MR_processing()		{if (!keylockFlag) enter_memory_data('r'); return;};
		void MS_processing()		{if (!keylockFlag) enter_memory_data('s'); return;};
		void MPLUS_processing()		{if (!keylockFlag) enter_memory_data(cADD); return;};
		void MMINUS_processing()	{if (!keylockFlag) enter_memory_data(cSUB); return;};

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		void ControlDisplay();
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
};

/*
//function works, but the values are not fixed
template <typename T>
std::basic_string <char> Calculations::toStringFull(T value, const unsigned int sign=16) {
	std::basic_string <char> str;
	std::ostringstream oss;
	oss<<std::setprecision(sign)<<value;
	str=oss.str();
	string::iterator ptr(str.begin());
	while (ptr!=str.end()) {
		if (*ptr=='.') {
			*ptr=',';
			break;
		}
		++ptr;
	}
	ptr=str.begin();
	return str;
}
*/

template <typename T>
std::basic_string <char> Calculations::toStringFull(T value, const unsigned int sign=16)
{
	std::basic_string <char> str=sEmpty, str_buf;
	std::ostringstream oss;
	oss<<std::fixed<<std::setprecision(sign)<<value;
	str_buf=oss.str();
	string::iterator ptr(str_buf.begin());
	int integer_count(0);
	unsigned int counter(0);
	bool pointf=false;
	while (ptr!=str_buf.end()) {
		if (ptr[0]=='-'&&*ptr==ptr[0]) {
			{str+=*ptr; ptr++;}
			continue;
		}
		if (*ptr=='.') {
			*ptr=',';
			{str+=*ptr; ptr++;}
			integer_count+=counter;
			pointf=true;
		}
		else {
			if (counter>sign) {
				if (!pointf)
					integer_count+=1;
				ptr++;
			}
			else {
				{str+=*ptr; ptr++;}
				counter++;
			}
		}
	}
	
	if (!integer_count)
		integer_count=counter;
	
	if (pointf==true) {
		counter=0;
		ptr=str.end()-1;
		while (str.length()>0) {
			if (*ptr=='0')
				counter++;
			else
				break;
			ptr--;
		}
		str.erase(str.length()-counter,counter);
		pointf=false;
	}
	
	ptr=str.end()-1;
	if (*ptr==',')
		str.erase(str.length()-1,1);
	ptr=str_buf.begin();
	
	if (str=="-0")
		str=sNull;
	else {
		if (integer_count>sign+1) {
			str="1";
			overflowFlag=true;
		}
	}
	return str;
}

template <typename T>
std::basic_string <char> Calculations::toString(T value) {
	std::basic_string <char> str;
	std::ostringstream oss;
	oss<<value;
	str=oss.str();
	string::iterator ptr(str.begin());
	while (ptr!=str.end()) {
		if (*ptr=='.') {
			*ptr=',';
			break;
		}
		++ptr;
	}
	ptr=str.begin();
	return str;
}

template <typename T>
T Calculations::fromString(std::basic_string <char> str) {
	string::iterator ptr(str.begin());
	while (ptr!=str.end()) {
		if (*ptr==',') {
			*ptr='.';
			break;
		}
		++ptr;
	}
	ptr=str.begin();
	std::istringstream iss(str);
	T value;
	iss>>value;
	return value;
}

bool& Calculations::preActiveEqual(bool flag=false) {
	if (!flag)
		return equalFlag;
	else {
		operationFlag=false;
		digitFlag=false;
		return equalFlag;
	}
}

bool& Calculations::preActiveOperation(bool flag=false) {
	if (!flag)
		return operationFlag;
	else {
		equalFlag=false;
		digitFlag=false;
		return operationFlag;
	}
}

bool& Calculations::preActiveDigit(bool flag=false) {
	if (!flag)
		return digitFlag;
	else {
		equalFlag=false;
		operationFlag=false;
		return digitFlag;
	}
}

std::basic_string <char> Calculations::ccalculations(std::basic_string <char> str_buff)
{
	size_t length=str_buff.length();
	int count(1);
	std::basic_string <char> operations=sEmpty;

	for (size_t i(0); i<length; ++i) {
		if (str_buff[0]=='-'&&!i)
			continue;
		
		if (str_buff[i]==cADD||str_buff[i]==cSUB||str_buff[i]==cMUL||str_buff[i]==cDIV) {
			count++;
			operations=operations+str_buff[i];
			if (str_buff[i+1]=='-')
				++i;
		}
	}

	std::basic_string <char> *array_str = new std::basic_string <char>[count];
	for (size_t i(0), index(0); i<length; ++i) {
		if (str_buff[0]=='-'&&!i) {
			array_str[index]+=str_buff[0];
			continue;
		}
		
		if (str_buff[i]==cADD||str_buff[i]==cSUB||str_buff[i]==cMUL||str_buff[i]==cDIV) {
			++index;
			if (str_buff[i+1]=='-') {
				array_str[index]+=str_buff[i+1];
				--index;
				continue;
			}
		}
		else
			array_str[index]+=str_buff[i];
	}

	double *array_num = new double[count];
	for (int i(0); i<count; ++i)
		array_num[i]=fromString<double>(array_str[i]);
	
	std::basic_string <char> result_snumber;
	double result(*array_num);
	int indexOpr(EOF);
	int sizeOpr(operations.length());
	while (++indexOpr<sizeOpr) {
		if (operations[indexOpr]==cADD)
			result+=array_num[indexOpr+1];
		else
		if (operations[indexOpr]==cSUB)
			result-=array_num[indexOpr+1];
		else
		if (operations[indexOpr]==cMUL)
			result*=array_num[indexOpr+1];
		else
		if (operations[indexOpr]==cDIV) {
			if (!array_num[indexOpr+1]) {
				result_snumber="NOT DIVIDED";
				goto exit_point;
			}
			result/=array_num[indexOpr+1];
		}
	}
	
	//13 - numbers after the decimal point
	result_snumber=toStringFull(result, 13);
	if (overflowFlag)
		result_snumber="OUT OF RANGE";
	exit_point:
	delete [] array_str;
	delete [] array_num;
	
	return result_snumber;
}

void Calculations::control_number(std::basic_string <char>& str)
{
	char ls1=0x0, ls2(ls1);
	string::iterator ptr=str.end()-1;
	if (*ptr=='+'||*ptr=='-'||*ptr=='*'||*ptr=='/') {
		ls1=*ptr;
		str.erase(str.length()-1,1);
	}
	
	ptr=str.begin();
	bool pointf=false;
	while (ptr!=str.end()) {
		if (*ptr==',') {
			pointf=true;
			ptr=str.end()-1;
			break;
		}
		else
			ptr++;
	}
		
	if (pointf) {
		int counter=0;
		while (str.length()>0) {
			if (*ptr=='0')
				counter++;
			else
				break;
			ptr--;
		}
		str.erase(str.length()-counter,counter);
		pointf=false;
	}
		
	ptr=str.end();
	ls2=*(ptr-1);
	if (ls2==',')
		{
			str.erase(str.length()-1,1);
		}
	ptr=str.begin();
	if (str=="-0")
		str=sNull;
	if (isOperation(ls1))
		str=str+ls1;
	return;
}

void Calculations::enter_data(char symbol)
{
	if (isEqual(symbol)) {
		out::operation_msg="EQUAL";
		if (buffFlag||preActiveEqual()||(isOperation(act_opr)&&preActiveDigit())) {
			char last_opr;
			string::iterator ptr(buff_1.end());
			last_opr=*(ptr-1);
			if (isDigit(last_opr)) {
				last_opr=act_opr;
				{
					string str_symbol=sEmpty;
					buff_1.insert(buff_1.length(), str_symbol+=last_opr);
				}
			}
			control_number(buff_1);
			control_number(buff_2);
			//ccalculations:
			out::snumber=ccalculations(buff_1+buff_2);
			pre_result=out::snumber;
			if (out::snumber=="NOT DIVIDED"||out::snumber=="OUT OF RANGE") {
				std::basic_string <char> s(out::snumber);
				reset_data();
				out::snumber=s;
				preActiveEqual(1)=false;
				preActiveOperation(1)=false;
				preActiveDigit(1)=false;
				keylockFlag=true;
				return;
			}
			buff_1=out::snumber;
			snumber=sNull;
			{
				string str_symbol=sEmpty;
				buff_1.insert(buff_1.length(), str_symbol+=last_opr);
			}
			buffFlag=false;
			preActiveEqual(1)=true;
		}
		else {
			snumber=sNull;
			control_number(out::snumber);
		}
		return;
	}
	
	if (isOperation(symbol)) {
		act_opr=symbol;
		switch (act_opr) {
			case cADD: out::operation_msg="ADD"; break;
			case cSUB: out::operation_msg="SUB"; break;
			case cMUL: out::operation_msg="MUL"; break;
			case cDIV: out::operation_msg="DIV"; break;
			default: break;
		}

		if (preActiveEqual())
			{
				buff_1.erase(buff_1.length()-1,1);
			}
		
		if (buffFlag==true) {
			if(preActiveDigit()) {
				control_number(buff_1);
				control_number(buff_2);
				//ccalculations:
				out::snumber=ccalculations(buff_1+buff_2);
				pre_result=out::snumber;
				if (out::snumber=="NOT DIVIDED"||out::snumber=="OUT OF RANGE") {
					std::basic_string <char> s(out::snumber);
					reset_data();
					out::snumber=s;
					preActiveEqual(1)=false;
					preActiveOperation(1)=false;
					preActiveDigit(1)=false;
					keylockFlag=true;
					return;
				}
				buff_1=out::snumber;
				snumber=sNull;
				buff_2=buff_1;
				control_number(buff_2);
				{
					string str_symbol=sEmpty;
					buff_1.insert(buff_1.length(), str_symbol+=act_opr);
				}
			}
		}
		
		if (!buffFlag) {
			snumber=sNull;
			buff_2=buff_1;
			control_number(buff_2);
			out::snumber=buff_1;
			{
				string str_symbol=sEmpty;
				buff_1.insert(buff_1.length(), str_symbol+=act_opr);
			}
			buffFlag=true;
		}
		else {
			{
				buff_1.erase(buff_1.length()-1,1);
			}
			out::snumber=buff_1;
			{
				string str_symbol=sEmpty;
				buff_1.insert(buff_1.length(), str_symbol+=act_opr);
			}
		}
		control_number(out::snumber);
		preActiveOperation(1)=true;
		return;
	}
	
	if (isDigit(symbol)||symbol==',') {
		if (percentf)
			snumber=sNull;
		percentf=0;
		reciprocf=0;
		sqrtf=0;
		if (out::operation_msg=="EQUAL")
			out::operation_msg=sEmpty;
		if (symbol==',') {
			if (isSymbol(','))
				return;
			else
				{
					string str_symbol=sEmpty;
					snumber.insert(snumber.length(), str_symbol+=symbol);
				}
		}
		if (snumber==sNull)
			snumber.clear();
		if (symbol!=',')
			{
				string str_symbol=sEmpty;
				snumber.insert(snumber.length(), str_symbol+=symbol);
			}
		std::basic_string <char>::size_type length;
		length=snumber.length();
		if (length>14) {
			if (isSymbol('-')||isSymbol(',')) {
				if (length>15) {
					if (isSymbol('-')&&isSymbol(',')) {
						if (length>16)
							{
								snumber.erase(snumber.length()-1,1);
							}
					} else
						{
							snumber.erase(snumber.length()-1,1);
						}
				}
			} else
				{
					snumber.erase(snumber.length()-1,1);
				}
		}

		out::snumber=snumber;
		buffFlag?buff_2=snumber:buff_1=snumber;
		preActiveDigit(1)=true;
		return;
	}
}

void Calculations::enter_memory_data(char symbol) {
	switch (symbol) {
		case 'c':
			mnumber=sNull;
			goto exit_point;
		
		case 'r':
			snumber=mnumber;
			out::snumber=snumber;
			buffFlag?buff_2=snumber:buff_1=snumber;
			if (out::operation_msg=="EQUAL")
				out::operation_msg=sEmpty;
			snumber=sNull;
			preActiveDigit(1)=true;
			goto exit_point;
		
		case 's':
			snumber=sNull;
			mnumber=sNull;
			control_number(out::snumber);
			//ccalculations:
			mnumber=ccalculations(mnumber+cADD+out::snumber);
			goto exit_point;
		
		case cADD:
			snumber=sNull;
			control_number(out::snumber);
			//ccalculations:
			mnumber=ccalculations(mnumber+symbol+out::snumber);
			goto exit_point;
		
		case cSUB:
			snumber=sNull;
			control_number(out::snumber);
			//ccalculations:
			mnumber=ccalculations(mnumber+symbol+out::snumber);
			goto exit_point;
		
		default:
			goto exit_point;
	}
	
	exit_point:
	!(mnumber==sNull)?out::memory_msg="M":out::memory_msg=sEmpty;
	return;
}

void Calculations::back_digit() {
	if (preActiveEqual()||percentf||reciprocf||sqrtf)
		return;
	buffFlag?snumber=buff_2:snumber=buff_1;
	string::iterator ptr(snumber.begin());
	if (*ptr=='-') {
		if (snumber.size()<=2)
			snumber=sNull;
		else
			{
				snumber.erase(snumber.length()-1,1);
			}
	}
	else {
		if (snumber.size()>1)
			{
				snumber.erase(snumber.length()-1,1);
			}
		else
			snumber=sNull;
	}
	buffFlag?buff_2=snumber:buff_1=snumber;
	out::snumber=snumber;
	return;
}

void Calculations::sign_number() {
	if (preActiveDigit()||preActiveOperation()) {
		buffFlag?snumber=buff_2:snumber=buff_1;
		if (snumber==sNull) {
			preActiveDigit(1)=true;
			return;
		}
		string::iterator ptr(snumber.begin());
		if (*ptr=='-') {
			snumber.erase(0,1);
			buffFlag?buff_2=snumber:buff_1=snumber;
			out::snumber=snumber;
			preActiveDigit(1)=true;
			return;
		}
		snumber="-"+snumber;
		buffFlag?buff_2=snumber:buff_1=snumber;
		out::snumber=snumber;
		preActiveDigit(1)=true;
	}
	else {
		if (preActiveEqual()) {
			if (buff_1=="0+"||buff_1=="0-"||buff_1=="0*"||buff_1=="0/")
				return;
			snumber=buff_1;
			string::iterator ptr(snumber.begin());
			unsigned int last(snumber.length()-1);
			if (*ptr=='-') {
				snumber.erase(last,1);
				snumber.erase(0,1);
			}
			else {
				snumber.erase(last,1);
				snumber="-"+snumber;
			}
			out::snumber=snumber;
			ptr=buff_1.end()-1;
			buff_1=snumber+=*ptr;
			ptr=snumber.begin();
			snumber=sNull;
		}
	}
	return;
}

void Calculations::reset_data() {
	snumber=sNull;
	pre_result=sNull;
	out::snumber=snumber;
	out::operation_msg=sEmpty;
	equalFlag=false;
	operationFlag=false;
	digitFlag=false;
	buff_1=sNull;
	buff_2=sNull;
	buffFlag=false;
	overflowFlag=false;
	keylockFlag=false;
	act_opr=0x0;

	percentf=0;
	reciprocf=0;
	sqrtf=0;
	return;
}

void Calculations::reset_number() {
	snumber=sNull;
	buffFlag?buff_2=snumber:buff_1=snumber;
	out::snumber=snumber;
	keylockFlag=false;
	if (out::operation_msg=="EQUAL")
		out::operation_msg=sEmpty;
	preActiveDigit(1)=true;
	return;
}

void Calculations::reciproc_number() {
	char opr=0x0;
	buffFlag?snumber=buff_2:snumber=buff_1;
	if (isOperation(opr=snumber[snumber.length()-1]))
		snumber.erase(snumber.length()-1,1);
	out::snumber=ccalculations("1/"+snumber);
	if (out::snumber=="NOT DIVIDED") {
		std::basic_string <char> s(out::snumber);
		reset_data();
		out::snumber=s;
		preActiveEqual(1)=false;
		preActiveOperation(1)=false;
		preActiveDigit(1)=false;
		keylockFlag=true;
		return;
	}
	snumber=out::snumber;
	if (buffFlag)
		buff_2=snumber;
	else {
		if (opr==cADD||opr==cSUB||opr==cMUL||opr==cDIV)
			buff_1=snumber+opr;
		else
			buff_1=snumber;
	}
	snumber=sNull;
	if (out::operation_msg=="EQUAL")
		out::operation_msg=sEmpty;
	if (buffFlag)
		preActiveDigit(1)=true;
	reciprocf=1;
	return;
}

void Calculations::percent_number() {
	std::basic_string <char> buff_1_tmp;
	std::basic_string <char> buff_2_tmp;
	if (buffFlag) {
		buff_1_tmp=buff_1;
		buff_1_tmp.erase(buff_1_tmp.length()-1,1);
		buff_1_tmp+=cMUL;
		buff_2_tmp=buff_2;
		buff_2_tmp+=cDIV;

		//ccalculations:
		buff_2_tmp=ccalculations(buff_1_tmp+buff_2_tmp+"100");
		out::snumber=buff_2=buff_2_tmp;
		snumber=sNull;
	}
	else {
		if (preActiveEqual())
			snumber=out::snumber;
		buff_1_tmp=snumber;
		buff_1_tmp+=cMUL;
		buff_2_tmp=pre_result;
		buff_2_tmp+=cDIV;

		char opr(buff_1[buff_1.length()-1]);
		//ccalculations:
		buff_1_tmp=ccalculations(buff_1_tmp+buff_2_tmp+"100");
		out::snumber=buff_1=buff_1_tmp;
		if (opr==cADD||opr==cSUB||opr==cMUL||opr==cDIV) {
			string str_symbol=sEmpty;
			buff_1.insert(buff_1.length(), str_symbol+=opr);
		}
		snumber=out::snumber;
		if (out::operation_msg=="EQUAL")
			out::operation_msg=sEmpty;
	}
	if (buffFlag)
		preActiveDigit(1)=true;
	percentf=1;
	return;
}

void Calculations::sqrt_number() {
	char opr=0x0;
	buffFlag?snumber=buff_2:snumber=buff_1;
	if (isOperation(opr=snumber[snumber.length()-1]))
		snumber.erase(snumber.length()-1,1);
	double dnumber=fromString<double>(snumber);
	if (dnumber<0) {
		reset_data();
		out::snumber="NOT EXECUTED";
		preActiveEqual(1)=false;
		preActiveOperation(1)=false;
		preActiveDigit(1)=false;
		keylockFlag=true;
		return;
	}
	dnumber=pow(dnumber, 0.5);//SQRT
	out::snumber=toStringFull(dnumber, 13);
	snumber=out::snumber;
	if (buffFlag)
		buff_2=snumber;
	else {
		if (opr==cADD||opr==cSUB||opr==cMUL||opr==cDIV)
			buff_1=snumber+opr;
		else
			buff_1=snumber;
	}
	snumber=sNull;
	if (out::operation_msg=="EQUAL")
		out::operation_msg=sEmpty;
	if (buffFlag)
		preActiveDigit(1)=true;
	sqrtf=1;
	return;
}

///////////////////////
///debug information///
///////////////////////
void Calculations::gotoxy(const int x, const int y) {
	COORD posXY={x,y};
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, posXY);
	return;
}

void Calculations::console_information(char* txt, std::basic_string <char> infS, int pX, int pY) {
	gotoxy(pX, pY);
	printf("%s", txt);
	bool f(false);
	size_t n(4);
	for (size_t ind(0); ind<infS.length(); ++ind) {
		if (ind<n)
			;
		else {
			n=2;
			break;
		}
	}
	for (size_t ind(0); ind<infS.length(); ++ind) {
		if (ind<n)
			printf("%c", infS[ind]);
		else {
			printf("..");
			f=true;
			break;
		}
	}
	if (f) {
		string::iterator ptr(infS.end()-2);
		while (ptr!=infS.end()) {
			printf("%c", *ptr);
			ptr++;
		}
		f=false;
	}
	return;
}

void Calculations::debug(const char* key) {
	static int POS_Y=0;
	char* buffFlagINF;
	if (buffFlag)
		buffFlagINF="YES";
	else 
		buffFlagINF="NO";
	
	std::basic_string <char> act("Op");
	if (preActiveDigit())
		act="Dig";
	else if (preActiveOperation())
		act+=act_opr;
	else if (preActiveEqual())
		act="Equ";
	else
		act="_";

    console_information("key:", 	key,    		0,		POS_Y);
    console_information("bfg:", 	buffFlagINF, 	7,		POS_Y);
    console_information("snum:", 	snumber, 		15,		POS_Y);
    console_information("buf1:", 	buff_1, 		27,		POS_Y);
    console_information("buf2:", 	buff_2, 		39,		POS_Y);
	console_information("pre:", 	pre_result, 	51,		POS_Y);
    console_information("out:", 	out::snumber, 	62,		POS_Y);
	console_information("", 		act, 			75,		POS_Y);
	POS_Y=(POS_Y+1);
	return;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Calculations::ControlDisplay() {
	if (out::snumber=="NOT DIVIDED"||out::snumber=="NOT EXECUTED"||out::snumber=="OUT OF RANGE")
		return;

	bool errorf(false);
	if (out::snumber!="FATAL ERROR") {
		if (out::snumber.length()>16) {
			out::snumber="FATAL ERROR";
			errorf=true;
		}
	}

	if (out::snumber!="FATAL ERROR") {
		string::iterator ptr(out::snumber.begin());
		if (*ptr==cSUB)
			ptr++;
		while (ptr!=out::snumber.end()) {
			if (isOperation(*ptr)||*ptr==0x0||*ptr=='.'||*ptr=='#') {
				out::snumber="FATAL ERROR";
				errorf=true;
				break;
			}
			ptr++;
		}
	}

	if (errorf) {
		std::basic_string <char> s(out::snumber);
		reset_data();
		out::snumber=s;
		preActiveEqual(1)=false;
		preActiveOperation(1)=false;
		preActiveDigit(1)=false;
		keylockFlag=true;
		errorf=false;
	}

	return;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#endif
