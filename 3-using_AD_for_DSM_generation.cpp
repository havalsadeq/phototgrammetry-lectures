

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
//#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>
//#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include<limits.h> 

#define PI 3.14159265
#define F 120
#define Pix 0.012
const char* source_window = "Source image";
const char* corners_window = "Corners detected";
using namespace cv;
using namespace std;

using namespace std;
int main()
{
	double pPoinY_row = 6912;
	double pPoinrX_col = 3840;
	Mat MN1 = (Mat_<double>(3, 3) <<
		0.9999916137735368, 0.003328789486498286, -0.002385695364084969,
		-0.00332482484419409, 0.9999930884920778, 0.001663883427449353,
		0.002391217592164016, -0.001655937455136055, 0.9999957699661317




		);

	Mat MN2 = (Mat_<double>(3, 3) <<


		0.9999663324997957, 0.00390827036962278, -0.007215212375665998,
		-0.003920330857179364, 0.99999094073089, -0.001658150207474606,
		0.00720866651179494, 0.001686380401418237, 0.9999725952486229



		);

	ofstream myfile;
	myfile.open("D:\\disparity_map_coordinates.txt");
	cv::Mat img1 = cv::imread("D:\\00_sample0\\isprs_Vaihingen_rectified\\10050105_rectified.png", 0);//first image
	cv::Mat img2 = cv::imread("D:\\00_sample0\\isprs_Vaihingen_rectified\\10050106_rectified.png", 0);//second image



	//cv::Mat img3 = cv::imread("D:\\pentagon_512\\pentag_r.jpg", 0);//third image
	//cv::Mat newimg;
	float disparity_range = 75;
	float AD;
	float i_candidate, jL_candidate, jR_candidate;
	Mat_<int> newimg(img1.rows, img1.cols, CV_8UC1);

	

//////limit for the extarction
	int diff = 2820;

	/*
	//the building only
	double left_col = 4000;
	double right_col = 6000;//6408
	//double right_col = 5000;//6408
	double upper_row = 450;//3364
	double lower_row = 1700;//8624
	*/

	double left_col = 4000;
	double right_col = 7000;//6408
	double upper_row = 450;//3364
	double lower_row = 2450;//8624

	//	for (int iL = upper_row; iL < lower_row; iL = iL + 1)
for (int i = upper_row; i < lower_row; ++i)//row
	{
	cout << i << " of " << lower_row << endl;
		for (int jL = left_col; jL < right_col; ++jL)//col
		{
			double min = 100000;
			//system("pause");
			for (int jR = jL -diff - disparity_range; jR < jL - diff + disparity_range; ++jR)//col
			{
			//	cout << "JR= "<<jR << endl;
					//cout << "jL= "<<jL << endl;
				//if (jR < jL) continue;
				//	if (jR > jL - disparity_range) continue;
				AD = abs((double)img1.at<uchar>(i, jL) - (double)img2.at<uchar>(i, jR));
				//	cout << " difference " << AD << endl;
				if (AD < min)
				{

					min = AD;
					i_candidate = i;
					jL_candidate = jL;
					jR_candidate = jR;

				}
				//	cout << min << endl;
				//	cout << (double)img1.at<uchar>(i, jL) << endl;
				//	cout << (double)img2.at<uchar>(i, jR) << endl << endl;;


				//	if ((double)img1.at<uchar>(i, j) > (double)img2.at<uchar>(i, j));
				//	newimg(i, j) = (double)img1.at<uchar>(i, j) + 100;//add your fundction as you like here

				//	myfile << i_candidate << " " << jL_candidate << " " << jL_candidate- jR_candidate << endl;



			}



		//	calumate the inverse coordinates
///////////deifne the parematers

			double 	jL_LSM_real = jL_candidate;
			double	iL_real = i_candidate;
			double	jR_real = jR_candidate;
			double	iR_real = i_candidate;
			double Xp1, Yp1, Xp2, Yp2;
		//	cout << iL_real << "  " << jL_LSM_real << "  " << jR_real << endl;
		//	system("pause");
			double Org_x_Left = (-1 * F) * (
				(MN1.at<double>(0, 0) * ((double)(jL_LSM_real - pPoinrX_col) * Pix) + MN1.at<double>(1, 0) * (pPoinY_row - (double)iL_real) * Pix + MN1.at<double>(2, 0) * (-1 * F))
				/
				(MN1.at<double>(0, 2) * ((double)(jL_LSM_real - pPoinrX_col) * Pix) + MN1.at<double>(1, 2) * (pPoinY_row - (double)iL_real) * Pix + MN1.at<double>(2, 2) * (-1 * F))
				);
			double Org_y_left = (-1 * F) * (
				(MN1.at<double>(0, 1) * ((double)(jL_LSM_real - pPoinrX_col) * Pix) + MN1.at<double>(1, 1) * (pPoinY_row - (double)iL_real) * Pix + MN1.at<double>(2, 1) * (-1 * F))
				/
				(MN1.at<double>(0, 2) * ((double)(jL_LSM_real - pPoinrX_col) * Pix) + MN1.at<double>(1, 2) * (pPoinY_row - (double)iL_real) * Pix + MN1.at<double>(2, 2) * (-1 * F))
				);
			//double Xp1, Yp1, Xp2, Yp2;


		//////////////////////////////////////////////////////////////////////

			double Org_x_Right = (-1 * F) * (
				(MN2.at<double>(0, 0) * ((double)(jR_real)-pPoinrX_col) * Pix + MN2.at<double>(1, 0) * (pPoinY_row - (double)iR_real) * Pix + MN2.at<double>(2, 0) * (-1 * F))
				/
				(MN2.at<double>(0, 2) * ((double)(jR_real)-pPoinrX_col) * Pix + MN2.at<double>(1, 2) * (pPoinY_row - (double)iR_real) * Pix + MN2.at<double>(2, 2) * (-1 * F))
				);
			double Org_y_Right = (-1 * F) * (
				(MN2.at<double>(0, 1) * ((double)(jR_real)-pPoinrX_col) * Pix + MN2.at<double>(1, 1) * (pPoinY_row - (double)iR_real) * Pix + MN2.at<double>(2, 1) * (-1 * F))
				/
				(MN2.at<double>(0, 2) * ((double)(jR_real)-pPoinrX_col) * Pix + MN2.at<double>(1, 2) * (pPoinY_row - (double)iR_real) * Pix + MN2.at<double>(2, 2) * (-1 * F))
				);

			////////////////////////////////////////////
			myfile << Org_x_Left << " " << Org_y_left << " " << Org_x_Right << "  " << Org_y_Right << " 498361.185 5418944.984 207.745" << endl;
			//myfile4 << Org_x_Left << " " << Org_y_left << " " << Org_x_Right << "  " << Org_y_Right << " 498361.185 5418944.984 207.745  " << cov[candidate] << endl;

			//myfile << i_candidate << " " << jL_candidate << " " << jL_candidate - jR_candidate << endl;

		//	myfile << i << " " << jL << " " << min << endl;
		}	//system("pause");
	}
	//imwrite("D:\\newimg.jpg", newimg);

	


}

