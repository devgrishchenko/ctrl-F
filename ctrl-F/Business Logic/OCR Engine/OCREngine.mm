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

- (UIImage*)processBuffer :(CMSampleBufferRef)sampleBuffer {
    
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    unsigned char *buffer = (unsigned char *)CVPixelBufferGetBaseAddress(imageBuffer);
    
    Mat matrix;
    
    ImageProcessor::Buffer2Mat(matrix, buffer,
                               (int)CVPixelBufferGetBytesPerRow(imageBuffer),
                               (int)CVPixelBufferGetHeight(imageBuffer),
                               (int)CVPixelBufferGetWidth(imageBuffer));
    
    CVPixelBufferUnlockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
    
    rectangle(matrix, cv::Rect(100, 300, 100, 100), Scalar(255, 255, 0), 10);
    
    return [OCREngine convertMatToImage:matrix];
//    CVPixelBufferLockBaseAddress(imageBuffer, 0);
//
//    ImageProcessor::Mat2Buffer(matrix, buffer);
//
//    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
}

// MARK: - Converts Mat to UIImage

+ (UIImage *)convertMatToImage :(Mat)mat {
    
    NSData *data = [NSData dataWithBytes:mat.data length:mat.elemSize() * mat.total()];
    CGColorSpaceRef colorSpace;
    
    (mat.elemSize() == 1) ? colorSpace = CGColorSpaceCreateDeviceGray() : colorSpace = CGColorSpaceCreateDeviceRGB();
    
    CGDataProviderRef provider = CGDataProviderCreateWithCFData((__bridge CFDataRef)data);
    
    CGImageRef imageRef = CGImageCreate(mat.cols,
                                        mat.rows,
                                        8,
                                        8 * mat.elemSize(),
                                        mat.step[0],
                                        colorSpace,
                                        kCGImageAlphaNone|
                                        kCGBitmapByteOrderDefault,
                                        provider,
                                        NULL,
                                        false,
                                        kCGRenderingIntentDefault);
    
    UIImage *image = [UIImage imageWithCGImage:imageRef];
    
    //: Clean up
    CGImageRelease(imageRef);
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpace);
    
    return image;
}
@end
