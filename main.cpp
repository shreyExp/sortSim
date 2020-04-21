#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "element.h"
#include "record.h"

using namespace std;
using namespace cv;

void print(Element *a, int n);

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


