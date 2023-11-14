//
//  DocumentContentView.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

struct DocumentContentView: View {

    @Binding var document: EngineIDEDocument
    @Binding var theme: Theme
    @ObservedObject var navigationStore: NavigationStore = .init()

    @EnvironmentObject var navigationManager: NavigationManager

    var body: some View {
        NavigationSplitView(
            sidebar: {
                VStack {
                    NavigationOutlineView(
                        document: $document,
                        theme: $theme,
                        navigationStore: navigationStore
                    )
                    .environmentObject(navigationManager)
                }
                .frame(minWidth: 200)
            },
            detail: {
                TextEditor(text: $document.text)
            }
        )
        .searchable(text: $navigationStore.searchPhrase, placement: .sidebar)
        .accentColor(theme.iconForegroundDeselected)
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
