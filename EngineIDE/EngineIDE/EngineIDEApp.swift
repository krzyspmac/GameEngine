//
//  EngineIDEApp.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

@main
struct EngineIDEApp: App {

    @ObservedObject private var themeManager = ThemeManager.shared

    var body: some Scene {
        DocumentGroup(newDocument: EngineIDEDocument()) { file in
            DocumentContentView(
                document: file.$document,
                theme: $themeManager.current
            )
            .environmentObject(NavigationManager.shared)
        }
    }
}
