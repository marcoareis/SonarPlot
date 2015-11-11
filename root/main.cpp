#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char **argv) {

	cv::Mat3b image = cv::Mat3b::zeros(600, 1000);
	cv::Point center(image.cols * 0.5, image.rows * 0.9);

	// fixed variables (parametrizavel)
	int beams = 256, bins = 500;
	double fovx = 120.0, start_angle = -60.0;

	// so...
	double rad_beg = start_angle * M_PI / 180;
	double rad_end = (start_angle + fovx) * M_PI / 180;
	double beam_size = (fovx * M_PI / 180) / beams;

	std::vector<int> transfer;

	//  delimiting each sector
	for (int imgx = 0; imgx < image.cols; ++imgx) {
		for (int imgy = 0; imgy < center.y; ++imgy) {

			cv::Point2f point(imgx - center.x, imgy - center.y);

			if (!point.y) {
				transfer.push_back(-1);
			} else {
				double theta = atan(point.x / point.y);
				double radius = sqrt(point.x * point.x + point.y * point.y);

				// pixels outside of sonar image
				if (radius >= bins || rad_beg > theta || theta > rad_end || !radius)
					transfer.push_back(-1);

				// pixels inside of sonar image
				else {

					int id_beam;

					for (int id_beam = 0; id_beam < beams - 1; ++id_beam) {

						if (theta >= rad_beg + (id_beam * beam_size) && theta < rad_beg + (id_beam * beam_size)){
							std::cout << "entao eh natal" << std::endl;
						}



					}

//					transfer.push_back(0);

				}
			}
		}
	}


	std::cout << "Image: " << center.y * image.cols << std::endl;
	std::cout << "Transfer: " << transfer.size() << std::endl;

	// plot sonar image
	for (int x = 0; x < image.cols; ++x) {
		for (int y = 0; y < center.y; ++y) {
			if (!transfer[x * center.y + y]) {
				image[y][x][0] = 255;
				image[y][x][1] = 0;
				image[y][x][2] = 0;
			}
		}
	}



//	for (int i = 0; i < image.cols; ++i) {
//		for (int j = 0; j < image.rows; ++j) {
//
//		}
//
//	}

//			double current_angle;
//
//			// Selecting the current angle to the next step
//
//			if (point.y != 0) {
//				current_angle = atan((point.x) / (point.y));
//			} else
//				current_angle = M_PI_2;
//
//
////				std::cout << "this is the current angle       " << minAngle / ratio << " < " << current_angle/ratio << " < " << maxAngle / ratio << std::endl;
//
//
//
//
//			// pixels outside of sonar image
//			if (radius >= bins || start_angle >= current_angle || current_angle >= end_angle || !radius){
//				transfer.push_back(-1);
//			}
//
//
//			// pixels inside of sonar image
//			else {
//
//					double my_bin, id_bins, id_beam;
//					double minAngle, maxAngle;
//					double minBin, maxBin;
//
//					//here ends the declaration
//
//
//
//
//
//
//
//
//			int start_beam, end_beam;
//			cv::Scalar color;
//
//
//			if (current_angle >= 0){
//				start_beam = beams/2.0;
//				end_beam = 0;
//				color = cv::Scalar(255,0,0);
////				std::cout << "look at ronaldvinho" << std::endl;
//
//			} else {
//				start_beam = beams;
//				end_beam = beams/2.0;
//				color = cv::Scalar(0,0,255);
//
////				std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
//
//			}
//
//
//
//
//
//					for (int my_beam = start_beam; my_beam > end_beam; my_beam--)	{		//First bricklayer
//
//						image[imgy][imgx][0] = color[0];
//						image[imgy][imgx][1] = color[1];
//						image[imgy][imgx][2] = color[2];
//
//						int my_beam2 = 256 - my_beam;
//
//						minBin = (my_bin - 1);
//						maxBin = my_bin;
//
//						minAngle =  (my_beam- 1.0) ;
//						maxAngle = my_beam;
//
//
////						std::cout << "this is the second one               " << minAngle / ratio << " < " << current_angle/ratio << " < " << maxAngle / ratio << std::endl;
//
//						if (current_angle >= minAngle && current_angle < maxAngle){
//
//
////														std::cout << " este eh o beam -->" <<  my_beam2 << std::endl;
////														std::cout << " este eh o raio -->" <<  int(radius) << std::endl << std::endl;
//
//							if(my_beam == 44) {
//								image[imgy][imgx][0] = 255;
//								image[imgy][imgx][1] = 255;
//								image[imgy][imgx][2] = 255;
//							}
//
////							bins_identification.push_back(radius);
//
////							for (int n = 0; n <= 128; ++n) {
////
////							std::coutdouble current_angle;
//
//							// Selecting the current angle to the next step
//
//							if (point.y != 0) {
//								current_angle = atan((point.x) / (point.y));
//							} else
//								current_angle = M_PI_2;
//
//
//				//				std::cout << "this is the current angle       " << minAngle / ratio << " < " << current_angle/ratio << " < " << maxAngle / ratio << std::endl;
//
//
//
//
//							// pixels outside of sonar image
//							if (radius >= bins || start_angle >= current_angle || current_angle >= end_angle || !radius){
//								transfer.push_back(-1);
//							}
//
//
//							// pixels inside of sonar image
//							else {
//
//									double my_bin, id_bins, id_beam;
//									double minAngle, maxAngle;
//									double minBin, maxBin;
//
//									//here ends the declaration
//
//
//
//
//
//
//
//
//							int start_beam, end_beam;
//							cv::Scalar color;
//
//
//							if (current_angle >= 0){
//								start_beam = beams/2.0;
//								end_beam = 0;
//								color = cv::Scalar(255,0,0);
//				//				std::cout << "look at ronaldvinho" << std::endl;
//
//							} else {
//								start_beam = beams;
//								end_beam = beams/2.0;
//								color = cv::Scalar(0,0,255);
//
//				//				std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
//
//							}
//
//
//
//
//
//									for (int my_beam = start_beam; my_beam > end_beam; my_beam--)	{		//First bricklayer
//
//										image[imgy][imgx][0] = color[0];
//										image[imgy][imgx][1] = color[1];
//										image[imgy][imgx][2] = color[2];
//
//										int my_beam2 = 256 - my_beam;
//
//										minBin = (my_bin - 1);
//										maxBin = my_bin;
//
//										minAngle =  (my_beam- 1.0) ;
//										maxAngle = my_beam;
//
//
//				//						std::cout << "this is the second one               " << minAngle / ratio << " < " << current_angle/ratio << " < " << maxAngle / ratio << std::endl;
//
//										if (current_angle >= minAngle && current_angle < maxAngle){
//
//
//				//														std::cout << " este eh o beam -->" <<  my_beam2 << std::endl;
//				//														std::cout << " este eh o raio -->" <<  int(radius) << std::endl << std::endl;
//
//											if(my_beam == 44) {
//												image[imgy][imgx][0] = 255;
//												image[imgy][imgx][1] = 255;
//												image[imgy][imgx][2] = 255;
//											}
//
//				//							bins_identification.push_back(radius);
//
//				//							for (int n = 0; n <= 128; ++n) {
//				//
//				//							std::cout << beams_identification[n] << std::endl;
//				//
//				//							}
//
//
//											break;
//										}
//
//
//									}
//
//							}
//
//
//
//
//							// Here ends the sweep
//						}
//					}
//
// << beams_identification[n] << std::endl;
//
//							}


//							break;
//						}


//					}

//			}




			// Here ends the sweep
//		}
//	}






	cv::imshow("Sonar View", image);
	cv::waitKey();
	return 0;
}

