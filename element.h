#ifndef ELEMENT_H
#define ELEMENT_H

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

#endif
