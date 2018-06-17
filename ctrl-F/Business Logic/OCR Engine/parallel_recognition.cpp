//
//  parallel_recognition.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-06-14.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "parallel_recognition.hpp"


ParallelRecognition::ParallelRecognition(const Ptr<KNearest> knn, Mat &matrix) : _matrix(matrix) {
    
    _knn = knn;
}


void ParallelRecognition::DetectContours(Mat &processedMatrix, vector<vector<Point>> &characterContours) const {
    
    //: Finds contours on the image and returns vector
    findContours(processedMatrix.clone(), characterContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}


void ParallelRecognition::DetectWord(vector<CharacterContour> &validCharacterContours, Mat &originalMatrix, Mat &processedMatrix) const {
    
    if (validCharacterContours.size() == 0) return;
    
    //    double time = (double) getTickCount();
    //
    //    Parallel parallel(validCharacterContours, originalMatrix, processedMatrix, _knn);
    //    parallel_for_(Range(0, (int)validCharacterContours.size()), parallel);
    //
    //    time = ((double) getTickCount() - time) / getTickFrequency();
    //    cout << "Take: " << time << " s" << endl;
}


void ParallelRecognition::Pipeline() const {
    
    double time = (double) getTickCount();
    Mat processedMatrix;
    vector<vector<Point>> characterContours;
    vector<CharacterContour> validCharacterContours;
    
    ImageProcessor::ProcessMat(_matrix, processedMatrix);
    this->DetectContours(processedMatrix, characterContours);
    CharacterContour::FilterCharacterContours(characterContours, validCharacterContours);
    
    characterContours.clear();
    
    this->DetectWord(validCharacterContours, _matrix, processedMatrix);
    time = ((double) getTickCount() - time) / getTickFrequency();
    cout << "Take: " << time << " s" << endl;
}
