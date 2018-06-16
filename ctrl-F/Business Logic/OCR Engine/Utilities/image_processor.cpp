//
//  image_processor.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-29.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "image_processor.hpp"


void ImageProcessor::Mat2Buffer(Mat &matrix, unsigned char *buffer) {
    
    buffer = matrix.data;
}


void ImageProcessor::Buffer2Mat(Mat &matrix, unsigned char *buffer, const int &bytesPerRow, const int &height, const int &width) {
    
    matrix = Mat(height, width, CV_8UC4, buffer, bytesPerRow);
}


void ImageProcessor::ProcessMat(Mat &matrix, Mat &processedMatrix) {
    
    //: Converts image to the grayscale
    cvtColor(matrix, processedMatrix, CV_BGR2GRAY);
    
    //: Convert grayscale to threshold
    threshold(processedMatrix, processedMatrix, 150, 255, THRESH_BINARY_INV);
}
