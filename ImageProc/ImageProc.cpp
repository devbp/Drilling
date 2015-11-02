// ImageProc.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include<vector>
#include<fstream>

using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	Mat src, hsv;
    src=imread("c:/oil1.png");
	cvtColor(src, src, CV_BGR2GRAY); //change the color image to grayscale image
	 int count=0;
	 uchar val;

	 // Set threshold and maxValue
	/*double thresh = 100;
	double maxValue = 255; 
    Mat dst;
	// Binary Threshold
	//threshold(src,dst, thresh, maxValue, THRESH_BINARY);
	//imshow( "H-S Histogram", src );
	*/
	
	 std::ofstream outputfile;
	 outputfile.open ("drilling_plan_oil1.txt");
	
	
	 std::vector<Point> drillpoints;
	 std::vector<Point> filtereddrillpoints;
	for(int r=25;r<src.rows;r=r+50) 
	{
		if(count>=64)break;
		for (int c=25;c<src.cols;c=c+50)
			{ 
				if(count>=64)break;
     
			 val=src.at<uchar>(r,c);
 			  if((int)val>100)
			  {
				
			  std::cout<<(int)val<<"  ";
			  src.at<uchar>(r,c) =0; 
			  Point pt = Point(c, r);
			  circle(src,pt,25,Scalar(0,0,122),2,8,0);
			  outputfile<<c;
			  outputfile<<" ";
			  outputfile<<r;
			  outputfile<<std::endl;
			  drillpoints.push_back(pt);
			  count++;
			  		  
			 }

			
			}
	}

	outputfile.close();
 
	imwrite( "oil1_solution.png", src );
	
	/*
	if(count>64)
	{  int i;
		for( i=0;i<drillpoints.size();i++)
		{    int x=drillpoints.at(i).x;
			int y=drillpoints.at(i).y;
			 val=(int)src.at<uchar>(x,y);
			if((int)val>100)
			{  Point pt=Point(drillpoints.at(i).x,drillpoints.at(i).y);
			  filtereddrillpoints.push_back(pt);

			}
		}

	}
	*/

	std::cout<<"size"<<count<<std::endl;
	std::cout<<"filtered drill points"<<filtereddrillpoints.size();

     //Mat img_hist_equalized;
     //equalizeHist(src, img_hist_equalized); //equalize the histogram
    
    imshow( "Drill Section", src);
    waitKey();
	
	return 0;
}

