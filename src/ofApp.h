#pragma once

#include "ofMain.h"
#pragma comment(lib, "opencv_world340.lib")
#pragma comment(lib, "yolo_cpp_dll.lib")

#include <iostream>
#include <Windows.h>
#include "yolo_v2_class.hpp"
#include "opencv2\opencv.hpp"
#include "ofxCv.h"

using namespace cv;
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		
		//--------------------------------------------------------------
		int FileSize(string path);
		Mat makeImageBGR24(Mat img);
		std::vector<ofVec4f> box(Detector *Detector, cv::Mat img, float threshold);
		std::vector<float> confi(Detector *Detector, cv::Mat img, float threshold);
		std::vector<int> objid(Detector *Detector, cv::Mat img, float threshold);
		std::vector<ofVec4f> ImageTextValue(string Textlink);
		void drawRect(std::vector<ofVec4f> Value, ofColor color, std::vector<int> name, std::vector<float> confi);
		void human_drawRect(std::vector<ofVec4f> Value, ofColor color);
		void Reedclassname(string Textlink);

		//--------------------------------------------------------------
		int img_num;
		int Class_num;
		int img_filesize;
		bool img_Single;
		bool WebCam;
		String ClassList[81];

		//--------------------------------------------------------------
		ofVideoPlayer video;
		ofImage InputImage, VideoImage;
		cv::Mat cv_image, BGRimages;

		ofVideoGrabber cam;

		std::vector<ofVec4f> PlateboxValue;

		ofTrueTypeFont verdana18;

		//--------------------------------------------------------------
		std::vector<float> confidence;
		std::vector<int> objectid;
		std::vector<ofVec4f> DetectorboxValue;

		Detector *DetectorArray[1];
		
};
