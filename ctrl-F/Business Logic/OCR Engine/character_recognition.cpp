//
//  character_recognition.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "character_recognition.hpp"


void CharacterRecognition::DetectContours(Mat &processedMatrix, vector<vector<Point>> &characterContours) {
    
    //: Finds contours on the image and returns vector
    findContours(processedMatrix.clone(), characterContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}


void CharacterRecognition::Pipeline(Mat &matix) {
    
    Mat processedMatrix;
    vector<vector<Point>> characterContours;
    vector<CharacterContour> validCharacterContours;
    
    ImageProcessor::ProcessMat(matix, processedMatrix);
    this->DetectContours(processedMatrix, characterContours);
    CharacterContour::FilterCharacterContours(characterContours, validCharacterContours);
    
    for (unsigned i = 0; i < validCharacterContours.size(); i++) {
        
        rectangle(matix, validCharacterContours[i].GetCharRect(), Scalar(255, 255, 0), 1);
    }
}
