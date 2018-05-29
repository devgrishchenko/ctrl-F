//
//  OCREngine.m
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-29.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#import "OCREngine.h"
#import "image_processor.hpp"

@implementation OCREngine

- (void)processBuffer :(CMSampleBufferRef)buffer {
    
    CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(buffer);
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    
    //Processing here
    int bufferWidth = (int)CVPixelBufferGetWidth(pixelBuffer);
    int bufferHeight = (int)CVPixelBufferGetHeight(pixelBuffer);
    unsigned char *pixel = (unsigned char *)CVPixelBufferGetBaseAddress(pixelBuffer);
    
    Mat matrix;
    
    ImageProcessor::Buffer2Mat(matrix, pixel, bufferHeight, bufferWidth);
}
@end
