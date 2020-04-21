#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "element.h"
using namespace std;
using namespace cv;

void print(Element *a, int n);
void maxmin(Element *a, int n, int& max, int& min);
void record(Mat &M, Element* a, int n, string name, int delay);
void maxmin(Element *a, int n, int& max, int& min);
void lift(Element* a, int n, int min);
void shuffle(Element* a, int size, int times, Mat& M);
void shuffle2(Element* a, int size, int times, Mat& M);

int main(int argc, char** argv){
	namedWindow("hello", WINDOW_NORMAL);
	resizeWindow("hello", 300, 300);
	RNG rng(0xFFFFFFFF);
	const int size = 50;
	Element a[size];
	for(int i = 0; i < size; i++){
		a[i].setValue(i);
		a[i].setBlue(rng.uniform(0,255));
		a[i].setGreen(rng.uniform(0,255));
		a[i].setRed(rng.uniform(0,255));

	}
	const int times = 100;
	Mat M = Mat(500, 700, CV_8UC3, Scalar(10, 10, 10));
	shuffle2(a, size, times, M);
	cout<<"Numbers before sort"<<endl;
	print(a, size);

	Element temp;
	bool flag = 1;
	int count = 0;
	while(flag){
		cout<<"After "<<count<<" iterations a is "<<endl;
		print(a, size);
		count++;
		flag = 0;
		for(int i = 1; i < size; i++){
			if(a[i].getValue() < a[i-1].getValue()){
				flag = 1;
				temp = a[i];
				a[i] = a[i-1];
				a[i-1] = temp;
			}
			record(M, a, size, "hello", 20);
		}
	}
	cout<<"Numbers after sort"<<endl;
	print(a, size);
}

void print(Element *a, int n){
	for(int i = 0; i < n; i++)
		cout<<a[i].getValue()<<" ";
	cout<<endl;
}

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

void shuffle(Element* a, int size, int times, Mat& M){
	RNG rng(0xFFFFFFFF);
	Element temp;
	int breakIndex;
	int delay = 1000;
	record(M, a, size, "hello", delay);
	for(int i = 0; i < times; i++){
		breakIndex = rng.uniform(0,size-1);
		for(int j = breakIndex; j < size; j++){
			temp = a[j];
			a[j] = a[j-breakIndex];
			a[j-breakIndex] = temp;
			record(M, a, size, "hello", 500);
		}
		if(i < times/10)
			delay = 1000;
		else
			delay = 50;
		record(M, a, size, "hello", delay);
	}
}

void shuffle2(Element* a, int size, int times, Mat& M){
	RNG rng(0xFFFFFFFF);
	Element temp;
	int breakIndexLeft;
	int breakIndexRight;
	int delay = 1000;
	record(M, a, size, "hello", delay);
	for(int k = 0; k < times; k++){
		breakIndexLeft = rng.uniform(0,size/2);
		breakIndexRight = rng.uniform(size/2 + 1, size-1);
		for(int i = breakIndexLeft; i < breakIndexRight; i++){
			temp = a[breakIndexLeft];
			for(int j = breakIndexLeft+1; j < size; j++){
				a[j-1] = a[j];
			}
			a[size-1] = temp;
			//record(M, a, size, "hello", 500);
		}
		if(k < times/10)
			delay = 1000;
		else
			delay = 50;
		record(M, a, size, "hello", delay);
	}
}