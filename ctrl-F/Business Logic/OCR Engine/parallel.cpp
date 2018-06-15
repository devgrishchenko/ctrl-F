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
    vector<vector<CharacterContour>> _textMatrix;
    Mat &_originalMatrix;
    Mat _processedMatrix;
    const string search = "has";
    
public:
    
    Parallel(const vector<vector<CharacterContour>> textMatrix, Mat &originalMatrix, const Mat processedMatrix, const Ptr<SVM> svm)
    : _textMatrix(textMatrix), _originalMatrix(originalMatrix), _processedMatrix(processedMatrix), _svm(svm) {};
    
    virtual void operator ()(const Range& range) const {
        
        for (unsigned int i = range.start; i < range.end; i++) {
            
            string line;
            vector<size_t> positions;
            
            for (unsigned int iLine = 0; iLine < _textMatrix[i].size(); iLine++) {
                
                Mat extractedChar;
    
                resize(_processedMatrix(_textMatrix[i][iLine].GetCharRect()), extractedChar, {RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT});
                extractedChar.convertTo(extractedChar, CV_32FC1);
    
                line += tolower(char(int(_svm->predict(extractedChar.reshape(1 , 1)))));
            }
            
            size_t pos = line.find(search, 0);

            while(pos != string::npos) {

                positions.push_back(pos);
                pos = line.find(search, pos + 1);
            }

            for (size_t p = 0; p < positions.size(); p++) {

                size_t lastIndex = positions[p] + search.length() - 1;
                
                rectangle(_originalMatrix,
                          cv::Rect(_textMatrix[i][positions[p]].GetCharRect().x,
                                   _textMatrix[i][positions[p]].GetCharRect().y,
                                   _textMatrix[i][lastIndex].GetCharRect().x
                                   + _textMatrix[i][lastIndex].GetCharRect().width
                                   - _textMatrix[i][positions[p]].GetCharRect().x,
                                   _textMatrix[i][lastIndex].GetCharRect().height),
                          Scalar(255, 255, 0), 2);
            }
        }
    }
    
    
    Parallel& operator = (const Parallel &) {
        
        return *this;
    };
};
