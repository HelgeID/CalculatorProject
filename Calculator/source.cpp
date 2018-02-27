/*EN This program is for training and testing, so it works on the principle of "as is"!*/
/*RU Эта программа представляет собой обучение и тестирование, поэтому работает по принципу "как есть"!*/
/*UA Ця програма являє собою навчання і тестування, тому працює за принципом "як є"!*/

#include <vector>
#include <graphics.h>
#include "calculations.h"
using std::string;

unsigned int FRegister(0);

class Button
{
	private:
		int posX1, posY1;
		int posX2, posY2;
		unsigned int color_frame;
		unsigned int color_inside;
		friend int take_posX1(Button&);
		friend int take_posY1(Button&);
		friend int take_posX2(Button&);
		friend int take_posY2(Button&);

	public:
		Button(int, int, int, int, unsigned int, unsigned int);
		void draw_button(unsigned int, unsigned int);
		void draw_button_title(int, unsigned int, bool);
		~Button(void);
};

int take_posX1(Button& obj) {
	return obj.posX1;
}

int take_posY1(Button& obj) {
	return obj.posY1;
}

int take_posX2(Button& obj) {
	return obj.posX2;
}

int take_posY2(Button& obj) {
	return obj.posY2;
}

Button::Button(int posX1, int posY1, int posX2, int posY2, unsigned int color_frame=DARKGRAY, unsigned int color_inside=DARKGRAY)
{
	this->posX1=posX1;
	this->posY1=posY1;
	this->posX2=posX2;
	this->posY2=posY2;
	this->color_frame=color_frame;
	this->color_inside=color_inside;
}

void Button::draw_button(unsigned int _color_frame=NULL, unsigned int _color_inside=NULL)
{
	unsigned int color_default=getcolor();
	int _posX1, _posY1, _posX2, _posY2;
	int number_lines((posY2-posY1)-1);
	if (_color_frame)
	{
	} else
		_color_frame=color_frame;
	setcolor(_color_frame);
	rectangle(posX1,posY1,posX2,posY2);
	_posX1=posX1+1;
	_posY1=posY1+1;
	_posX2=posX2-1;
	_posY2=posY2-number_lines;
	if (_color_inside)
	{
	} else
		_color_inside=color_inside;
	setcolor(_color_inside);
	int i=0;
	while(i<number_lines) {
		line(_posX1,_posY1+i,_posX2,_posY2+i);
		i=i+1;
	}
	setcolor(color_default);
	return;
}

void Button::draw_button_title(int indx, unsigned int _color_title=LIGHTGRAY, bool bk_click=false)
{
	char* title_table[]={
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
		",", "+", "-", "*", "/", "±", "=", "1/", "%", "SQ",
		"←", "CE", "C", "MC", "MR", "MS", "M+", "M-"
	};
	
	/*
		init color
	*/
	unsigned int color_default(getcolor());
	setcolor(COLOR(128,128,128));
	unsigned int color_background(getcolor());
	!bk_click?setbkcolor(color_background):setbkcolor(LIGHTGRAY);
	setcolor(_color_title);
	
	/*
		draw title
	*/
	int poscX=(posX1+((posX2-posX1)/2));
	int poscY=(posY1+((posY2-posY1)/2));
	
	char msg[3];
	settextjustify(CENTER_TEXT, VCENTER_TEXT);
	
	if (indx==20) {
		char* ptr;
		char symbol[2];
		symbol[1]='\0';//end line
		*(symbol+0)=0x1b;
		ptr=&symbol[0];
		sprintf(msg, "%s", ptr);
	} else
		sprintf(msg, "%s", title_table[indx]);
	outtextxy(poscX+1, poscY+5, msg);
	setcolor(color_default);
	setbkcolor(0);
	return;
}

Button::~Button(void)
{
}

class cButton:public Button
{
	public:
		cButton(int posX1, int posY1, int posX2, int posY2):Button(posX1, posY1, posX2, posY2) {
		}
		void passive(int indx) {draw_button(); draw_button_title(indx);};
		void active(int indx)  {draw_button(DARKGRAY); draw_button_title(indx, WHITE);};
		void pressed(int indx) {draw_button(WHITE, LIGHTGRAY); draw_button_title(indx, WHITE, true);};
		~cButton(void) {
		}
};

class Calculator
{
	private:
		string number;//-0,1234567890123

	public:
		friend bool find_space_buttonONE(int, int);
		friend bool find_space_buttonTWO(int, int);
		friend bool find_space_buttonTHREE(int, int);
		friend bool find_space_buttonFOUR(int, int);
		friend bool find_space_buttonFIVE(int, int);
		friend bool find_space_buttonSIX(int, int);
		friend bool find_space_buttonSEVEN(int, int);
		friend bool find_space_buttonEIGHT(int, int);
		friend bool find_space_buttonNINE(int, int);
		friend bool find_space_buttonZERO(int, int);
		friend bool find_space_buttonPOINT(int, int);
		friend bool find_space_buttonADD(int, int);
		friend bool find_space_buttonSUB(int, int);
		friend bool find_space_buttonMUL(int, int);
		friend bool find_space_buttonDIV(int, int);
		friend bool find_space_buttonSIGN(int, int);
		friend bool find_space_buttonEQUAL(int, int);
		friend bool find_space_buttonRECIPROC(int, int);
		friend bool find_space_buttonPERCENT(int, int);
		friend bool find_space_buttonSQRT(int, int);
		friend bool find_space_buttonBACK(int, int);
		friend bool find_space_buttonCE(int, int);
		friend bool find_space_buttonC(int, int);
		friend bool find_space_buttonMC(int, int);
		friend bool find_space_buttonMR(int, int);
		friend bool find_space_buttonMS(int, int);
		friend bool find_space_buttonMPLUS(int, int);
		friend bool find_space_buttonMMINUS(int, int);
		
	public:
		std::vector<cButton> vecButton;
		int fCheck;
		bool (*ARRAY_fsb[28])(int, int);
		void processing_clicks();
		void click_HNDLR(int, int, int*);
		void move_HNDLR(int, int);

		struct MESSAGE {
			int posX, posY;
			char* msg;
		} *pmsg;

		MESSAGE operation_message;
		MESSAGE memory_message;

		Calculator(void):fCheck(0), number("0")
		{
			int i(0);
			ARRAY_fsb[i++]=find_space_buttonONE;
			ARRAY_fsb[i++]=find_space_buttonTWO;
			ARRAY_fsb[i++]=find_space_buttonTHREE;
			ARRAY_fsb[i++]=find_space_buttonFOUR;
			ARRAY_fsb[i++]=find_space_buttonFIVE;
			ARRAY_fsb[i++]=find_space_buttonSIX;
			ARRAY_fsb[i++]=find_space_buttonSEVEN;
			ARRAY_fsb[i++]=find_space_buttonEIGHT;
			ARRAY_fsb[i++]=find_space_buttonNINE;
			ARRAY_fsb[i++]=find_space_buttonZERO;
			ARRAY_fsb[i++]=find_space_buttonPOINT;
			ARRAY_fsb[i++]=find_space_buttonADD;
			ARRAY_fsb[i++]=find_space_buttonSUB;
			ARRAY_fsb[i++]=find_space_buttonMUL;
			ARRAY_fsb[i++]=find_space_buttonDIV;
			ARRAY_fsb[i++]=find_space_buttonSIGN;
			ARRAY_fsb[i++]=find_space_buttonEQUAL;
			ARRAY_fsb[i++]=find_space_buttonRECIPROC;
			ARRAY_fsb[i++]=find_space_buttonPERCENT;
			ARRAY_fsb[i++]=find_space_buttonSQRT;
			ARRAY_fsb[i++]=find_space_buttonBACK;
			ARRAY_fsb[i++]=find_space_buttonCE;
			ARRAY_fsb[i++]=find_space_buttonC;
			ARRAY_fsb[i++]=find_space_buttonMC;
			ARRAY_fsb[i++]=find_space_buttonMR;
			ARRAY_fsb[i++]=find_space_buttonMS;
			ARRAY_fsb[i++]=find_space_buttonMPLUS;
			ARRAY_fsb[i++]=find_space_buttonMMINUS;
		}
		~Calculator(void)
		{
		}
		string getNumber() {
			return (this->number);
		}
		void setNumber(string number) {
			this->number=number;
			return;
		}
		
		void background();
		void drawingDisplay(int, int, int, int);
		void drawingNumber(const int, const int);
		void initOperationMsg();
		void initMemoryMsg();
		void drawingMsg(MESSAGE**);
		void initialize_elements();
};

void Calculator::processing_clicks()
{
	vecButton[fCheck-1].pressed(fCheck-1);
//	for (int i(0); i<28; i++) {
//		if (i!=fCheck-1) {
//			vecButton[i].passive(i);
//		}
//	}
	delay(150);
	vecButton[fCheck-1].active(fCheck-1);
	fCheck=0;
	return;
}

void Calculator::click_HNDLR(int X, int Y, int *FCheck)
{
	for (int i(0); i<28; i++) {
		if ((*ARRAY_fsb[i])(X,Y)!=NULL) {
			*FCheck=i+1;
			::FRegister=*FCheck;
			break;
		}
	}
	return;
}

void Calculator::move_HNDLR(int X, int Y)
{
	if (!fCheck) {
		for (int i(0); i<28; i++) {
			if ((*ARRAY_fsb[i])(X,Y)!=NULL)
				vecButton[i].active(i);
			else {
				delay(3);
				vecButton[i].passive(i);
			}
		}
	}
	return;
}

void Calculator::background()
{
	unsigned int color_default(getcolor());
	setcolor(COLOR(195,195,195));
	setfillstyle(SOLID_FILL, getcolor());
	bar(0,0,212,284);
	setcolor(DARKGRAY);
	line(0,18,212,18);
	setcolor(color_default);
	setfillstyle(SOLID_FILL, color_default);
	return;
}

void Calculator::drawingDisplay(const int posX1=11, const int posY1=30, const int posX2=200, const int posY2=79)
{
	unsigned int color_default, color_display;
	color_default=getcolor();
	setcolor(COLOR(163,73,164));
	color_display=getcolor();
	if (IS_RGB_COLOR(color_display))
		setfillstyle(SOLID_FILL, color_display);
	bar(posX1, posY1, posX2, posY2);
	setcolor(color_default);
	setfillstyle(SOLID_FILL, color_default);
	return;
}

void Calculator::drawingNumber(const int pos_offsetX=0, const int pos_offsetY=0)
{
	/*
		init color
	*/
	unsigned int color_default, color_background;
	color_default=getcolor();
	setcolor(COLOR(163,73,164));
	color_background=getcolor();
	setbkcolor(color_background);
	setcolor(color_default);
	
	/*
		draw number
	*/
	int pos_Start(183);//starting position
	int difference(11);//difference between two symbols
	int pos_Top_Bottom(54);//top-bottom position of the number
	string strNumber=getNumber();
	size_t lenNumber=strNumber.length();
	int index(lenNumber);
	while (index--)
		pos_Start-=difference;
	char* ptr;
	char symbol[2];
	symbol[1]='\0';//end line
	for (int i=0; i<lenNumber; i++, pos_Start+=difference) {
		symbol[0]=strNumber[i];
		ptr=&symbol[0];
		outtextxy(11+pos_Start+pos_offsetX, pos_Top_Bottom+pos_offsetY, ptr);
	}
	setbkcolor(0);
	return;
}

void Calculator::initOperationMsg()
{
	if (out::operation_msg=="ADD"||out::operation_msg=="SUB"||out::operation_msg=="MUL"||out::operation_msg=="DIV") {
		operation_message.posX=180; operation_message.posY=45;
	}
	else
	if (out::operation_msg=="EQUAL") {
		operation_message.posX=169; operation_message.posY=45;
	}
	else {
		if (out::operation_msg=="") {
			operation_message.posX=-1; operation_message.posY=-1;
		}
	}
	operation_message.msg=out::operation_msg;
	pmsg=&operation_message;
	return;
}

void Calculator::initMemoryMsg()
{
	if (out::memory_msg=="M") {
		memory_message.posX=25; memory_message.posY=45;
	}
	else {
		if (out::memory_msg=="") {
			memory_message.posX=-1; memory_message.posY=-1;
		}
	}
	memory_message.msg=out::memory_msg;
	pmsg=&memory_message;
	return;
}

void Calculator::drawingMsg(MESSAGE** message)
{
	/*
		init color
	*/
	unsigned int color_default, color_background;
	color_default=getcolor();
	setcolor(COLOR(163,73,164));
	color_background=getcolor();
	setbkcolor(color_background);
	setcolor(color_default);

	/*
		draw msg
	*/
	outtextxy((*message)->posX, (*message)->posY, (*message)->msg);
	setbkcolor(0);
	return;
}

void Calculator::initialize_elements()
{
	//init text style
	int style=COMPLEX_FONT;
	const size_t size(1);
	settextstyle(style, HORIZ_DIR, size);
	
	//init background
	background();
	
	//init display
	drawingDisplay();
	
	//init number
	drawingNumber();
	
	//init msg
	initOperationMsg(); drawingMsg(&pmsg);
	initMemoryMsg(); drawingMsg(&pmsg);

	//init buttons
	int i(EOF);
	cButton objButtonONE(11,213,44,239); 		vecButton.insert(vecButton.end(), objButtonONE);		vecButton[++i].passive(i);
	cButton objButtonTWO(50,213,83,239); 		vecButton.insert(vecButton.end(), objButtonTWO);		vecButton[++i].passive(i);
	cButton objButtonTHREE(89,213,122,239); 	vecButton.insert(vecButton.end(), objButtonTHREE);		vecButton[++i].passive(i);
	cButton objButtonFOUR(11,181,44,207); 		vecButton.insert(vecButton.end(), objButtonFOUR);		vecButton[++i].passive(i);
	cButton objButtonFIVE(50,181,83,207); 		vecButton.insert(vecButton.end(), objButtonFIVE);		vecButton[++i].passive(i);
	cButton objButtonSIX(89,181,122,207); 		vecButton.insert(vecButton.end(), objButtonSIX);		vecButton[++i].passive(i);
	cButton objButtonSEVEN(11,149,44,175); 		vecButton.insert(vecButton.end(), objButtonSEVEN);		vecButton[++i].passive(i);
	cButton objButtonEIGHT(50,149,83,175); 		vecButton.insert(vecButton.end(), objButtonEIGHT);		vecButton[++i].passive(i);
	cButton objButtonNINE(89,149,122,175); 		vecButton.insert(vecButton.end(), objButtonNINE);		vecButton[++i].passive(i);
	cButton objButtonZERO(11,245,83,271); 		vecButton.insert(vecButton.end(), objButtonZERO);		vecButton[++i].passive(i);
	cButton objButtonPOINT(89,245,122,271); 	vecButton.insert(vecButton.end(), objButtonPOINT);		vecButton[++i].passive(i);
	cButton objButtonADD(128,245,161,271); 		vecButton.insert(vecButton.end(), objButtonADD);		vecButton[++i].passive(i);
	cButton objButtonSUB(128,213,161,239); 		vecButton.insert(vecButton.end(), objButtonSUB);		vecButton[++i].passive(i);
	cButton objButtonMUL(128,181,161,207); 		vecButton.insert(vecButton.end(), objButtonMUL);		vecButton[++i].passive(i);
	cButton objButtonDIV(128,149,161,175); 		vecButton.insert(vecButton.end(), objButtonDIV);		vecButton[++i].passive(i);
	cButton objButtonSIGN(128,117,161,143); 	vecButton.insert(vecButton.end(), objButtonSIGN);		vecButton[++i].passive(i);
	cButton objButtonEQUAL(167,213,200,271); 	vecButton.insert(vecButton.end(), objButtonEQUAL);		vecButton[++i].passive(i);
	cButton objButtonRECIPROC(167,181,200,207);	vecButton.insert(vecButton.end(), objButtonRECIPROC);	vecButton[++i].passive(i);
	cButton objButtonPERCENT(167,149,200,175);	vecButton.insert(vecButton.end(), objButtonPERCENT);	vecButton[++i].passive(i);
	cButton objButtonSQRT(167,117,200,143);		vecButton.insert(vecButton.end(), objButtonSQRT);		vecButton[++i].passive(i);
	cButton objButtonBACK(11,117,44,143);		vecButton.insert(vecButton.end(), objButtonBACK);		vecButton[++i].passive(i);
	cButton objButtonCE(50,117,83,143);			vecButton.insert(vecButton.end(), objButtonCE);			vecButton[++i].passive(i);
	cButton objButtonC(89,117,122,143);			vecButton.insert(vecButton.end(), objButtonC);			vecButton[++i].passive(i);
	cButton objButtonMC(11,85,44,111);			vecButton.insert(vecButton.end(), objButtonMC);			vecButton[++i].passive(i);
	cButton objButtonMR(50,85,83,111);			vecButton.insert(vecButton.end(), objButtonMR);			vecButton[++i].passive(i);
	cButton objButtonMS(89,85,122,111);			vecButton.insert(vecButton.end(), objButtonMS);			vecButton[++i].passive(i);
	cButton objButtonMPLUS(128,85,161,111);		vecButton.insert(vecButton.end(), objButtonMPLUS);		vecButton[++i].passive(i);
	cButton objButtonMMINUS(167,85,200,111);	vecButton.insert(vecButton.end(), objButtonMMINUS);		vecButton[++i].passive(i);
	return;
}

/*////////////////////////////////////////////////////////////////////////////////
	Initialization objects!!!
*/////////////////////////////////////////////////////////////////////////////////
Calculations objCalculations;
Calculator objCalculator;
//////////////////////////////////////////////////////////////////////////////////

//Find Space Button #1
bool find_space_buttonONE(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[0])&&x<take_posX2(objCalculator.vecButton[0]))&&(y>take_posY1(objCalculator.vecButton[0])&&y<take_posY2(objCalculator.vecButton[0])))
		return true;
	return false;
}

//Find Space Button #2
bool find_space_buttonTWO(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[1])&&x<take_posX2(objCalculator.vecButton[1]))&&(y>take_posY1(objCalculator.vecButton[1])&&y<take_posY2(objCalculator.vecButton[1])))
		return true;
	return false;
}

//Find Space Button #3
bool find_space_buttonTHREE(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[2])&&x<take_posX2(objCalculator.vecButton[2]))&&(y>take_posY1(objCalculator.vecButton[2])&&y<take_posY2(objCalculator.vecButton[2])))
		return true;
	return false;
}

//Find Space Button #4
bool find_space_buttonFOUR(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[3])&&x<take_posX2(objCalculator.vecButton[3]))&&(y>take_posY1(objCalculator.vecButton[3])&&y<take_posY2(objCalculator.vecButton[3])))
		return true;
	return false;
}

//Find Space Button #5
bool find_space_buttonFIVE(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[4])&&x<take_posX2(objCalculator.vecButton[4]))&&(y>take_posY1(objCalculator.vecButton[4])&&y<take_posY2(objCalculator.vecButton[4])))
		return true;
	return false;
}

//Find Space Button #6
bool find_space_buttonSIX(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[5])&&x<take_posX2(objCalculator.vecButton[5]))&&(y>take_posY1(objCalculator.vecButton[5])&&y<take_posY2(objCalculator.vecButton[5])))
		return true;
	return false;
}

//Find Space Button #7
bool find_space_buttonSEVEN(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[6])&&x<take_posX2(objCalculator.vecButton[6]))&&(y>take_posY1(objCalculator.vecButton[6])&&y<take_posY2(objCalculator.vecButton[6])))
		return true;
	return false;
}

//Find Space Button #8
bool find_space_buttonEIGHT(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[7])&&x<take_posX2(objCalculator.vecButton[7]))&&(y>take_posY1(objCalculator.vecButton[7])&&y<take_posY2(objCalculator.vecButton[7])))
		return true;
	return false;
}

//Find Space Button #9
bool find_space_buttonNINE(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[8])&&x<take_posX2(objCalculator.vecButton[8]))&&(y>take_posY1(objCalculator.vecButton[8])&&y<take_posY2(objCalculator.vecButton[8])))
		return true;
	return false;
}

//Find Space Button #10
bool find_space_buttonZERO(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[9])&&x<take_posX2(objCalculator.vecButton[9]))&&(y>take_posY1(objCalculator.vecButton[9])&&y<take_posY2(objCalculator.vecButton[9])))
		return true;
	return false;
}

//Find Space Button #11
bool find_space_buttonPOINT(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[10])&&x<take_posX2(objCalculator.vecButton[10]))&&(y>take_posY1(objCalculator.vecButton[10])&&y<take_posY2(objCalculator.vecButton[10])))
		return true;
	return false;
}

//Find Space Button #12
bool find_space_buttonADD(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[11])&&x<take_posX2(objCalculator.vecButton[11]))&&(y>take_posY1(objCalculator.vecButton[11])&&y<take_posY2(objCalculator.vecButton[11])))
		return true;
	return false;
}

//Find Space Button #13
bool find_space_buttonSUB(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[12])&&x<take_posX2(objCalculator.vecButton[12]))&&(y>take_posY1(objCalculator.vecButton[12])&&y<take_posY2(objCalculator.vecButton[12])))
		return true;
	return false;
}

//Find Space Button #14
bool find_space_buttonMUL(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[13])&&x<take_posX2(objCalculator.vecButton[13]))&&(y>take_posY1(objCalculator.vecButton[13])&&y<take_posY2(objCalculator.vecButton[13])))
		return true;
	return false;
}

//Find Space Button #15
bool find_space_buttonDIV(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[14])&&x<take_posX2(objCalculator.vecButton[14]))&&(y>take_posY1(objCalculator.vecButton[14])&&y<take_posY2(objCalculator.vecButton[14])))
		return true;
	return false;
}

//Find Space Button #16
bool find_space_buttonSIGN(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[15])&&x<take_posX2(objCalculator.vecButton[15]))&&(y>take_posY1(objCalculator.vecButton[15])&&y<take_posY2(objCalculator.vecButton[15])))
		return true;
	return false;
}

//Find Space Button #17
bool find_space_buttonEQUAL(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[16])&&x<take_posX2(objCalculator.vecButton[16]))&&(y>take_posY1(objCalculator.vecButton[16])&&y<take_posY2(objCalculator.vecButton[16])))
		return true;
	return false;
}

//Find Space Button #18
bool find_space_buttonRECIPROC(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[17])&&x<take_posX2(objCalculator.vecButton[17]))&&(y>take_posY1(objCalculator.vecButton[17])&&y<take_posY2(objCalculator.vecButton[17])))
		return true;
	return false;
}

//Find Space Button #19
bool find_space_buttonPERCENT(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[18])&&x<take_posX2(objCalculator.vecButton[18]))&&(y>take_posY1(objCalculator.vecButton[18])&&y<take_posY2(objCalculator.vecButton[18])))
		return true;
	return false;
}

//Find Space Button #20
bool find_space_buttonSQRT(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[19])&&x<take_posX2(objCalculator.vecButton[19]))&&(y>take_posY1(objCalculator.vecButton[19])&&y<take_posY2(objCalculator.vecButton[19])))
		return true;
	return false;
}

//Find Space Button #21
bool find_space_buttonBACK(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[20])&&x<take_posX2(objCalculator.vecButton[20]))&&(y>take_posY1(objCalculator.vecButton[20])&&y<take_posY2(objCalculator.vecButton[20])))
		return true;
	return false;
}

//Find Space Button #22
bool find_space_buttonCE(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[21])&&x<take_posX2(objCalculator.vecButton[21]))&&(y>take_posY1(objCalculator.vecButton[21])&&y<take_posY2(objCalculator.vecButton[21])))
		return true;
	return false;
}

//Find Space Button #23
bool find_space_buttonC(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[22])&&x<take_posX2(objCalculator.vecButton[22]))&&(y>take_posY1(objCalculator.vecButton[22])&&y<take_posY2(objCalculator.vecButton[22])))
		return true;
	return false;
}

//Find Space Button #24
bool find_space_buttonMC(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[23])&&x<take_posX2(objCalculator.vecButton[23]))&&(y>take_posY1(objCalculator.vecButton[23])&&y<take_posY2(objCalculator.vecButton[23])))
		return true;
	return false;
}

//Find Space Button #25
bool find_space_buttonMR(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[24])&&x<take_posX2(objCalculator.vecButton[24]))&&(y>take_posY1(objCalculator.vecButton[24])&&y<take_posY2(objCalculator.vecButton[24])))
		return true;
	return false;
}

//Find Space Button #26
bool find_space_buttonMS(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[25])&&x<take_posX2(objCalculator.vecButton[25]))&&(y>take_posY1(objCalculator.vecButton[25])&&y<take_posY2(objCalculator.vecButton[25])))
		return true;
	return false;
}

//Find Space Button #27
bool find_space_buttonMPLUS(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[26])&&x<take_posX2(objCalculator.vecButton[26]))&&(y>take_posY1(objCalculator.vecButton[26])&&y<take_posY2(objCalculator.vecButton[26])))
		return true;
	return false;
}

//Find Space Button #28
bool find_space_buttonMMINUS(int x, int y) {
	if ((x>take_posX1(objCalculator.vecButton[27])&&x<take_posX2(objCalculator.vecButton[27]))&&(y>take_posY1(objCalculator.vecButton[27])&&y<take_posY2(objCalculator.vecButton[27])))
		return true;
	return false;
}

//link to function "click_HNDLR", works online
void click_HNDLR_label(int x, int y) {
	objCalculator.click_HNDLR(x, y, &objCalculator.fCheck);
	return;
}

//link to function "move_HNDLR", works online
void move_HNDLR_label(int x, int y) {
	objCalculator.move_HNDLR(x, y);
	return;
}

void update_display()
{
	objCalculator.setNumber(out::snumber);
	objCalculator.drawingDisplay();
	objCalculator.drawingNumber(0x6, 0xE);

	objCalculator.initOperationMsg();
	objCalculator.drawingMsg(&objCalculator.pmsg);
	objCalculator.initMemoryMsg();
	objCalculator.drawingMsg(&objCalculator.pmsg);

	FRegister=0;
	return;
}

int main()
{
	int wid(initwindow(212, 284, "Calculator", 128, 128));
	setcurrentwindow(wid);
	cleardevice();
	objCalculator.initialize_elements();
	registermousehandler(WM_LBUTTONDOWN, click_HNDLR_label);
	registermousehandler(WM_MOUSEMOVE, move_HNDLR_label);
	update_display();

	//clicks history is logged in the console
	//comment out the function FreeConsole()
	FreeConsole();
	
	bool repeat(true);
	while (repeat) {
		if (!objCalculator.fCheck)
			delay(180);
		else
			objCalculator.processing_clicks();

		if (FRegister) {
			switch (FRegister) {
				case 1:		objCalculations.ONE_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("1");		break;
				case 2:		objCalculations.TWO_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("2");		break;
				case 3:		objCalculations.THREE_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("3");		break;
				case 4:		objCalculations.FOUR_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("4");		break;
				case 5:		objCalculations.FIVE_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("5");		break;
				case 6:		objCalculations.SIX_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("6");		break;
				case 7:		objCalculations.SEVEN_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("7");		break;
				case 8:		objCalculations.EIGHT_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("8");		break;
				case 9:		objCalculations.NINE_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("9");		break;
				case 10:	objCalculations.ZERO_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("0");		break;
				case 11:	objCalculations.POINT_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug(",");		break;
				case 12:	objCalculations.ADD_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("+");		break;
				case 13:	objCalculations.SUB_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("-");		break;
				case 14:	objCalculations.MUL_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("*");		break;
				case 15:	objCalculations.DIV_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("/");		break;
				case 16:	objCalculations.SIGN_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("+-");	break;
				case 17:	objCalculations.EQUAL_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("=");		break;
				case 18:	objCalculations.RECIPROC_processing();	objCalculations.ControlDisplay();	update_display();	objCalculations.debug("1/");	break;
				case 19:	objCalculations.PERCENT_processing();	objCalculations.ControlDisplay();	update_display();	objCalculations.debug("%");		break;
				case 20:	objCalculations.SQRT_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("SQ");	break;
				case 21:	objCalculations.BACK_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("←");		break;
				case 22:	objCalculations.CE_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("CE");	break;
				case 23:	objCalculations.C_processing();			objCalculations.ControlDisplay();	update_display();	objCalculations.debug("C");		break;
				case 24:	objCalculations.MC_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("MC");	break;
				case 25:	objCalculations.MR_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("MR");	break;
				case 26:	objCalculations.MS_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("MS");	break;
				case 27:	objCalculations.MPLUS_processing();		objCalculations.ControlDisplay();	update_display();	objCalculations.debug("M+");	break;
				case 28:	objCalculations.MMINUS_processing();	objCalculations.ControlDisplay();	update_display();	objCalculations.debug("M-");	break;
			}
		}
	}
	
	return 0;
}
