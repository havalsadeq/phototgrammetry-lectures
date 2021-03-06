//this prgram is designed by  Asst. Prof. Dr.Haval A.Sadeq
//this program is soeciedf for image matching matchign based on SSD, sum of absulte difference.
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>

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
float NCC(const Mat imgL1, Mat imgR1, int tWidth1, int iL1, int jL1, int iR1, int jR1);
using namespace std;
int main()
{

	double pPoinY_row = 6912;
	double pPoinrX_col = 3840;
	Mat MN1 = (Mat_<double>(3, 3) <<
		0.9999916137735368, 0.003328789486498286, -0.002385695364084969,
		-0.00332482484419409, 0.9999930884920778, 0.001663883427449353,
		0.002391217592164016, -0.001655937455136055, 0.9999957699661317);

	Mat MN2 = (Mat_<double>(3, 3) <<
		0.9999663324997957, 0.00390827036962278, -0.007215212375665998,
		-0.003920330857179364, 0.99999094073089, -0.001658150207474606,
		0.00720866651179494, 0.001686380401418237, 0.9999725952486229);
	ofstream myfile;
	myfile.open("D:\\disparity_map_coordinates.txt");
	cv::Mat img1 = cv::imread("D:\\00_sample0\\isprs_Vaihingen_rectified\\10050105_rectified.png", 0);//first image
	cv::Mat img2 = cv::imread("D:\\00_sample0\\isprs_Vaihingen_rectified\\10050106_rectified.png", 0);//second image




//////limit for the extarction
	int diff = 2820;

	//the building only
	
		/*double left_col = 4100;
	double right_col = 4400;//6408
	double upper_row = 9900;//3364
	double lower_row = 10300;//8624
*/
	double left_col = 4000;
	double right_col = 7000;//6408
	double upper_row = 450;//3364
	double lower_row = 2450;//8624



	float disparity_range = 75;
	float window_size = 9;
	float match;
	float dis;
	float i_candidate, jL_candidate, jR_candidate;
	Mat_<int> newimg(img1.rows, img1.cols, CV_8UC1);
	for (int i = upper_row; i < lower_row; ++i)//row
	{
		cout << i << " of " << lower_row << endl;

		for (int jL = left_col; jL < right_col; ++jL)//col
		{
			double max = -100000;
			for (int jR = jL - diff - disparity_range; jR < jL - diff + disparity_range; ++jR)//col
	
			{

				match = (NCC(img1, img2, window_size, i, jL, i, jR));// corr2 = 0.;

				if (match > max)
				{

					max = match;
					i_candidate = i;
					jL_candidate = jL;
					jR_candidate = jR;

				}


			}




			//	calumate the inverse coordinates
///////////deifne the parematers

			double 	jL_LSM_real = jL_candidate;
			double	iL_real = i_candidate;
			double	jR_real = jR_candidate;
			double	iR_real = i_candidate;
			double Xp1, Yp1, Xp2, Yp2;

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
			if (max >= 0.85)
			{
//fidn the image coordinate using the
			//	cout << Org_x_Left << " " << Org_y_left << " " << Org_x_Right << "  " << Org_y_Right << " 498361.185 5418944.984 207.745" << endl;
				myfile << Org_x_Left << " " << Org_y_left << " " << Org_x_Right << "  " << Org_y_Right << " 498361.185 5418944.984 207.745" << endl;
			}

		//myfile << i << " " << jL << " " << min << endl;
		}
	}
	//imwrite("D:\\newimg.jpg", newimg);
	system("pause");

}





float NCC(const Mat imgL1, Mat imgR1, int tWidth1, int iL1, int jL1, int iR1, int jR1)
{
	float tCor;
	float tWindow[20000], corWindo[20000];

	float iAverage; // Average Gray Level of Image
	float tAverage; // Average Gray Level of Template
	int tW;							
	int tHeight = tWidth1; // TEMPLATE HEIGHT
						  

						   //	 FIND AVERAGE GRAY LEVEL OF the templete using right image
	tAverage = 0.0;  tW = 0;
	for (int it = iL1 - tHeight / 2; it < tHeight + iL1 - tHeight / 2; it++)
		for (int jt = jL1 - tWidth1 / 2; jt < tWidth1 + jL1 - tWidth1 / 2; jt++)
		{
	
			tAverage += (float)imgL1.at<uchar>(it, jt); tWindow[tW] = (float)imgL1.at<uchar>(it, jt); tW = tW + 1; 
		}
	tAverage = tAverage / (tHeight * tWidth1);
									

	iAverage = 0.; tW = 0;
	/// FIND AVERAGE GRAY LEVEL OF SECTION IMAGE along the rectified lines


	for (int it = iR1 - tHeight / 2; it < tHeight + iR1 - tHeight / 2; it++)
		for (int jt = jR1 - tWidth1 / 2; jt < tWidth1 + jR1 - tWidth1 / 2; jt++)
		{
			//	cout << it << "   " << jt << endl;
			iAverage += (float)imgR1.at<uchar>(it, jt); corWindo[tW] = (float)imgR1.at<uchar>(it, jt); tW = tW + 1;

		}

	iAverage = iAverage / (tHeight * tWidth1);


	float numerator = 0.0; //tu so
	float denominator = 0.; // mau so
							//float tCor = 0; // numerator / denominator
	float sumxix = 0.; // sum xi - x
	float sumyiy = 0.; // sum yi - y //denominator = sqrt(sumxix * sumyiy)

					   //	for (int k = 0; k < tHeight; k++)
					   //for (int l = 0; l < tWidth; l++)
	for (int l = 0; l < tHeight * tWidth1; l++)
	{
		numerator += (tWindow[l] - tAverage) * (corWindo[l] - iAverage);
		sumxix += (tWindow[l] - tAverage) * (tWindow[l] - tAverage);
		sumyiy += (corWindo[l] - iAverage) * (corWindo[l] - iAverage);
	}
	denominator = sqrt(sumxix * sumyiy);
	tCor = numerator / denominator;

	return (tCor);
}
