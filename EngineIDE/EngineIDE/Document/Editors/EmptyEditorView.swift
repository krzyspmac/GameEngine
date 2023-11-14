//
//  EmptyEditorView.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

struct EmptyEditorView: View, EditorProtocol {

    @EnvironmentObject var navigationManager: NavigationManager

    private(set) var outlineItem: OutlineItem

    var body: some View {
        Group {
            Text("Empty editor")
        }.onAppear(perform: {
            DispatchQueue.main.async {
                navigationManager.selectedOutlineItem = outlineItem
            }
        })
    }
}
