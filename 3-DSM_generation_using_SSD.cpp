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
float SSD(const Mat imgL1, Mat imgR1, int tWidth1, int iL1, int jL1, int iR1, int jR1);
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
	double right_col = 7000;//3000 pixels
	double upper_row = 450;//
	double lower_row = 2450;//2000 pixels
	//total pixels is 6 000 000
	float disparity_range = 75;
	float window_size = 9;
	float match;
	float dis;
	float i_candidate, jL_candidate, jR_candidate;
	Mat_<int> newimg(img1.rows, img1.cols, CV_8UC1);
	for (int i = upper_row; i < lower_row; ++i)//row
	{
		cout << i << " of " << lower_row << endl;
		//for (int jL = 0; jL < img1.cols - disparity_range; ++jL)//col
		for (int jL = left_col; jL < right_col; ++jL)//col
		//	for (int jL = disparity_range; jL < img1.cols - disparity_range- window_size/2; ++jL)//col
		{
			//cout << " jL " << jL <<" of "<< img1.cols << endl;
			double min = 100000;
			//system("pause");
			for (int jR = jL - diff - disparity_range; jR < jL - diff + disparity_range; ++jR)//col
		//	for (int jR = jL - disparity_range; jR < jL + disparity_range; ++jR)//col
			{  
					//cout << "JR= "<<jR << endl;
					//cout << "jL= "<<jL << endl;
			//	if (jR < jL) continue;
				//	if (jR > jL - disparity_range) continue;
			///	AD = 1000000;
				match = (SSD(img1, img2, window_size, i, jL, i, jR));// corr2 = 0.;
				//system("pause");
				//AD = abs((double)img1.at<uchar>(i, jL) - (double)img2.at<uchar>(i, jR));
			//		cout << " difference " << jL <<"  "<<jR<< " "<< AD << endl;
				//	system("pause");
				if (match < min)
				{
					min = match;
					i_candidate = i;
					jL_candidate = jL;
					jR_candidate = jR;
			//		cout << "                            minimum  difference " << min << endl;

				}
				//	cout << min << endl;
				//	cout << (double)img1.at<uchar>(i, jL) << endl;
				//	cout << (double)img2.at<uchar>(i, jR) << endl << endl;;
				//	if ((double)img1.at<uchar>(i, j) > (double)img2.at<uchar>(i, j));
				//	newimg(i, j) = (double)img1.at<uchar>(i, j) + 100;//add your fundction as you like here
	

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

		//	myfile << i_candidate << " " << jL_candidate << " " << jL_candidate - jR_candidate << endl;
		//	cout << i_candidate << " " << jL_candidate << " "  << jR_candidate <<" " << jL_candidate - jR_candidate << endl;	system("pause");
			//myfile << i << " " << jL << " " << min << endl;
		}
	}
	//imwrite("D:\\newimg.jpg", newimg);

	


}


float SSD(const Mat imgL1, Mat imgR1, int tWidth1, int iL1, int jL1, int iR1, int jR1)
{
	float tCor;
	float tWindow[20000], corWindo[20000];
	float imL[10000], imR[10000];
	float sum; // Average Gray Level of Image
	float tAverage; // Average Gray Level of Template
	int tW;							//int tWidth = 5; // TEMPLATE WIDTH
	int tHeight = tWidth1; // TEMPLATE HEIGHT
						   //int i = 400;

						   //	 FIND AVERAGE GRAY LEVEL OF the templete using right image
	  tW = 0;
	int countL = 0;
	for (int it = iL1 - tHeight / 2; it < tHeight + iL1 - tHeight / 2; it++)//continously calculte the templete pixel values
		for (int jt = jL1 - tWidth1 / 2; jt < tWidth1 + jL1 - tWidth1 / 2; jt++)
		{
		//	cout <<"iL1  "<< iL1 <<" "<< jL1 << " "<<jR1 << "  "<<(float)imgL1.at<uchar>(it, jt) << " "<<(float)imgR1.at<uchar>(it, jt) << endl;


			//	cout << it << "  image-L " << jt << "   "<< (int)imgL.at<uchar>(it, jt)<<endl;
			//sum += abs ((float)imgL1.at<uchar>(it, jt) - (float)imgR1.at<uchar>(it, jt)); 	
			imL[countL] = (float)imgL1.at<uchar>(it, jt); ++countL;
		//	cout << (float)imgL1.at<uchar>(it, jt) << " " << (float)imgR1.at<uchar>(it, jt) << endl;
			//	cout << " Val. "<< tAverage << endl;
			//cout << " sum " << sum << endl;
		}
	///////////////////
	// 
	int countR = 0;
		for (int it = iR1 - tHeight / 2; it < tHeight + iR1 - tHeight / 2; it++)//continously calculte the templete pixel values
	for (int jt = jR1 - tWidth1 / 2; jt < tWidth1 + jR1 - tWidth1 / 2; jt++)
	{
		//	cout <<"iL1  "<< iL1 <<" "<< jL1 << " "<<jR1 << "  "<<(float)imgL1.at<uchar>(it, jt) << " "<<(float)imgR1.at<uchar>(it, jt) << endl;


			//	cout << it << "  image-L " << jt << "   "<< (int)imgL.at<uchar>(it, jt)<<endl;
	//	sum += abs((float)imgL1.at<uchar>(it, jt) - (float)imgR1.at<uchar>(it, jt));
		imR[countR] = (float)imgR1.at<uchar>(it, jt); ++countR;
		//cout << (float)imgL1.at<uchar>(it, jt) << " " << (float)imgR1.at<uchar>(it, jt) << endl;
		//	cout << " Val. "<< tAverage << endl;
		//cout << " sum " << sum << endl;
	}
		sum = 0.0;
		for (int count = 0; count < tWidth1 * tWidth1; ++count)
		{
		sum += (imL[count] - imR[count])* (imL[count] - imR[count]);
		//	cout << sum << " " <<imL[count] << " " << imR[count] << endl;
		}
	//tAverage = tAverage / (tHeight * tWidth1);//this is done 
											  //cout << " taver. " << tAverage << endl;					
											  //	system("pause");
											  /////////////////////////////COMPUTE correlation start in the scan on the right image

	//sum = 0.; tW = 0;
	/// FIND AVERAGE GRAY LEVEL OF SECTION IMAGE along the rectified lines


	//	cout << " sum  " << sum << endl;

	return (sum);
}
