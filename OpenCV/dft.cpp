#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
//***********calculate runing time**********//
    const int64 start = getTickCount();
    Mat image, image2, imageROI, result;

//**********read two picturs****************//
    image = imread("./Color.jpeg", 0);//CV_LOAD_IMAGE_COLOR);//8UC3);
    if(image.empty())
    {
      cout << "Image is empty" << endl;
      return 1;
    }
    if(image.isContinuous())
      cout << "Image is continuous" << endl;
    cout << "Image size:" << image.size() << endl;

    image2 = imread("./wechat.png",CV_LOAD_IMAGE_COLOR);
    if(image2.empty())
    {
      cout << "Image2 is empty" << endl;
      return 1;
    }
    if(image.isContinuous())
      cout << "Image2 is continuous" << endl;
    cout << "Image2 size:" << image.size() << endl;

//*************My Operation*************//
    //2
    int m = getOptimalDFTSize(image.rows);
    int n = getOptimalDFTSize(image.cols);

    Mat padded;
    copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0));
    //3
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);
    //4
    dft(complexI, complexI);
    //5
    split(complexI, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat magnitudeImage = planes[0];
    //6
    magnitudeImage += Scalar::all(1);
    log(magnitudeImage, magnitudeImage);
    //7
    magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & - 2, magnitudeImage.rows & - 2));
    int cx = magnitudeImage.cols/2;
    int cy = magnitudeImage.rows/2;
    Mat q0(magnitudeImage, Rect(0, 0, cx, cy));
    Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));
    Mat q2(magnitudeImage, Rect(0, cy, cx, cy));
    Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));

    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
    //8
    normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

    imshow("pinyuzhi", magnitudeImage);



//************show image,image2,result********//
    //imshow("Image", image);
    //imshow("Image2", image2);
    //imshow("Result",result);

//***********print runing time**************//
    double duration = (getTickCount() - start) / getTickFrequency();//程序运行时间计算
    cout << "程序用时：" << duration << "s" << endl;

    waitKey(0);

    return 0;
}
