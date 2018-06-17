//
//  character_recognition.hpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#ifndef character_recognition_hpp
#define character_recognition_hpp

#include "image_processor.hpp"
#include "parallel.cpp"


class CharacterRecognition {
    
private:
    
    Ptr<KNearest> _knn;
  
public:
    
    CharacterRecognition(const string &modelPath);
    void DetectContours(Mat &processedMatrix, vector<vector<cv::Point>> &characterContours);
    void DetectWord(vector<CharacterContour> &validCharacterContours, Mat &originalMatrix, Mat &processedMatrix, const string word);
    void Pipeline(Mat &matrix, const string word);
};
#endif
