//
//  NavigationManager.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import Combine

/// Just for keeping the currently opened outline element
final class NavigationManager: ObservableObject {

    static let shared: NavigationManager = .init()

    @Published var selectedOutlineItem: OutlineItem?
}
