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
#import "image_processor.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;


class CharacterRecognition {
  
public:
    
    void DetectContours(Mat &matrix);
};
#endif
