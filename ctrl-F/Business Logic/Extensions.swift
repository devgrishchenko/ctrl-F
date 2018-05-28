//
//  Extensions.swift
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-28.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

import UIKit


// MARK: - Sets anchor to the view

extension UIView {
    
    
    public func anchor(top: NSLayoutYAxisAnchor? = nil, left: NSLayoutXAxisAnchor? = nil, bottom: NSLayoutYAxisAnchor? = nil, right: NSLayoutXAxisAnchor? = nil, topConstant: CGFloat = 0, leftConstant: CGFloat = 0, bottomConstant: CGFloat = 0, rightConstant: CGFloat = 0, widthConstant: CGFloat = 0, heightConstant: CGFloat = 0) {
        
        //: Disables default constraints to prevent collisions
        translatesAutoresizingMaskIntoConstraints = false
        
        var anchors = [NSLayoutConstraint]()
        
        //: Appends anchor properties if they are not null
        if let top = top {
            
            anchors.append(topAnchor.constraint(equalTo: top, constant: topConstant))
        }
        
        if let left = left {
            
            anchors.append(leftAnchor.constraint(equalTo: left, constant: leftConstant))
        }
        
        if let bottom = bottom {
            
            anchors.append(bottomAnchor.constraint(equalTo: bottom, constant: -bottomConstant))
        }
        
        if let right = right {
            
            anchors.append(rightAnchor.constraint(equalTo: right, constant: -rightConstant))
        }
        
        if widthConstant > 0 {
            
            anchors.append(widthAnchor.constraint(equalToConstant: widthConstant))
        }
        
        if heightConstant > 0 {
            
            anchors.append(heightAnchor.constraint(equalToConstant: heightConstant))
        }
        
        //: Activities anchors
        anchors.forEach({ $0.isActive = true })
        
        _ = anchors
    }
}
