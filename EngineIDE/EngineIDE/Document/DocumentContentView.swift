//
//  DocumentContentView.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

let data: [OutlineItem] = [
    .init(
        type: .project,
        title: "Project",
        image: .init(systemName: "doc"),
        indentation: 0,
        children: [
            .init(
                type: .scenes,
                title: "Scenes",
                image: .init(systemName: "folder.fill"),
                indentation: 1,
                children: [
                ]
            ),
            .init(
                type: .textures,
                title: "Textures",
                image: .init(systemName: "photo"),
                indentation: 1,
                children: [
                ]
            ),
        ]
    )
]

struct DocumentContentView: View {

    @Binding var document: EngineIDEDocument
    @Binding var theme: Theme

    @EnvironmentObject var navigationManager: NavigationManager

    var body: some View {
        NavigationSplitView(
            sidebar: {
                NavigationOutlineView(
                    document: $document,
                    theme: $theme
                )
                .environmentObject(navigationManager)

                Text("\(navigationManager.selectedOutlineItem?.title ?? "n/a")")

            },
            detail: {
                TextEditor(text: $document.text)
            }
        )
        .accentColor(theme.iconForegroundColor)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        let themeManager = ThemeManager()
        let theme = themeManager.current
        let binding = Binding<Theme>(
            get: { theme },
            set: { _ in }
        )
        DocumentContentView(
            document: .constant(EngineIDEDocument()),
            theme: binding
        )
        .environmentObject(NavigationManager.shared)
    }
}
