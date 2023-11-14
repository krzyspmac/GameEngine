//
//  NavigationOutline.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

enum OutlineItemType: String, Identifiable, CaseIterable {

    case unknown
    case project
    case scenes
    case textures

    var id: String { self.rawValue }
}

struct OutlineItem: Identifiable, Equatable {

    var id = UUID()
    var type: OutlineItemType
    var title: String
    var image: Image
    var indentation: Int
    var children: [OutlineItem]?
    var isSelected: Bool = false
}

extension OutlineItem {
    static var empty: Self {
        .init(type: .unknown, title: "", image: Image(systemName: ""), indentation: 0)
    }
}

extension OutlineItem {

    @ViewBuilder
    func contentView() -> some View {
        switch self.type {
        case .unknown:
            EmptyEditorView(outlineItem: self)
        case .project:
            TextEditorView(outlineItem: self)
        case .scenes:
            EmptyEditorView(outlineItem: self)
        case .textures:
            EmptyEditorView(outlineItem: self)
        }
    }
}
