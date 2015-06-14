# To configure the project and create the Makefile, run the following on the terminal:
#			qmake -spec macx-g++ opengazer.pro

CONFIG	+=	qt
QT += gui widgets

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.8

HEADERS += 	Calibrator.h HeadTracker.h LeastSquares.h EyeExtractor.h GazeTracker.h MainGazeTracker.h OutputMethods.h PointTracker.h FaceDetector.h Point.h utils.h BlinkDetector.h FeatureDetector.h mir.h DebugWindow.h Application.h Video.h Detection.h Command.h ImageWindow.h ImageWidget.h TestWindow.h Prefix.hpp HeadCompensation.h HiResTimer.h ExtractEyeFeaturesSegmentation.h GoogleGlassWindow.h EyeExtractorSegmentationGrountruth.h GazeTrackerHistogramFeatures.h

SOURCES += 	opengazer.cpp Calibrator.cpp HeadTracker.cpp LeastSquares.cpp EyeExtractor.cpp GazeTracker.cpp MainGazeTracker.cpp OutputMethods.cpp PointTracker.cpp FaceDetector.cpp Point.cpp utils.cpp BlinkDetector.cpp FeatureDetector.cpp mir.cpp DebugWindow.cpp Application.cpp Video.cpp Detection.cpp Command.cpp ImageWindow.cpp ImageWidget.cpp TestWindow.cpp HeadCompensation.cpp HiResTimer.cpp ExtractEyeFeaturesSegmentation.cpp GoogleGlassWindow.cpp EyeExtractorSegmentationGrountruth.cpp GazeTrackerHistogramFeatures.cpp

TARGET  = 	opengazer

QMAKE_CFLAGS 	+= `pkg-config opencv --cflags` -include Prefix.hpp -stdlib=libc++
QMAKE_CXXFLAGS 	+= `pkg-config opencv --cflags` -include Prefix.hpp -stdlib=libc++
QMAKE_LIBS 	+= `pkg-config opencv --libs`


macx {
	# Mac OS X linker parameters and include directories
	QMAKE_LIBS += -L/opt/local/lib -lm -ldl -lgthread-2.0 -lfann -lboost_filesystem-mt -lboost_system-mt -lgsl -lgslcblas
}

unix:!macx {
	# Linux linker parameters and include directories
	QMAKE_LIBS += -L/usr/local/lib -L/opt/local/lib -lm -ldl -lgthread-2.0 -lfann -lboost_filesystem -lboost_system -lgsl -lgslcblas
	QMAKE_LIBS += -L/usr/local/cuda-6.5/lib64/ -lGLEW

	INCLUDEPATH += /usr/local/include
}
