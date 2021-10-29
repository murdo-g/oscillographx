#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	ofSetBackgroundAuto(false);
	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(54, 54, 54);
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	
	gui.setup(); // most of the time you don't need a name
	gui.add(decay.setup("Decay", 255, 0, 255));
	gui.add(brightness.setup("Brightness", 155, 0, 255));

	
	soundStream.printDeviceList();
	
	int bufferSize = 1024;

	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;


	ofSoundStreamSettings settings;

	// if you want to set the device id to be different than the default
	// auto devices = soundStream.getDeviceList();
	// settings.device = devices[4];

	// you can also get devices for an specific api
	// auto devices = soundStream.getDevicesByApi(ofSoundDevice::Api::PULSE);
	// settings.device = devices[0];

	// or get the default device for an specific api:
	// settings.api = ofSoundDevice::Api::PULSE;

	// or by name
	auto devices = soundStream.getMatchingDevices("default");
	if(!devices.empty()){
		settings.setInDevice(devices[0]);
	}

	settings.setInListener(this);
	settings.sampleRate = 96000;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 2;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);
	

}

//--------------------------------------------------------------
void ofApp::update(){
	//lets scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);

	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
		ofSetColor(10, 10, 10, decay);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofDrawRectangle(0, 0, WIN_WIDTH, WIN_HEIGHT);
		
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofSetColor(127, 127, 255, brightness);

		ofSetLineWidth(2);
		ofPolyline polyline;

			//ofBeginShape();
			for (unsigned int i = 0; i < left.size(); i++){
				polyline.curveTo(WIN_WIDTH*0.5 + left[i]*WIN_WIDTH, WIN_HEIGHT*0.5 + right[i]*WIN_HEIGHT);
				//ofVertex(512 + left[i]*1024.0f, 250 + right[i]*768.0f);
			}

			polyline.draw();
		gui.draw();

}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (size_t i = 0; i < input.getNumFrames(); i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;

		numCounted+=2;
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	if( key == 's' ){
		soundStream.start();
	}
	
	if( key == 'e' ){
		soundStream.stop();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

