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
            OutlineGroup(data, children: \.children, content: { child in
                OutlineItemView(
                    item: child,
                    theme: $theme
                )
                .environmentObject(navigationManager)
            })
            .padding([.leading, .trailing], Sizes.large)

            Spacer()
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
                        item.image
                            .resizable()
                            .scaledToFit()
                            .frame(width: 14, height: 14)
                            .symbolRenderingMode(.hierarchical)
                            .foregroundColor(theme.iconForegroundColor)

                        Text(item.title)
                    }
                )
                .buttonStyle(selected: item == navigationManager.selectedOutlineItem)
                .onTapGesture {
                    print("On tap \(item.title)")
                }
            }
        }
        .padding(.leading, CGFloat(item.indentation) * Sizes.large)
    }
}

private extension NavigationLink {

    @ViewBuilder
    func buttonStyle(selected: Bool) -> some View {
        if selected {
            self.buttonStyle(BorderedButtonStyle())
        } else {
            self.buttonStyle(BorderlessButtonStyle())
        }
    }
}
