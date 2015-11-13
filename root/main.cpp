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

	// grid boundaries
	double rad_beg = start_angle * M_PI / 180;
	double rad_end = (start_angle + fovx) * M_PI / 180;
	double beam_size = (fovx * M_PI / 180) / beams;

	std::vector<int> transfer;

	//  Sweeping the Image---------->> Whole Image Cartesian Sweep
	for (int imgx = 0; imgx < image.cols; ++imgx) {
		for (int imgy = 0; imgy < center.y; ++imgy) {

			cv::Point2f point(imgx - center.x, imgy - center.y);

			if (!point.y) {
				transfer.push_back(-1);
			} else {
				double theta = atan(point.x / point.y);
				double radius = sqrt(point.x * point.x + point.y * point.y);

				// pixels outside of sonar image
				if (radius >= bins || rad_beg > theta || theta > rad_end || !radius){
					transfer.push_back(-1);
				}

				// pixels inside of sonar image
				else {


					//  Sweeping the Grid ---------->> Entire Grid Polar Sweep

//					for (int id_bin = 0; id_bin < bins; ++id_bin) {

					for (uint id_Beam = 0; id_Beam < beams; ++id_Beam) {


						if (theta >= rad_beg + (id_Beam * beam_size) && theta < rad_beg + ((id_Beam + 1) * beam_size)){

											transfer.push_back(id_Beam * radius);


//											std::cout << "id_beam  " << id_Beam << std::endl << "radius   ------>" << radius << std::endl;

							}

						}
//					}
				}
			}




			// Stop sweeping the image
		}
	}


	std::cout << "Image: " << center.y * image.cols << std::endl;
	std::cout << "Transfer: " << transfer.size() << std::endl;

	// plot sonar image
	for (int x = 0; x < image.cols; ++x) {
		for (int y = 0; y < center.y; ++y) {
			if (!transfer[x * center.y+ y]) {
				image[y][x][0] = 255;
				image[y][x][1] = 0;
				image[y][x][2] = 255;
			}
		}
	}









	cv::imshow("Sonar View", image);
	cv::waitKey();
	return 0;
}

