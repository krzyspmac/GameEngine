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
    @ObservedObject var navigationStore: NavigationStore

    @EnvironmentObject var navigationManager: NavigationManager

    var body: some View {
        VStack {
            List {
                OutlineGroup(items: navigationStore.data, theme: $theme)
            }

            Spacer()

            HStack {
                Text("\(navigationManager.selectedOutlineItem?.title ?? "n/a")")

                Spacer()
            }
        }
    }
}

private struct OutlineGroup: View {

    var items: [OutlineItem]
    @Binding var theme: Theme

    var body: some View {
        VStack(spacing: 0) {
            ForEach(items) { item in
                OutlineItemView(item: item, theme: $theme)

                if let children = item.children {
                    OutlineGroup(items: children, theme: $theme)
                }
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
            Button(
                action: {
                    navigationManager.selectedOutlineItem = item
                },
                label: {
                    HStack {
                        item.image
                            .resizable()
                            .scaledToFit()
                            .frame(width: Sizes.large, height: Sizes.large)
                            .symbolRenderingMode(.hierarchical)
                            .foregroundColor(
                                navigationManager.selectedOutlineItem == item
                                ? theme.iconForegroundSelected
                                : theme.iconForegroundDeselected
                            )

                        Text(item.title)

                        Spacer()
                    }
                    .padding(.leading, CGFloat(item.indentation) * Sizes.large)
                    .frame(maxWidth: .infinity)
                    .contentShape(Rectangle())
                }
            )
            .buttonStyle(
                OutlineButtonStyle(
                    isSelected: navigationManager.selectedOutlineItem == item,
                    theme: theme
                )
            )
        }
    }
}

struct OutlineButtonStyle: ButtonStyle {
    var isSelected: Bool
    var theme: Theme

    func makeBody(configuration: Configuration) -> some View {
        configuration.label
            .padding(Sizes.mini)
            .padding(.leading, Sizes.normal)
            .background( isSelected ? theme.outlineItemSelected : .clear )
            .foregroundStyle(.foreground)
            .clipShape(
                RoundedRectangle(cornerRadius: 7.0)
            )
    }
}
