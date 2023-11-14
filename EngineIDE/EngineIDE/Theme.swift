//
//  Theme.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI
import Combine

struct Theme {

    var iconForegroundDeselected: Color
    var iconForegroundSelected: Color

    var outlineItemSelected: Color

    init(
        iconForegroundDeselected: Color,
        iconForegroundSelected: Color,
        outlineItemSelected: Color
    ) {
        self.iconForegroundDeselected = iconForegroundDeselected
        self.iconForegroundSelected = iconForegroundSelected
        self.outlineItemSelected = outlineItemSelected
    }
}

final class ThemeManager: ObservableObject {

    static var shared: ThemeManager = .init()

    @Published var current: Theme

    public init() {
        current = Theme(
            iconForegroundDeselected: .blue,
            iconForegroundSelected: .white,
            outlineItemSelected: .gray.opacity(0.5)
        )
    }
}
