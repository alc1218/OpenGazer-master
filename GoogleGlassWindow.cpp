#include "GoogleGlassWindow.h"
#include "Application.h"

#include <boost/filesystem.hpp>

GoogleGlassWindow::GoogleGlassWindow() {
	_window.setWindowTitle("Opengazer Images");

	_window2.setWindowTitle("Opengazer Text");

	//_interface.create(cv::Size(rect.get_width(), rect.get_height()), CV_8UC3);

	_interface.create(cv::Size(	_window.size().width(), 
								_window.size().height()), 
								CV_8UC3);

	_pictureResized.create(cv::Size((_window.size().width()/2)/picturesX, 
									 _window.size().height()/picturesY), 
									 CV_8UC3);

	




	_interface2.create(cv::Size(_window.size().width(), 
								_window.size().height()), 
								CV_8UC3);

	_pictureResized2.create(cv::Size(_window.size().width()/picturesX, 
								 	 _window.size().height()/picturesY), 
								 	 CV_8UC3);

	_text_resized2.create(cv::Size(	_window.size().width(), 
								 	_window.size().height()), 
									CV_8UC3);


	_window.show();
	_window2.show();

}

GoogleGlassWindow::~GoogleGlassWindow() {}

// Main processing function
void GoogleGlassWindow::process() {

	if(!isActive())
		return;



	// PICTURE TO INTERFACE

	boost::filesystem::directory_iterator end_itr;
	
	boost::filesystem::path pictures_path("../Images_Google/Pictures");
	boost::filesystem::directory_iterator picture_image(pictures_path);

	for (int i = 0; i < picturesX; i++) {

		for (int j = 0; j < picturesY; j++) {

			if(picture_image->path().filename().string().compare(".DS_Store") == 0 || picture_image->path().filename().string().compare(".") == 0 || picture_image->path().filename().string().compare("..") == 0) {
				
				++picture_image;
				j--;
				continue;
			} else if(picture_image != end_itr) {
			
				cv::Mat picture = cv::imread(picture_image->path().string().c_str(), CV_LOAD_IMAGE_COLOR);
				//IplImage* picture = (IplImage*) cvLoadImage(picture_image->path().string().c_str());

				cv::resize(picture, _pictureResized2, _pictureResized2.size());
				//cvResize(picture, _pictureResized);

				roi_rect = cv::Rect(_interface.cols/picturesX * i, _interface.rows/picturesY * j, _interface.cols/picturesX, _interface.rows/picturesY);

				_pictureResized2.copyTo(_interface(roi_rect));

				//cvCopy(_picture_resized, _interface);

				++picture_image;
			}
		}
	}



	// INFORMATION TEXT OF PICTURES TO INTERFACE

	boost::filesystem::path text_path("../Images_Google/Text");
	boost::filesystem::directory_iterator text_image(text_path);

	/*
	// GAUSSIAN PROCESS ESTIMATION

	int estimation_x = (Application::Data::gazePointGP.x + Application::Data::gazePointGPLeft.x) / 2;
	int estimation_y = (Application::Data::gazePointGP.y + Application::Data::gazePointGPLeft.y) / 2;
	
	*/

	// GAUSSIAN PROCESS HISTOGRAM FEATURES ESTIMATION

	int estimation_x = (Application::Data::gazePointHistFeaturesGP.x + Application::Data::gazePointHistFeaturesGPLeft.x) / 2;
	int estimation_y = (Application::Data::gazePointHistFeaturesGP.y + Application::Data::gazePointHistFeaturesGPLeft.y) / 2;

	int index_x = estimation_x / (_interface2.cols / picturesX);
	int index_y = estimation_y / (_interface2.rows / picturesY);
	int view_image = (index_x * picturesX) + index_y;

	if ((view_image) < (picturesX * picturesY)) {
		
		int image_file_index = 0;

		while(true) {
			if (!(text_image->path().filename().string().compare(".DS_Store") == 0 || text_image->path().filename().string().compare(".") == 0 || text_image->path().filename().string().compare("..") == 0)) {				
				if(image_file_index == view_image)
					break;
				
				image_file_index++;
			}
			text_image++;
		}
		
		cv::Mat _text = cv::imread(text_image->path().string().c_str(), CV_LOAD_IMAGE_COLOR);

		cv::resize(_text, _text_resized2, _text_resized2.size());

		_text_resized2.copyTo(_interface2);

	}


	// PICTURE FRAMEWORK TO INTERFACE

	//cvSetImageROI(interface, cvRect(index_x * interface->width/picturesX, index_y * interface->height/picturesY, interface->width/picturesX, interface->height/picturesY));

	//cv::Rect framework = cvRectangle(interface, cvPoint(0 ,0), cvPoint(interface->width/picturesX, interface->height/picturesY), cvScalar(255,255, 0), 10, 8, 0);

	//cv::Rect framework = cv::Rect(cvPoint(0 ,0), cvPoint(_interface.rows/picturesX, _interface.cols/picturesY), cvScalar(255,255, 0), 10, 8, 0);

	//Rect brect = rRect.boundingRect();

	roi_rect = cv::Rect(index_x * _interface.size().width/picturesX, index_y * _interface.size().height/picturesY, _interface.size().width/picturesX, _interface.size().height/picturesY);

	cv::rectangle(_interface, roi_rect, cv::Scalar(255,0,0), 10, 8);

	//framework.copyTo(_interface(roi_rect));

	cv::imwrite("lastgoogle.png", _interface);
	_window.showImage(_interface);
	_window2.showImage(_interface2);

}


// Start testing procedure. Reset frame counter and save target point locations
void GoogleGlassWindow::start() {
	_window.show();
	
}

// Aborts calibration
void GoogleGlassWindow::abortGoogleGlassWindow() {
	_window.hide();
}

// Checks if calibrator is active
bool GoogleGlassWindow::isActive() {
	return true;
	//return _frameNumber >= 0;
}

void GoogleGlassWindow::draw() {
	if(isActive()) {



	}
}
