//
//  character_recognition.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "character_recognition.hpp"


CharacterRecognition::CharacterRecognition(const string &modelPath) {
    
    _svm = Algorithm::load<SVM>(modelPath);
}


void CharacterRecognition::DetectContours(Mat &processedMatrix, vector<vector<Point>> &characterContours) {
    
    //: Finds contours on the image and returns vector
    findContours(processedMatrix.clone(), characterContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}


void CharacterRecognition::DetectWord(vector<CharacterContour> &validCharacterContours, Mat &originalMatrix, Mat &processedMatrix) {
    
    if (validCharacterContours.size() == 0) return;
    
    vector<vector<CharacterContour>> textMatrix;
    CharacterContour::SortCharacterContours(validCharacterContours, textMatrix);
    
    Parallel parallel(textMatrix, originalMatrix, processedMatrix, _svm);
    parallel_for_(Range(0, (int)textMatrix.size()), parallel);

    textMatrix.clear();
}


void CharacterRecognition::Pipeline(Mat &matrix) {
    
    Mat processedMatrix;
    vector<vector<Point>> characterContours;
    vector<CharacterContour> validCharacterContours;
    
    ImageProcessor::ProcessMat(matrix, processedMatrix);
    this->DetectContours(processedMatrix, characterContours);
    CharacterContour::FilterCharacterContours(characterContours, validCharacterContours);
    
    characterContours.clear();
    
    this->DetectWord(validCharacterContours, matrix, processedMatrix);
    
    matrix.release();
}
