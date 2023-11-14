//
//  EmptyEditor.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

struct EmptyEditor: View, EditorProtocol {

    @EnvironmentObject var navigationManager: NavigationManager

    private(set) var outlineItem: OutlineItem
    @State private(set) var onAppearEditor: ((OutlineItem) -> Void)?

    var body: some View {
        Group {
            Text("Empty editor")
        }.onAppear(perform: {
            navigationManager.selectedOutlineItem = outlineItem
            print("On appear from view: \(outlineItem.title)")
        })
    }

    @ViewBuilder
    func onAppearEditor(_ completion: @escaping ((OutlineItem) -> Void)) -> Self {
        self.onAppearEditor = completion
        return self
    }
}
