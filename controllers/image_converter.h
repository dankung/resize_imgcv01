#pragma once
#include <opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <vector>
#include <string>

using namespace std;
using namespace cv;

#ifndef CONVERTIMAGE_H_
#define CONVERTIMAGE_H_

/**
 * Kelas yang mengonversi gambar ke base64 dan sebaliknya
 */
class Image_Converter {
public:
	/**
	 * Constritor default
	 */
	Image_Converter();

	/**
	 * Metode yang mengubah gambar base64 menjadi cv::Mat
	 * @param imageBase64, gambar menjadi base64
	 * @return gambar menjadi cv::Mat
	 */
	cv::Mat str2mat(const string& imageBase64);

	/**
	 * Metode yang mengubah menjadi sebuah cv::Mat pada gambar dalam base64
	 * @param img, menjadi gambar cv::Mat
	 * @return gambar menjadi base64
	 */
	string mat2str(const Mat& img);

	virtual ~Image_Converter();

private:
	std::string base64_encode(uchar const* bytes_to_encode, unsigned int in_len);

	std::string base64_decode(String encoded_string);

};

#endif 

