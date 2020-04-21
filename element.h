#include <opencv2/core/core.hpp>

class Element{
	private:
		uchar blue, green, red;
		int value;
	public:
		Element();
		Element(int invalue, uchar inblue, uchar ingreen, uchar inred);
		uchar getBlue();
		uchar getGreen();
		uchar getRed();
		int getValue();
		void setValue(int in);
		void setBlue(uchar bl);
		void setGreen(uchar gr);
		void setRed(uchar rd);
};
Element::Element(){
	blue = 10;
	green = 10;
	green = 10;
	value = 10;
}
Element::Element(int invalue, uchar inblue, uchar ingreen, uchar inred){
	value = invalue;
	blue = inblue;
	green = ingreen;
	red = inred;
}

uchar Element::getBlue(){
	return blue;
}

uchar Element::getGreen(){
	return green;
}

uchar Element::getRed(){
	return red;
}
void Element::setValue(int in){
	value = in;
}
void Element::setBlue(uchar bl){
	blue = bl;
}
void Element::setGreen(uchar gr){
	green = gr;
}
void Element::setRed(uchar rd){
	red = rd;
}

int Element::getValue(){
	return value;
}
