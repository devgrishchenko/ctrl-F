//
//  OCREngine.m
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-29.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#import "OCREngine.h"
#import "character_recognition.hpp"

@implementation OCREngine

CharacterRecognition *_characterRecognition;


- (instancetype)init {
    
    if (self = [super init]) {
        
        _characterRecognition = new CharacterRecognition();
    }
    
    return self;
}


- (void)processBuffer :(CMSampleBufferRef)sampleBuffer {
    
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    unsigned char *buffer = (unsigned char *)CVPixelBufferGetBaseAddress(imageBuffer);
    
    Mat matrix;
    
    ImageProcessor::Buffer2Mat(matrix, buffer,
                               (int)CVPixelBufferGetBytesPerRow(imageBuffer),
                               (int)CVPixelBufferGetHeight(imageBuffer),
                               (int)CVPixelBufferGetWidth(imageBuffer));
    
    CVPixelBufferUnlockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
    
    //: Recognition
    _characterRecognition->DetectContours(matrix);
    
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    ImageProcessor::Mat2Buffer(matrix, buffer);

    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
    
    matrix.release();
}
@end
