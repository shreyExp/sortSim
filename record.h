#ifndef  RECORD_H
#define  RECORD_H
#include "element.h"
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
void record(Mat &M, Element* a, int n, string name, int delay);
void maxmin(Element *a, int n, int& max, int& min);
void lift(Element* a, int n, int min);
void record(Mat &M, Element* a, int n, string name, int delay){
	M = Scalar(10, 10, 10);
	int hbuffer = 10;
	int vbuffer = 10;
	int cols = M.cols * M.channels();
	int totalWidth = M.cols - 2* hbuffer;
	int hresidue = totalWidth%n;
	hbuffer += hresidue/2;
	int width = totalWidth/n;
	int totalHeight = M.rows - 3*vbuffer;


	int min, max;
	maxmin(a, n, max, min);

	float vscale = float(totalHeight)/(max - min);
	lift(a, n, min);

	for(int i = 0; i < n; i++){
		rectangle(M,
			Point(hbuffer + i*width, (M.rows-vbuffer)),
			Point(hbuffer + (((i+1)*width)-1), (M.rows-vbuffer) - int(vscale*a[i].getValue())),
			Scalar(a[i].getBlue(),a[i].getGreen(),a[i].getRed()),
			FILLED,
			LINE_8);
	}
	imshow(name, M);
	waitKey(delay);
}

void maxmin(Element *a, int n, int& max, int& min){
	max = a[0].getValue();
	min = a[0].getValue();
	for( int i = 0; i < n; i++){
		if(a[i].getValue() > max)
			max = a[i].getValue();
		if(a[i].getValue() < min)
			min = a[i].getValue();
	}
}

void lift(Element* a, int n, int min){
	if(min < 0){
		for(int i = 0; i < n; i++){
			a[i].setValue(a[i].getValue() - min);
		}
	}
}

#endif
