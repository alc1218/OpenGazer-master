#pragma once

#include "ImageWindow.h"
#include "Point.h"

class TestWindow {
public:
	TestWindow();
	~TestWindow();
	
	// Main processing function
	void process();
	
	// Calibration API functions (for future use)
	void start(const std::vector<Point> &points);
	void pointStart();
	void pointEnd();
	void abortTesting();
	void testingEnded();
	void draw();
	
	bool isActive();
	Point getActivePoint();
	int getPointNumber();
	int getPointFrameNo();
	bool isLastFrame();
	bool isLastPoint();
	bool isFinished();
	bool shouldStartNextPoint();
	
private:
	int _frameNumber;
	std::vector<Point> _points;
	ImageWindow _window;
	cv::Mat _screenImage;
	cv::Mat _targetImage;
};


