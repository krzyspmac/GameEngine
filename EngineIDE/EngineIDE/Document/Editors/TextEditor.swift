//
//  TextEditor.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

struct TextEditorView: View, EditorProtocol {

    @EnvironmentObject var navigationManager: NavigationManager

    private(set) var outlineItem: OutlineItem

    var body: some View {
        Group {
            Text("Text Editor View")
        }.onAppear(perform: {
            DispatchQueue.main.async {
                navigationManager.selectedOutlineItem = outlineItem
            }
        })
    }
}

