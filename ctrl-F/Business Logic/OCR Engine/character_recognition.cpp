//
//  character_recognition.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "character_recognition.hpp"


CharacterRecognition::CharacterRecognition(const string &modelPath) {
    
    CharacterRecognition::_svm = Algorithm::load<SVM>(modelPath);
}


void CharacterRecognition::DetectContours(Mat &processedMatrix, vector<vector<Point>> &characterContours) {
    
    //: Finds contours on the image and returns vector
    findContours(processedMatrix.clone(), characterContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}


void CharacterRecognition::DetectWord(vector<CharacterContour> &validCharacterContours, Mat &originalMatrix, Mat &processedMatrix) {
    
    if (validCharacterContours.size() == 0) return;
    
//    vector<vector<CharacterContour>> textMatrix;
    
    for (unsigned int i = 0; i < validCharacterContours.size(); i++) {

        Mat extractedChar;

        resize(processedMatrix(validCharacterContours[i].GetCharRect()), extractedChar, {RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT});
        extractedChar.convertTo(extractedChar, CV_32FC1);
        rectangle(originalMatrix, validCharacterContours[i].GetCharRect(), Scalar(255, 255, 0), 2);

        _svm->predict(extractedChar.reshape(1 , 1));
    }
    
//    CharacterContour::SortCharacterContours(validCharacterContours, textMatrix);
    
//    //: Line in text
//    for (int iLine = 0; iLine < textMatrix.size(); iLine++) {
//
//        //: Each char in line
//        for (int iChar = 0; iChar < textMatrix[iLine].size(); iChar++) {
//
//            Mat extractedChar;
//
//            resize(processedMatrix(textMatrix[iLine][iChar].GetCharRect()), extractedChar, {RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT});
//            extractedChar.convertTo(extractedChar, CV_32FC1);
//            rectangle(originalMatrix, textMatrix[iLine][iChar].GetCharRect(), Scalar(255, 255, 0), 2);
//
//            cout << _svm->predict(extractedChar.reshape(1 , 1)) << endl;
//        }
//    }
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
}


/*
 vector<CharacterContour> temp(_validCharacterContours);
 Mat processedImage = _processedImage.clone();
 
 long start = (long)threadId * (temp.size() / NUM_THREADS);
 long end = start + temp.size() / NUM_THREADS + ((long)threadId == NUM_THREADS - 1 ? temp.size() % NUM_THREADS : 0) - 1;
 
 if (temp.size() > 0 && start > 0 && end > 0 && start != end) {
 
 for (unsigned long i = start; i < end; i++) {
 
 Mat extractedChar;
 
 resize(processedImage(temp[i].GetCharRect()), extractedChar, {RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT});
 extractedChar.convertTo(extractedChar, CV_32FC1);
 rectangle(_image, temp[i].GetCharRect(), Scalar(255, 255, 0), 2);
 
 cout << char(int(_svm->predict(extractedChar.reshape(1 , 1)))) << endl;
 
 extractedChar.release();
 }
 }
 
 temp.clear();
 processedImage.release();
 */
