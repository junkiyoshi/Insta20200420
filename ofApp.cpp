#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->frame.clear();
	int number_of_satellite = 4;
	int number_of_log = 50;
	int base_radius = 80;

	for (int i = 0; i < 8; i++) {

		auto base_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto base_location = glm::vec3(
			ofMap(ofNoise(base_seed.x, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -500, 500),
			ofMap(ofNoise(base_seed.y, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -500, 500),
			ofMap(ofNoise(base_seed.z, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -500, 500));

		for (int j = 0; j < number_of_satellite; j++) {

			float noise_seed_x = ofRandom(1000);
			float noise_seed_y = ofRandom(1000);
			auto location = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
			location = glm::normalize(location) * base_radius * 1.2;

			for (int k = 0; k < number_of_log; k++) {

				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + k) * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + k) * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
				auto tmp_base_location = glm::vec3(
					ofMap(ofNoise(base_seed.x, (ofGetFrameNum() + k) * 0.005), 0, 1, -500, 500),
					ofMap(ofNoise(base_seed.y, (ofGetFrameNum() + k) * 0.005), 0, 1, -500, 500),
					ofMap(ofNoise(base_seed.z, (ofGetFrameNum() + k) * 0.005), 0, 1, -500, 500));
				auto loc = tmp_base_location + glm::vec4(location, 0) * rotation_y * rotation_x;
				this->frame.addVertex(loc);
				
				ofColor c;
				c.setHsb(ofRandom(255), 255, 255);
				this->frame.addColor(ofColor(c, ofMap(k, 0, number_of_log, 25, 255)));
			}
		}
	}

	for (int i = 0; i < this->frame.getNumVertices(); i++) {

		for (int k = i + 1; k < this->frame.getNumVertices(); k++) {

			if (glm::distance(this->frame.getVertex(i), this->frame.getVertex(k)) < 30) {

				this->frame.addIndex(i); this->frame.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}