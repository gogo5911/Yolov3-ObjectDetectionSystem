#include "ofApp.h"

///IMAGE(1) , VIDEO(2), WEBCAM(3)
///�̹��� Ȥ�� ���� ���� ����
#define MODE 1
#define CAM_WIDTH 1280
#define CAM_HEIGHT 960

using namespace cv;
//--------------------------------------------------------------
void ofApp::setup(){

	///�̹��� Ȥ�� ���� �ε� ����
#if MODE == 1

	///�̹��� 1�� Ȥ�� 1�� �̻� ����
	///1�� -> true
	///1�� �̻� -> false
	img_Single = false;


#elif MODE == 2 
	
	video.load("Videos/Sample.mp4");
	video.play();


#else 
	
	cam.setup(CAM_WIDTH, CAM_HEIGHT);


#endif
	///ã���� �ϴ� Class ��
	Class_num = 1;

	///cfg, weights 
	DetectorArray[0] = new Detector("data/yolofile/yolov3.cfg", "data/yolofile/yolov3.weights");

	///���� ����
	ofSetLineWidth(4);
	
	///���� �̹��� �� (���� �̹������� ���)
	img_num = 0;

	///font ����
	verdana18.load("font/Verdana_Bold.ttf", 14, true, true);
	verdana18.setLineHeight(26.0f);
	verdana18.setLetterSpacing(1.037);


	///Class �̸� �������� �κ�
	Reedclassname("yolofile/coco.names");

}

//--------------------------------------------------------------
void ofApp::update(){

#if MODE == 1 
#elif MODE == 2

	video.update();

#else

	cam.update();
	if (cam.isInitialized())
	{
		WebCam = true;
		ofSetWindowShape(CAM_WIDTH, CAM_HEIGHT);
	}
	else { WebCam = false; }


#endif

}

//--------------------------------------------------------------
void ofApp::draw(){

#if MODE == 1

	if (img_Single){

		
		string img_path = "Images/img/0.jpg";   ///�̹��� ��� �Է�
		InputImage.load(img_path);
		cv_image = ofxCv::toCv(InputImage);
		BGRimages = makeImageBGR24(cv_image);  ///RGB�̹��� BGR�̹����� ����

		DetectorboxValue = box(DetectorArray[0], BGRimages, 0.7);
		confidence = confi(DetectorArray[0], BGRimages, 0.7);
		objectid = objid(DetectorArray[0], BGRimages, 0.7);

		///���� �̹��� �ٿ�� �ڽ� ���
		string txt_path = "Images/txt/0.txt";

		PlateboxValue = ImageTextValue(txt_path);

		///Mat �̹��� ofimage�� ��ȯ
		ofPixels t;
		ofxCv::toOf(BGRimages, t);
		ofImage BGRInputImage = ofImage(t);

		BGRInputImage.draw(0, 0, InputImage.getWidth(), InputImage.getHeight());
		human_drawRect(PlateboxValue, ofColor(0, 255, 0)); /// human Detect �ʷϻ�
		drawRect(DetectorboxValue, ofColor(255, 0, 0), objectid, confidence);  /// Yolo Detect ������

	}
	else {

		string path = "data/Images/img";
		img_filesize = FileSize(path);




		char ImageTmpChar[255];
		sprintf(ImageTmpChar, "Images/img/%1d.jpg\0", img_num); ///���� ������ ����� ��� ����������մϴ�.
		InputImage.load(ImageTmpChar);

		cv_image = ofxCv::toCv(InputImage);
		BGRimages = makeImageBGR24(cv_image);  ///RGB�̹��� BGR�̹����� ����

		DetectorboxValue = box(DetectorArray[0], BGRimages, 0.7);
		confidence = confi(DetectorArray[0], BGRimages, 0.7);
		objectid = objid(DetectorArray[0], BGRimages, 0.7);

		///���� �̹��� �ٿ�� �ڽ� ���
		char TextTmpChar[255];
		sprintf(TextTmpChar, "Images/txt/%1d.txt\0", img_num); ///���� ������ ����� ��� ����������մϴ�.
		PlateboxValue = ImageTextValue(TextTmpChar);

		///Mat �̹��� ofimage�� ��ȯ
		ofPixels t;
		ofxCv::toOf(BGRimages, t);
		ofImage BGRInputImage = ofImage(t);

		BGRInputImage.draw(0, 0, InputImage.getWidth(), InputImage.getHeight());
		human_drawRect(PlateboxValue, ofColor(0, 255, 0)); /// human Detect �ʷϻ�
		drawRect(DetectorboxValue, ofColor(255, 0, 0), objectid, confidence);  /// Yolo Detect ������


	
	
	}

	
#elif MODE == 2

	if (video.isFrameNew()) {

		ofPixels pixels = video.getPixels();
		VideoImage.setFromPixels(pixels);

		cv_image = ofxCv::toCv(VideoImage);
		BGRimages = makeImageBGR24(cv_image);  ///RGB�̹��� BGR�̹����� ����

		DetectorboxValue = box(DetectorArray[0], BGRimages, 0.7);
		confidence = confi(DetectorArray[0], BGRimages, 0.7);
		objectid = objid(DetectorArray[0], BGRimages, 0.7);


		ofPixels t;
		ofxCv::toOf(BGRimages, t);
		ofImage BGRInputImage = ofImage(t);

		BGRInputImage.draw(0, 0, video.getWidth(), video.getHeight());

		drawRect(DetectorboxValue, ofColor(255, 0, 0), objectid, confidence);  /// Yolo Detect ������
	}

#else

	if (WebCam) {

		ofPixels pixels = cam.getPixels();
		VideoImage.setFromPixels(pixels);

		cv_image = ofxCv::toCv(VideoImage);
		BGRimages = makeImageBGR24(cv_image);  ///RGB�̹��� BGR�̹����� ����

		DetectorboxValue = box(DetectorArray[0], BGRimages, 0.7);
		confidence = confi(DetectorArray[0], BGRimages, 0.7);
		objectid = objid(DetectorArray[0], BGRimages, 0.7);

		ofPixels t;
		ofxCv::toOf(BGRimages, t);
		ofImage BGRInputImage = ofImage(t);

		BGRInputImage.draw(0, 0, cam.getWidth(), cam.getHeight());

		drawRect(DetectorboxValue, ofColor(255, 0, 0), objectid, confidence);  /// Yolo Detect ������

	}
	

#endif


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

#if MODE == 1
	if (!img_Single) {	
		switch (key) {
		case 'q':

			if (img_num == img_filesize - 1) {
				img_num = img_filesize - 1;
			}
			else {
				img_num++;
			}
			break;

			break;

		case 'w':

			if (img_num == 0) {
				img_num = 0;
			}
			else {
				img_num--;
			}
			break;

			break;
		}
	}
#elif MODE == 2
#else
#endif
}

int ofApp::FileSize(string path) {

	int Filenum = 0;
	typedef std::vector<std::string> stringvec;
	namespace fs = std::filesystem;
	stringvec v;
	for (const auto & entry : fs::directory_iterator(path)) {
		Filenum++;
	}
	if (Filenum == 0) {
		std::cout << "������ �����ϴ�." << endl;
	}
	return Filenum;
}

Mat ofApp::makeImageBGR24(cv::Mat img){

	Mat tmpimage;

	uchar* buffer = new uchar[img.rows * img.cols * 3];
	uchar* video_buffer;
	
	for (int i = 0; i < img.rows; ++i)
	{
		
		video_buffer = img.ptr<uchar>(i);
		for (int j = 0; j < 3 * img.cols; j += 3)
		{
			buffer[i * 3 * img.cols + j] = video_buffer[j];
			buffer[i * 3 * img.cols + j + 1] = video_buffer[j + 1];
			buffer[i * 3 * img.cols + j + 2] = video_buffer[j + 2];
		}
	}
	
	// char to cv::Mat
	cv::Mat input(img.rows, img.cols, CV_8UC3, buffer);
	tmpimage = input.clone();

	//cv::Mat camMats;
	//cv::cvtColor(tmpimage, camMats, CV_BGRA2GRAY);
	
	return tmpimage;
}

std::vector<ofVec4f> ofApp::box(Detector *Detector, cv::Mat img, float threshold) {

	std::vector<ofVec4f> tmpVector;
	std::vector<bbox_t> plateResult = Detector->detect(img, threshold);
	tmpVector.resize(plateResult.size());

	for (int i = 0; i < plateResult.size(); i++)
	{
		tmpVector[i].x = plateResult[i].x;
		tmpVector[i].y = plateResult[i].y;
		tmpVector[i].z = plateResult[i].w;
		tmpVector[i].w = plateResult[i].h;
	}

	return tmpVector;
}

std::vector<float> ofApp::confi(Detector *Detector, cv::Mat img, float threshold) {

		std::vector<float> tmpVector;
		std::vector<bbox_t> plateResult = Detector->detect(img, threshold);
		tmpVector.resize(plateResult.size());
		for (int i = 0; i < plateResult.size(); i++)
		{
			tmpVector[i] = plateResult[i].prob;
		}

		return tmpVector;

}

std::vector<int> ofApp::objid(Detector *Detector, cv::Mat img, float threshold) {

	std::vector<int> tmpVector;
	std::vector<bbox_t> plateResult = Detector->detect(img, threshold);
	tmpVector.resize(plateResult.size());
	for (int i = 0; i < plateResult.size(); i++)
	{
		tmpVector[i] = plateResult[i].obj_id;
	}

	return tmpVector;

}

void ofApp::Reedclassname(string Textlink) {

	vector < string > linesOfTheFile;
	ofBuffer buffer = ofBufferFromFile(Textlink);
	for (auto line : buffer.getLines()) {
		linesOfTheFile.push_back(line);
	}

	string tamp;

	for (int l = 0; l < linesOfTheFile.size(); l++) {
		tamp = ofFromString<string>(linesOfTheFile[l]);
		ClassList[l] = tamp;
	}


}


std::vector<ofVec4f> ofApp::ImageTextValue(string Textlink) {


	std::vector<ofVec4f> tmpvalue;

	vector < string > linesOfTheFile;
	ofBuffer buffer = ofBufferFromFile(Textlink);
	for (auto line : buffer.getLines()) {
		linesOfTheFile.push_back(line);
	}

	tmpvalue.resize(linesOfTheFile.size());

	string tamp;
	string tamptoken[6];
	int plus = 0;

	for (int l = 0; l < linesOfTheFile.size(); l++) {
		tamp = ofFromString<string>(linesOfTheFile[l]);
		std::istringstream ist(tamp);
		std::string token;
		plus = 0;

		while (std::getline(ist, token, ' ')) {
			tamptoken[plus] = token;
			if (plus == 6) { plus = 6; }
			else { plus++; }

		}
		tmpvalue[l].x = atof(tamptoken[1].c_str());
		tmpvalue[l].y = atof(tamptoken[2].c_str());
		tmpvalue[l].z = atof(tamptoken[3].c_str());
		tmpvalue[l].w = atof(tamptoken[4].c_str());


		int tmpw = InputImage.getWidth() * tmpvalue[l].z;
		int tmph = InputImage.getHeight() * tmpvalue[l].w;

		int tmpx = (InputImage.getWidth() * tmpvalue[l].x) - (tmpw / 2);
		int tmpy = (InputImage.getHeight() * tmpvalue[l].y) - (tmph / 2);

		tmpvalue[l].x = tmpx;
		tmpvalue[l].y = tmpy;
		tmpvalue[l].z = tmpw;
		tmpvalue[l].w = tmph;

	}

	return tmpvalue;

}

void ofApp::drawRect(std::vector<ofVec4f> Value, ofColor color, std::vector<int> name, std::vector<float> confi) {

	for (int j = 0; j < Value.size(); j++) {
		
		int num = name[j];
		string objProb;
		objProb = "" + ClassList[num] + " / " + ofToString(confi[j]*100);
					
		ofNoFill();
		ofSetColor(color);
		ofRect(Value[j].x, Value[j].y, Value[j].z, Value[j].w);

		ofFill();
		ofRect(Value[j].x, Value[j].y, Value[j].z, 50);
		ofNoFill();

		ofSetColor(0, 0, 0);
		verdana18.drawString(objProb, Value[j].x+10, Value[j].y+30);
		
		
		ofSetColor(255, 255, 255);
		ofFill();

	}

}

void ofApp::human_drawRect(std::vector<ofVec4f> Value, ofColor color) {

	for (int j = 0; j < Value.size(); j++) {


		ofNoFill();
		ofSetColor(color);
		ofRect(Value[j].x, Value[j].y, Value[j].z, Value[j].w);

		ofSetColor(255, 255, 255);
		ofFill();

	}

}