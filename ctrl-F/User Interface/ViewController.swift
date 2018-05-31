//
//  ViewController.swift
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-28.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    private var layerView: UIView!
    private var liveCamera: LiveCamera!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        let imge = UIImageView(frame: self.view.frame)
        self.view.addSubview(imge)
        self.layerView = UIView(frame: self.view.frame)
        self.view.addSubview(self.layerView)
        self.layerView.anchor(top: self.view.topAnchor, left: self.view.leftAnchor, bottom: self.view.bottomAnchor, right: self.view.rightAnchor, topConstant: 0, leftConstant: 0, bottomConstant: 0, rightConstant: 0, widthConstant: 0, heightConstant: 0)
        
        self.liveCamera = LiveCamera(with: self.layerView, img: imge)
        self.liveCamera.runSession()
    }

    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
}
