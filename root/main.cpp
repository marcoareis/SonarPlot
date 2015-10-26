#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char **argv) {

	cv::Mat3b image = cv::Mat3b::zeros(600, 1000);
	cv::Point center(image.cols / 2, image.rows * 0.9);

	double ratio = M_PI / 180;
	double offset = -M_PI_2;
	double start_angle = -60.0 * ratio + offset;
	double end_angle = 60.0 * ratio + offset;
	int bins = 500;
	int beams = 256;

	double radiusLimit = image.cols/ 2.0;
	double radiusIncrement = radiusLimit / bins;

	double angleLimit = 210.0 * ratio + offset;
	double angleIncrement = angleLimit / beams;

	std::vector<int> pixelCartesianPositions;

	std::vector<int> transfer;

	//  delimiting each sector

	int my_bin, my_beam;

	my_beam = 256 - my_beam;
	double minBin, maxBin;
	minBin = (my_bin - 1) * radiusIncrement;
	maxBin = my_bin * radiusIncrement;

	double minAngle, maxAngle;
	minAngle =  (my_beam - 1) * (angleIncrement) - (5*M_PI/6);
	maxAngle =  my_beam * (angleIncrement)  - (5*M_PI/6);


	//				std::cout << "this is the min angle ---->" << minAngle / ratio << std::endl;
	//				std::cout << "this is the max angle ----------->" << maxAngle / ratio << std::endl;
	//				std::cout << "this is the angle increment ----------->" << angleIncrement / ratio << std::endl;


	//      Here starts the sweep

	for (int imgx = 0; imgx < image.cols; ++imgx) {
		for (int imgy = 0; imgy < center.y; ++imgy) {


			std::vector<int> beams_identification;
			std::vector<int> bins_identification;

			cv::Point2f point(imgx - center.x, imgy - center.y);
			double radius = sqrt(point.x * point.x + point.y * point.y);
			double current_angle;

			// Selecting the current angle to the next step

			if (point.y != 0) {
				current_angle = atan((point.x) / (point.y));
			} else
				current_angle = M_PI_2;

			current_angle += offset;


			//				if(current_angle == -M_PI / 2){
			//						// isso aqui eh so pra saber onde eu estou, tipo uma bussola
			//					image[imgy][imgx][0] = 255;
			//					image[imgy][imgx][1] = 255;
			//					image[imgy][imgx][2] = 0;
			//				}





			if (radius >= radiusLimit || start_angle >= current_angle || current_angle >= end_angle){
				//aqui eu estou fora do grid
				transfer.push_back(-1);

			}



			else {
				//aqui eu estou dentro do grid, so estou trabalhando com os pixels que irei armazenar

				int start_beam;


				if (current_angle >= - M_PI/2) {

					for (int my_beam = 255; my_beam > beams/2; my_beam--)	{		//Primeiro pedreiro


						image[imgy][imgx][0] = 0;
						image[imgy][imgx][1] = 0;
						image[imgy][imgx][2] = 255;


						int my_bin, id_bins, id_beam;

						my_beam = 256 - my_beam;
						double minBin, maxBin;
						minBin = (my_bin - 1) * radiusIncrement;
						maxBin = my_bin * radiusIncrement;

						double minAngle, maxAngle;
						minAngle =  (my_beam - 1) * (angleIncrement) - (5*M_PI/6);
						maxAngle =  my_beam * (angleIncrement)  - (5*M_PI/6);



						if (current_angle >= minAngle && current_angle < maxAngle){

							std::cout << "PLEEEEI" << std::endl;

							beams_identification.push_back(my_beam);
							bins_identification.push_back(radius);

						}

						//						std::cout << "this is the min angle ---->" << minAngle / ratio << std::endl;
						//						std::cout << "this is the max angle ----------->" << maxAngle / ratio << std::endl;
						//						std::cout << "my_beam -->" << my_beam << std::endl;

						//						std::cout << "bins_identification -->" << bins_identification.at(my_beam) << std::endl;
						//						std::cout << "Beams_identification -->" << beams_identification.at(my_beam) << std::endl;

						break;
					}
				}


				else {



					for (int my_beam = beams/2; my_beam > 0; my_beam--){	//Segundo pedreiro

						image[imgy][imgx][0] = 0;
						image[imgy][imgx][1] = 255;
						image[imgy][imgx][2] = 0;


						int my_bin, id_bins, id_beam;

						my_beam = 256 - my_beam;
						double minBin, maxBin;
						minBin = (my_bin - 1) * radiusIncrement;
						maxBin = my_bin * radiusIncrement;

						double minAngle, maxAngle;
						minAngle =  (my_beam - 1) * (angleIncrement) - (5*M_PI/6);
						maxAngle =  my_beam * (angleIncrement)  - (5*M_PI/6);

						if (current_angle >= minAngle && current_angle < maxAngle){

//							std::cout << "PLEEEEI" << std::endl;

							beams_identification.push_back(my_beam);
							bins_identification.push_back(radius);

						}

//						std::cout << "this is the min angle ---->" << minAngle / ratio << std::endl;
//						std::cout << "this is the max angle ----------->" << maxAngle / ratio << std::endl;
//						std::cout << "my_beam -->" << my_beam << std::endl;

						//						std::cout << "bins_identification -->" << bins_identification.at(my_beam) << std::endl;
						//						std::cout << "Beams_identification -->" << beams_identification.at(my_beam) << std::endl;

						break;

					}


				}


			}



			//			current_angle <= 0 ? start_beam = 0 : start_beam = beams/2;






			// 23859176587921364578936248975623897464896598461986238461892634891// 23859176587921364578936248975623897464896598461986238461892634891


			//			if (radius < radiusLimit && start_angle < current_angle && current_angle < end_angle) {
			//
			//				image[imgy][imgx][0] = 255;
			//				image[imgy][imgx][1] = 0;
			//				image[imgy][imgx][2] = 0;

			//&& (int) radius == my_bin

			//				if ( (current_angle > minAngle && current_angle < maxAngle )){
			//
			//					//paint in yellow
			//
			//					image[imgy][imgx][0] = 0;
			//					image[imgy][imgx][1] = 255;
			//					image[imgy][imgx][2] = 255;

			//				std::cout << "These are the point(s) coordinates -->" << cv::Point(imgx, imgy) << std::endl;
			//				}


			//				transfer.push_back(imgy * image.cols + imgx);


			//	}

			//		pixelCartesianPositions.push_back(imgy * image.cols + imgx);


			// Here ends the sweep
		}
	}




	cv::imshow("olha o ronaldinho", image);
	cv::waitKey();
	return 0;
}

