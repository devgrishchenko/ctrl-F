//
//  AppDelegate.swift
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-28.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?


    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        
        self.window = UIWindow(frame: UIScreen.main.bounds)
        self.window?.makeKeyAndVisible()
        
        self.window?.rootViewController = ViewController()
        
        return true
    }

    
    func applicationWillResignActive(_ application: UIApplication) {}
    

    func applicationDidEnterBackground(_ application: UIApplication) {}
    

    func applicationWillEnterForeground(_ application: UIApplication) {}
    

    func applicationDidBecomeActive(_ application: UIApplication) {}

    
    func applicationWillTerminate(_ application: UIApplication) {}
}
