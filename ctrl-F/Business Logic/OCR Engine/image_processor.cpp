//
//  image_processor.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-29.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "image_processor.hpp"


void ImageProcessor::Mat2Buffer(Mat &matrix, uchar *buffer) {
    
    
}


void ImageProcessor::Buffer2Mat(Mat &matrix, uchar *buffer, const int &height, const int &width) {
    
    matrix = Mat(height, width, CV_8UC4, buffer);
}
