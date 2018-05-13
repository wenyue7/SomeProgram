#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//椒盐函数，给像素添加噪点
void salt(Mat image,int n)
{
	int i, j;
	for(int k = 0; k < n; k++)
	{
	  //rand()是随机数生成器
	  i = rand()%image.cols;
	  j = rand()%image.rows;

	  if(image.type() == CV_8UC1)
	  {
	    image.at<uchar>(j,i) = 255;
	  }
	  else if (image.type() == CV_8UC3)
	  {
	    image.at<Vec3b>(j,i)[0] = 255;  //这种访问方法一般在随机访问像素时使用，不要再遍历像素时使用
	    image.at<Vec3b>(j,i)[1] = 255;
	    image.at<Vec3b>(j,i)[2] = 255;
	  }
	}
}


//减色函数
void colorReduce(Mat image, int div)
{
	int nl = image.rows;
	int nc = image.cols * image.channels();
	for(int j = 0; j < nl; j++)
	{
	  uchar *data = image.ptr<uchar>(j);     //data属性表示内存块的第一个元素的地址，它会返回一个无符号字符型指针
	  for(int i = 0; i < nc; i++)
	  {
	    data[i] = data[i] / div * div + div / 2;
	  }
	}
}
//方法二，利用位运算
void colorReduce2(Mat image, int div)
{
	int n;
	int nl = image.rows;
	int nc = image.cols * image.channels();
	div = pow(2,n);
	uchar mask = 0xFF << n;
	for(int j = 0; j < nl; j++)
	{
	  
	  uchar *data = image.ptr<uchar>(j);
	  for(int i = 0; i < nc; i++)
	  {
	    *data &= mask;
	    *data++ += div >> 1;
	  }
	}
	
}
//方法三，保留原图像
void colorReduce3(const Mat &image, Mat &result, int div)
{
	int nl = image.rows;
	int nc = image.cols * image.channels();
	result.create(image.rows, image.cols, image.type());
	for(int j = 0; j < nl; j++)
	{
	  const uchar *data_in = image.ptr<uchar>(j);
	  uchar *data_out = result.ptr<uchar>(j);
	  for(int i = 0; i < nc * image.channels(); i++)
	  {
	    data_out[i] = data_in[i] / div * div + div / 2;
	  }
	}
}


//迭代器
//方法四，减色函数，利用迭代器
void colorReduce4(Mat &image, int div)
{
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();  //在初始位置获得迭代器
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();  //在初始位置获得迭代器
	for(; it != itend; ++it)  //循环遍历所有像素
	{
	  (*it)[0] = (*it)[0] / div * div + div / 2;;
	  (*it)[1] = (*it)[0] / div * div + div / 2;;
	  (*it)[2] = (*it)[0] / div * div + div / 2;;
	}
}

//扫描图像并访问相邻像素
void sharpen(const Mat &image, Mat &result)
{
	//判断是否需要分配图像数据
	result.create(image.size(), image.type());
	int channels = image.channels();

	//处理所有行（第一行和最后一行除外）
	for(int j = 1; j < image.rows - 1; j++)
	{
	  const uchar *previous = image.ptr<const uchar>(j - 1);  //上一行
	  const uchar *current = image.ptr<const uchar>(j);       //当前行 
	  const uchar *next = image.ptr<const uchar>(j + 1);      //下一行

	  uchar *output = result.ptr<uchar>(j);                  //输出行

	  for(int i = channels; i < (image.cols - 1) * channels; i++)
	  {
	    *output++ = saturate_cast<uchar>(5 * current[i] - current[i - channels] - current[i + channels] - previous[i] - next[i]);
	  }
	}

	//把未处理的像素设为
	result.row(0).setTo(Scalar(0));
	result.row(result.rows - 1).setTo(Scalar(0));
	result.col(0).setTo(Scalar(0));
	result.col(result.cols - 1).setTo(Scalar(0));
}

//图像重映射
void wave(const Mat &image, Mat &result)
{
	//映射参数
	Mat srcX(image.rows, image.cols, CV_32F);
	Mat srcY(image.rows, image.cols, CV_32F);

	//创建映射参数
	for(int i = 0 ; i < image.rows; i++)
	{
	  for(int j = 0; j < image.cols; j++)
	  {
	    //(i,j)像素的新位置
	    srcX.at<float>(i, j) = j;  //保持在同一列
	    srcY.at<float>(i, j) = i + 5 * sin(j / 10.0); //原来在第i行的像素，现在根据一个正弦曲线移动
	  }
	}
	//应用映射参数
	remap(image, result, srcX, srcY, INTER_LINEAR);
}
