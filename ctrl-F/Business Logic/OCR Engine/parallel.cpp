//
//  parallel.hpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-06-13.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include <stdio.h>
#include "character_contour.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/ml/ml.hpp>

#define RESIZED_IMAGE_WIDTH  20
#define RESIZED_IMAGE_HEIGHT 30

using namespace std;
using namespace cv;
using namespace ml;

class Parallel : public ParallelLoopBody {
    
private:
    
    Ptr<SVM> _svm;
    vector<CharacterContour> _validCharacterContours;
    Mat &_originalMatrix;
    Mat _processedMatrix;
    
    
public:
    
    Parallel(const vector<CharacterContour> validCharacterContours, Mat &originalMatrix, const Mat processedMatrix, const Ptr<SVM> svm)
    : _validCharacterContours(validCharacterContours), _originalMatrix(originalMatrix), _processedMatrix(processedMatrix), _svm(svm) {};
    
    virtual void operator ()(const Range& range) const {
        
        for (unsigned int i = range.start; i < range.end; i++) {
            
            Mat extractedChar;
            
            resize(_processedMatrix(_validCharacterContours[i].GetCharRect()), extractedChar, {RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT});
            extractedChar.convertTo(extractedChar, CV_32FC1);
            rectangle(_originalMatrix, _validCharacterContours[i].GetCharRect(), Scalar(255, 255, 0), 2);
            
            _svm->predict(extractedChar.reshape(1 , 1));
        }
    }
    
    
    Parallel& operator = (const Parallel &) {
        
        return *this;
    };
};
