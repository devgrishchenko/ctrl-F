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

- (void)processBuffer :(CMSampleBufferRef)sampleBuffer {
    
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    unsigned char *buffer = (unsigned char *)CVPixelBufferGetBaseAddress(imageBuffer);
    
    Mat matrix;
    Mat processedMatrix;
    
    ImageProcessor::Buffer2Mat(matrix, buffer,
                               (int)CVPixelBufferGetBytesPerRow(imageBuffer),
                               (int)CVPixelBufferGetHeight(imageBuffer),
                               (int)CVPixelBufferGetWidth(imageBuffer));
    
    CVPixelBufferUnlockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
    
    //: Recognition
    ImageProcessor::ProcessMat(matrix, processedMatrix);
    
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    ImageProcessor::Mat2Buffer(matrix, buffer);

    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
    
    matrix.release();
    processedMatrix.release();
}
@end
