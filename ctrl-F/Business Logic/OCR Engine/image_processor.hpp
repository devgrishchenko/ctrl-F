//
//  image_processor.hpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-29.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#ifndef image_processor_hpp
#define image_processor_hpp

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;


class ImageProcessor {
    
public:
    
    static void ProcessMat(Mat &matrix, Mat &processedMatrix);
    static void Mat2Buffer(Mat &matrix, unsigned char *buffer);
    static void Buffer2Mat(Mat &matrix, unsigned char *buffer, const int &bytesPerRow, const int &height, const int &width);
};
#endif
