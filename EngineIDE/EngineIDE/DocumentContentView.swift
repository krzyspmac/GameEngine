//
//  DocumentContentView.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

private struct OutlineItem: Identifiable {
    var id = UUID()
    var title: String
    var image: Image
    var indentation: Int
    var children: [OutlineItem]?
}

private let data: [OutlineItem] = [
    .init(title: "Project", image: .init(systemName: "doc"), indentation: 0, children: [
        .init(title: "Scenes", image: .init(systemName: "folder.fill"), indentation: 1, children: [
        ]),
        .init(title: "Textures", image: .init(systemName: "photo"), indentation: 1, children: [
        ]),
    ])
]

struct DocumentContentView: View {

    @Binding var document: EngineIDEDocument
    @Binding var theme: Theme

    var body: some View {

        NavigationSplitView(
            sidebar: {
                NavigationOutlineView(
                    document: $document,
                    theme: $theme
                )
            },
            detail: {
                TextEditor(text: $document.text)
            }
        )
    }
}

private struct NavigationOutlineView: View {

    @Binding var document: EngineIDEDocument
    @Binding var theme: Theme

    var body: some View {
        VStack {
            OutlineGroup(data, children: \.children, content: { child in
                OutlineItemView(item: child, theme: $theme)
            })
            .padding([.leading, .trailing], Sizes.large)

            Spacer()
        }
    }
}

private struct OutlineItemView: View {

    var item: OutlineItem
    @Binding var theme: Theme

    var body: some View {
        HStack {
            item.image
                .resizable()
                .scaledToFit()
                .frame(width: 14, height: 14)
                .symbolRenderingMode(.hierarchical)
                .foregroundColor(theme.iconForegroundColor)

            Text(item.title)
        }
        .padding(.leading, CGFloat(item.indentation) * Sizes.large)
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
    }
}
