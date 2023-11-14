//
//  NavigationOutline+View.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI
import Combine

struct NavigationOutlineView: View {

    @Binding var document: EngineIDEDocument
    @Binding var theme: Theme

    @EnvironmentObject var navigationManager: NavigationManager

    var body: some View {
        VStack {
            List {
                OutlineGroup(items: data, theme: $theme)
            }

            Spacer()
        }
    }
}

private struct OutlineGroup: View {

    var items: [OutlineItem]
    @Binding var theme: Theme

    var body: some View {
        ForEach(items) { item in
            OutlineItemView(item: item, theme: $theme)

            if let children = item.children {
                OutlineGroup(items: children, theme: $theme)
            }
        }
    }
}

private struct OutlineItemView: View {

    var item: OutlineItem
    @Binding var theme: Theme

    @EnvironmentObject var navigationManager: NavigationManager

    var body: some View {
        HStack {
            Group {
                NavigationLink(
                    destination: {
                        item.contentView()
                            .environmentObject(navigationManager)
                    },
                    label: {
                        HStack {
                            item.image
                                .resizable()
                                .scaledToFit()
                                .frame(width: 14, height: 14)
                                .symbolRenderingMode(.hierarchical)
                                .foregroundColor(theme.iconForegroundColor)

                            Text(item.title)

                            Spacer()
                        }
                        .padding(.leading, CGFloat(item.indentation) * Sizes.large)
                    }
                )
            }
        }
    }
}
