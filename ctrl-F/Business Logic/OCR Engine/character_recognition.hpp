//
//  character_recognition.hpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#ifndef character_recognition_hpp
#define character_recognition_hpp

#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include "image_processor.hpp"
#include "character_contour.hpp"
#include <stdio.h>
#include <pthread.h>

#define RESIZED_IMAGE_WIDTH  20
#define RESIZED_IMAGE_HEIGHT 30

using namespace std;
using namespace cv;
using namespace ml;


class CharacterRecognition {
    
private:
    
    Ptr<SVM> _svm;
  
public:
    
    CharacterRecognition(const string &modelPath);
    void DetectContours(Mat &processedMatrix, vector<vector<cv::Point>> &characterContours);
    void DetectWord(vector<CharacterContour> &validCharacterContours, Mat &originalMatrix, Mat &processedMatrix);
    void Pipeline(Mat &matrix);
    void *ParallelLoop(void *threadId);
};
#endif
