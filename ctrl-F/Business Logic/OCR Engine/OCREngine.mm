//
//  OCREngine.m
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-29.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#import "OCREngine.h"
#include <opencv2/imgproc/imgproc.hpp>
#import "image_processor.hpp"

@implementation OCREngine

- (void)processBuffer :(CMSampleBufferRef)buffer {
    
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(buffer);
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    unsigned char *buf = (unsigned char *)CVPixelBufferGetBaseAddress(imageBuffer);
    
    Mat matrix;
    
    ImageProcessor::Buffer2Mat(matrix, buf, (int)CVPixelBufferGetHeight(imageBuffer), (int)CVPixelBufferGetWidth(imageBuffer));
    
    CVPixelBufferUnlockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
    
    rectangle(matrix, cv::Rect(0, 0, 100, 100), Scalar(255, 255, 0), 10);
    
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    ImageProcessor::Mat2Buffer(matrix, buf);
    
    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
}
@end
