//
//  EngineIDEApp.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

@main
struct EngineIDEApp: App {
    var body: some Scene {
        DocumentGroup(newDocument: EngineIDEDocument()) { file in
            ContentView(document: file.$document)
        }
    }
}
