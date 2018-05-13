#ifndef MYSAMPLE_H
#define MYSAMPLE_H

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void salt(Mat image,int n);                                       //椒盐函数声明
void colorReduce(Mat image, int div = 64);                        //减色函数声明
void colorReduce2(Mat image, int div);                            //减色函数法二声明
void colorReduce3(const Mat &image, Mat &result, int div = 6);    //减色函数法三声明
void colorReduce4(Mat &image, int div = 64);                      //减色函数法四声明
void sharpen(const Mat &image, Mat &result);                      //扫描图像并访问相邻像素
void wave(const Mat &image, Mat &result);                         //图像重映射



#endif
