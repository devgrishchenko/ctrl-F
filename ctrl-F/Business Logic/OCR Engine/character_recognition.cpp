//
//  character_recognition.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "character_recognition.hpp"


void CharacterRecognition::DetectContours(Mat &matrix) {
    
    vector<vector<Point>> charsContours;
    Mat processedMatrix;
    
    ImageProcessor::ProcessMat(matrix, processedMatrix);
    
    //: Finds contours on the image and returns vector
    findContours(processedMatrix.clone(), charsContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    for (unsigned int i = 0; i < charsContours.size(); i++) {
        
        rectangle(matrix, boundingRect(charsContours[i]), Scalar(255, 255, 0), 2);
    }
}
