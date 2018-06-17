//
//  ViewController.swift
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-28.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITextFieldDelegate {

    private var layerView: UIView!
    private var liveCamera: LiveCamera!
    private var searchedWord: UITextField!
    private let blurEffectViewTag = 101;
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.layerView = UIView(frame: self.view.frame)
        self.view.addSubview(self.layerView)
        self.layerView.anchor(top: self.view.topAnchor, left: self.view.leftAnchor, bottom: self.view.bottomAnchor, right: self.view.rightAnchor, topConstant: 0, leftConstant: 0, bottomConstant: 0, rightConstant: 0, widthConstant: 0, heightConstant: 0)
        
        self.liveCamera = LiveCamera(with: self.layerView)
        self.liveCamera.runSession()
        
        self.setSearchedWord()
    }

    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    
    override var prefersStatusBarHidden: Bool {
        
        return true
    }
    
    
    // MARK: - Input searched word
    
    private func setSearchedWord() {
        
        self.searchedWord = {
           
            let textField = UITextField()
            textField.delegate = self
            textField.backgroundColor = UIColor(red: 211/255, green: 211/255, blue: 211/255, alpha: 0.5)
            textField.textColor = .white
            textField.layer.cornerRadius = 5
            
            return textField
        }()
        
        self.view.addSubview(self.searchedWord)
        self.searchedWord.anchor(top: self.view.topAnchor, left: self.view.leftAnchor, bottom: nil, right: self.view.rightAnchor, topConstant: 20, leftConstant: 20, bottomConstant: 0, rightConstant: 20, widthConstant: 0, heightConstant: 40)
    }
    
    
    @objc
    private func hideKeyboard(_ sender: UITapGestureRecognizer) {
        
        self.view.endEditing(true)
        self.unblurBackground()
    }
    
    
    internal func textFieldShouldBeginEditing(_ textField: UITextField) -> Bool {
        
        if textField == self.searchedWord {
            
            self.blurBackground()
        }
        
        return true
    }
    
    
    internal func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        
        self.view.endEditing(true)
        self.unblurBackground()
        
        return false
    }
    
    
    private func blurBackground() {
        
        let tap = UITapGestureRecognizer(target: self, action: #selector(hideKeyboard(_:)))
        
        let blurEffect = UIBlurEffect(style: .light)
        let blurEffectView = UIVisualEffectView(effect: blurEffect)
        blurEffectView.frame = self.view.bounds
        blurEffectView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        
        blurEffectView.tag = self.blurEffectViewTag
        blurEffectView.isUserInteractionEnabled = true
        blurEffectView.addGestureRecognizer(tap)
        
        self.view.addSubview(blurEffectView)
        self.view.bringSubview(toFront: self.searchedWord)
    }
    
    
    private func unblurBackground() {
        
        for view in self.view.subviews {
            
            if let blurView = view as? UIVisualEffectView, blurView.tag == self.blurEffectViewTag {
                
                blurView.removeFromSuperview()
                
                self.liveCamera.setSearch(word: self.searchedWord.text!.lowercased())
            }
        }
    }
}
