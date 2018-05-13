#include <mysample2.h>

using namespace std;
using namespace cv;

int main()
{
	const int64 start = getTickCount();
	Mat image, result;

	image = imread("./image.png",CV_LOAD_IMAGE_COLOR);//8UC3);
	if(image.empty())
	{
	  cout << "Image is empty" << endl;
	  return 1;
	}
	if(image.isContinuous())
	  cout << "Image is continuous" << endl;
	cout << "Image size:" << image.size() << endl;

	result = image(Rect(500,250,700,100));

	imshow("Image",image);
	imshow("Result",result);


	double duration = (getTickCount() - start) / getTickFrequency();//程序运行时间计算
	cout << "程序用时：" << duration << "s" << endl;

	waitKey(0);

	return 0;
}
