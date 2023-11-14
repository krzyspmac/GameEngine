//
//  Theme.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI
import Combine

final class Theme: ObservableObject {

    var iconForegroundColor: Color

    init(iconForegroundColor: Color) {
        self.iconForegroundColor = iconForegroundColor
    }
}

final class ThemeManager: ObservableObject {

    static var shared: ThemeManager = .init()

    @Published var current: Theme

    public init() {
        current = Theme(
            iconForegroundColor: .blue
        )
    }
}
