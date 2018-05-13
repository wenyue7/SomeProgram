#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

main()
{
	Mat M(3,2,CV_8UC3,Scalar(0,0,255));
	Mat Z = Mat::zeros(2,3,CV_8UC1);
	Mat O = Mat::ones(2,3,CV_32F);
	Mat E = Mat::eye(2,3,CV_64F);

	cout << "M = " << endl << " " << M << endl;
	cout << "z = " << endl << " " << Z << endl;
	cout << "O = " << endl << " " << O << endl;
	cout << "E = " << endl << " " << E << endl;
	return 0;
}
