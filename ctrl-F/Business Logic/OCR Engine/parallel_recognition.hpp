//
//  parallel_recognition.hpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-06-14.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#ifndef parallel_recognition_hpp
#define parallel_recognition_hpp

#include <stdio.h>
#include "character_contour.hpp"
#include "image_processor.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/ml/ml.hpp>

#define RESIZED_IMAGE_WIDTH  20
#define RESIZED_IMAGE_HEIGHT 30

using namespace std;
using namespace cv;
using namespace ml;

class ParallelRecognition : public ParallelLoopBody {
    
private:
    
    Ptr<KNearest> _knn;
    Mat &_matrix;
    
public:
    
    ParallelRecognition(const Ptr<KNearest> knn, Mat &matrix);
    
    void DetectContours(Mat &processedMatrix, vector<vector<cv::Point>> &characterContours) const;
    void DetectWord(vector<CharacterContour> &validCharacterContours, Mat &originalMatrix, Mat &processedMatrix) const;
    void Pipeline() const;
    
    virtual void operator ()(const Range& range) const {
        
        for (unsigned int i = range.start; i < range.end; i++) {
            
            Pipeline();
        }
    }
    
    
    ParallelRecognition& operator = (const ParallelRecognition &) {
        
        return *this;
    };
};
#endif
