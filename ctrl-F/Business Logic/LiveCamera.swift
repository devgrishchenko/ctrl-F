//
//  LiveCamera.swift
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-28.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

import AVFoundation
import UIKit


public class LiveCamera: NSObject {
    
    private var session: AVCaptureSession!
    private var layer: AVSampleBufferDisplayLayer!
    
    
    public init(with layerView: UIView) {
        super.init()
        
        self.configSession()
        
        self.layer = AVSampleBufferDisplayLayer()
        self.layer.frame = layerView.bounds
        layerView.layer.addSublayer(self.layer)
    }
    
    
    private func configSession() {
        
        self.session = AVCaptureSession()
        self.session.sessionPreset = .hd1920x1080
        
        //: Device capture. Filters for the front camera
        let deviceCapture = AVCaptureDevice.devices(for: .video)
            .map { $0 }
            .filter { $0.position == .back}
            .first!
        
        do {
            
            //: Device input
            let deviceInput = try AVCaptureDeviceInput(device: deviceCapture)
            
            //: Device output
            let deviceOutput = AVCaptureVideoDataOutput()
            deviceOutput.videoSettings = [kCVPixelBufferPixelFormatTypeKey as String: Int(kCVPixelFormatType_32BGRA)]
            deviceOutput.setSampleBufferDelegate(self, queue: DispatchQueue.global(qos: DispatchQoS.QoSClass.background))
            
            //: Session configuration
            self.session.beginConfiguration()
            self.session.addInput(deviceInput)
            self.session.addOutput(deviceOutput)
            self.session.commitConfiguration()
            self.session.outputs[0].connections[0].videoOrientation = .portrait
        }
        catch {
            
            print(error)
        }
    }
    
    
    public func runSession() {
        
        self.session.startRunning()
    }
}


//MARK: - AVCapture Delegate

extension LiveCamera: AVCaptureVideoDataOutputSampleBufferDelegate, AVCaptureMetadataOutputObjectsDelegate {
    
    
    public func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        
        self.layer.enqueue(sampleBuffer)
    }
}
