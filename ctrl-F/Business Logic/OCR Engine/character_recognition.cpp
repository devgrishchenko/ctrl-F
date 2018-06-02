//
//  character_recognition.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "character_recognition.hpp"


CharacterRecognition::CharacterRecognition(const string &modelPath) {
    
    _kNearest = Algorithm::load<KNearest>(modelPath);
}


void CharacterRecognition::DetectContours(Mat &processedMatrix, vector<vector<Point>> &characterContours) {
    
    //: Finds contours on the image and returns vector
    findContours(processedMatrix.clone(), characterContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}


void CharacterRecognition::DetectWord(vector<CharacterContour> &validCharacterContours, Mat &originalMatrix, Mat &processedMatrix) {
    
    if (validCharacterContours.size() == 0) return;
    
    vector<vector<CharacterContour>> textMatrix;
    
    CharacterContour::SortCharacterContours(validCharacterContours, textMatrix);
    
    //: Line in text
    for (int iLine = 0; iLine < textMatrix.size(); iLine++) {
        
        //: Each char in line
        for (int iChar = 0; iChar < textMatrix[iLine].size(); iChar++) {
            
            Mat extractedChar;
            
            resize(processedMatrix(textMatrix[iLine][iChar].GetCharRect()), extractedChar, {RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT});
            extractedChar.convertTo(extractedChar, CV_32FC1);
            rectangle(originalMatrix, textMatrix[iLine][iChar].GetCharRect(), Scalar(255, 255, 0), 2);
            
            cout << _kNearest->predict(extractedChar.rreshape(1 , 1)) << endl;
        }
    }
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
