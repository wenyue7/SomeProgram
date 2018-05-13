//本例程文件为参照资料有：

//OpenCV计算机视觉编程攻略（第二版）学习时的练习文件  作者：[加]Robert Laganiere 著 相银初 译  对应第一章（图像的基本操作）和第二章（像素值的访问）


/* ==========================零散知识点==============================
data属性表示内存块的第一个元素的地址，它会返回一个无符号字符型指针

迭代器:
定义方法：MatIterator_<Vec3b> a;
	或Mat_<Vec3b>::iterator a;  //此处为在Mat_模板类内部定义的iterator

获得某个函数（或代码段）的运行时间：
const int64 start = getTickCount();         //getTickCount函数返回从最近一次电脑开机到当前的时钟周期数
colorReduce(image);                         //运行相关程序
double duration = (getTickCount() - start) / getTickFrequency(); //getTickFrequency返回每秒的时钟周期数
*/

#include "mysample.h"

int main()
{
	const int64 start = getTickCount();  //程序开始计时

	Mat image, result;
	image = imread("image.png",CV_LOAD_IMAGE_COLOR);
	if( image.empty() )
	{
	  cout << "Read image error" << endl;
	  return 1;
	}

	//测试矩阵的连续性,或者说有没有被填充
	if(image.isContinuous())
	cout << "法一判连续：矩阵连续" << endl;
	if(image.step == image.cols * image.elemSize())
	cout << "法二判连续：矩阵连续" << endl;
	//将矩阵变为m通道，n行
	//image.reshape(1,1);
	cout << endl;



//图像读取，显示，兴趣区域（第一章）

	//反转及显示
	//flip(image, result, -1);
	//imshow("Linux_pen_result", result);

	//图像复制
	//Mat backup;
	//backup = image.clone();  //深复制
	//image.copyTo(backup);    //深复制
	//backup = image;          //浅复制
	image.copyTo(result);

	//画圆
	//circle(image,Point(600,400),50,2,3,8);

	//插入文字
	//putText(image,"This is linux",Point(600,400),FONT_HERSHEY_PLAIN,5.0,Scalar(255,255,255),3);

	//定义ROI区域
	//Mat logo;
	//logo = imread("wechat.png");
	//Mat imageROI(image,Range(200,200+logo.rows),Range(300,300+logo.cols));
	//logo.copyTo(imageROI);



//操作像素（第二章）

	//利用椒盐函数添加噪点
	salt(result,8000);
	//imshow("salt",result);

	//利用指针操作像素,减色函数
	//colorReduce(image, 32);
	//colorReduce2(image, 32);
	//colorReduce3(image, result, 128);

	//利用迭代器遍历，迭代器是一种类，专门用于遍历集合的每个元素，OpenCV也提供了cv::Mat的迭代器类，并且与C++STL中的迭代器兼容
	//colorReduce4(image,128);

	//扫描图像并访问相邻像素
	//sharpen(image, result);

	//图像重映射
	//wave(image, result);


	//end



	//显示图像image
	//imshow("backup", backup);
	//imshow("Linux_Image",image);
	cout << "Image information" << endl;
	cout << "行 x 列 ：" << image.rows << " x " << image.cols << endl;//输出像素行数和列数
	cout << "有效宽度：" << image.step << endl;//以字节为单位输出图像的有效宽度(包括填充像素)
	cout << "像素大小：" << image.elemSize() << endl;//获得像素大小
	cout << "通道数量：" << image.channels() << endl;//获得图像中通道的数量
	cout << "像素总数：" << image.total() << endl;//获得矩阵中的像素（即矩阵的条目）总数
	cout << endl;

	//显示图像result
	imshow("Linux_Result",result);
	cout << "Result information" << endl;
	cout << "行 x 列 ：" << image.rows << " x " << image.cols << endl;//输出像素行数和列数
	cout << "有效宽度：" << image.step << endl;//以字节为单位输出图像的有效宽度(包括填充像素)
	cout << "像素大小：" << image.elemSize() << endl;//获得像素大小
	cout << "通道数量：" << image.channels() << endl;//获得图像中通道的数量
	cout << "像素总数：" << image.total() << endl;//获得矩阵中的像素（即矩阵的条目）总数

	double duration = (getTickCount() - start) / getTickFrequency(); //程序运行时间计算
	cout << "程序用时：" << duration << "s" << endl;

	waitKey(0);

	return 0;
}

