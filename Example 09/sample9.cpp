#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <stdint.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if(event==EVENT_MOUSEMOVE)
    {
		cv::Mat temp = cv::imread("output.jpg");

		int c=x;
		int r=y;

		Vec3b pixel = temp.at<Vec3b>(r,c);
		uchar blue = pixel[0];
		uchar green = pixel[1];
		uchar red = pixel[2];

		if(blue>=247&&blue<=255)
		{
			if(red>=247&&red<=255)
			{
				if(green>=247&&green<=255)
				{
					cout<<"MOVE ALLOWED"<<endl;
				}
			}
		}
		else
		{
			cout<<"NOT ALLOWED"<<endl;
		}
    }
	else
	{
		cout<<"Error"<<endl;
	}
}

void output()
{
	cv::Mat img_bw4, newTemp, img_gray;
	cv::Mat3b next = cv::imread("next3.jpg");

	cv::cvtColor(next, img_gray, CV_RGB2GRAY);
	cv::threshold(img_gray, newTemp, 85.0, 255.0, THRESH_BINARY);

	for(int r=0;r<next.rows;++r)
	{
		for(int c=0;c<next.cols;++c)
		{
			Vec3b pixel = next(r, c);
			int blue = pixel[0];
			int green = pixel[1];
			int red = pixel[2];

			if(red>=247&&green<=10&&blue<=10)
			{
				newTemp.at<uchar>(r, c) = 255;
			}
			else
			{
				newTemp.at<uchar>(r, c) = 0;
			}
		}
	}

	cv::imshow("FINAL", newTemp);
	cv::imwrite("output.jpg", newTemp);

	//Movement
	/*namedWindow("Movement", 1);
	setMouseCallback("Movement", CallBackFunc, NULL);
	imshow("Movement", newTemp);*/
}

void renovation2()
{
	cv::Mat img_bw4, newTemp, img_gray;
	cv::Mat3b next = cv::imread("next2.jpg");

	cv::cvtColor(next, img_gray, CV_RGB2GRAY);
	cv::threshold(img_gray, newTemp, 85.0, 255.0, THRESH_BINARY);

	for(int r=0;r<next.rows;++r)
	{
		for(int c=0;c<next.cols;++c)
		{
			Vec3b pixel = next(r, c);
			int blue = pixel[0];
			int green = pixel[1];
			int red = pixel[2];

			if(red>=247&&green<=10&&blue<=10)
			{
				newTemp.at<uchar>(r, c) = 255;
			}
			else
			{
				newTemp.at<uchar>(r, c) = 0;
			}
		}
	}

	//cv::imshow("New", newTemp);

	cvtColor(newTemp, img_bw4, CV_GRAY2BGR);

	vector<Vec4i> lines;
	HoughLinesP(newTemp, lines, 1, CV_PI/180, 180, 380, 50);
	for(size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(img_bw4, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 10, CV_AA);
	}
	
	imshow("source3", newTemp);
	imshow("detected lines3", img_bw4);
	cv::imwrite("next3.jpg", img_bw4);

	output();
}

void renovation()
{
	cv::Mat img_bw4, newTemp, img_gray;
	cv::Mat3b next = cv::imread("next.jpg");

	cv::cvtColor(next, img_gray, CV_RGB2GRAY);
	cv::threshold(img_gray, newTemp, 85.0, 255.0, THRESH_BINARY);

	for(int r=0;r<next.rows;++r)
	{
		for(int c=0;c<next.cols;++c)
		{
			Vec3b pixel = next(r, c);
			int blue = pixel[0];
			int green = pixel[1];
			int red = pixel[2];

			if(red>=247&&green<=10&&blue<=10)
			{
				newTemp.at<uchar>(r, c) = 255;
			}
			else
			{
				newTemp.at<uchar>(r, c) = 0;
			}
		}
	}

	//cv::imshow("New", newTemp);

	cvtColor(newTemp, img_bw4, CV_GRAY2BGR);

	vector<Vec4i> lines;
	HoughLinesP(newTemp, lines, 1, CV_PI/180, 180, 140, 40);
	for(size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(img_bw4, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
	}
	
	imshow("source2", newTemp);
	imshow("detected lines2", img_bw4);
	cv::imwrite("next2.jpg", img_bw4);
	renovation2();
}

int main()
{
	cv::Mat img_gray, img_bw, temp;
	//read an image
	cv::Mat3b img_bgr = cv::imread("s9.jpg");
	cv::imshow("Original Image", img_bgr);

	//conversion gray
    cv::cvtColor(img_bgr, img_gray, CV_RGB2GRAY);
	cv::imshow("G", img_gray);

	//binary
    cv::threshold(img_gray, img_bw, 95.0, 255.0, THRESH_BINARY);
	cv::threshold(img_gray, temp, 95.0, 255.0, THRESH_BINARY);

	//output
    cv::imshow("Binary (1st)", img_bw);

	cvtColor(img_bw, temp, CV_GRAY2BGR);

	vector<Vec4i> lines;
	HoughLinesP(img_bw, lines, 1, CV_PI/180, 100, 55, 10);
	for(size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(temp, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
	}

	imshow("source", img_bw);
	imshow("detected lines", temp);
	cv::imwrite("next.jpg", temp);

	renovation();

	cv::waitKey(0);

	return 0;
}