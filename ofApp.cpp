#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->font.loadFont("fonts/msgothic.ttc", 28, true, true, true);
	this->word = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
}

//--------------------------------------------------------------
void ofApp::update() {


}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSeedRandom(39);

	int span = 33;
	for (int x = 4; x < ofGetWindowWidth(); x += span) {

		int y_start = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035), 0, 1, 0, 1320);
		for (int i = 0; i < 40; i++) {

			auto y = (int)(y_start + i * span) % 1320 - 400;
			auto location = glm::vec2(x, y);

			ofPushMatrix();
			ofTranslate(location);
			
			ofPath chara_path = this->font.getCharacterAsPoints(this->word[(int)ofRandom(this->word.size())], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofNoFill();
			ofSetColor(239);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					ofVertex(vertex);
				}
			}
			ofEndShape(true);

			ofPopMatrix();
		}
	}

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}