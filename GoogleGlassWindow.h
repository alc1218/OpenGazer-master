#pragma once

#include "ImageWindow.h"
#include "Point.h"

#define picturesX 3
#define picturesY 3

class GoogleGlassWindow {
public:
	GoogleGlassWindow();
	~GoogleGlassWindow();
	
	// Main processing function
	void process();
	
	// Calibration API functions (for future use)
	void start();
	void abortGoogleGlassWindow();
	void draw();
	
	bool isActive();
	
private:
	ImageWindow _window;
	ImageWindow _window2;


	cv::Mat _interface;
	cv::Mat _pictureResized;
	
	cv::Mat _interface2;
	cv::Mat _pictureResized2;
	cv::Mat _text_resized2;
	
	cv::Rect roi_rect;


};


