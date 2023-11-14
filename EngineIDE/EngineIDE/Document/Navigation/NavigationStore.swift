//
//  NavigationStore.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI
import Combine

final class NavigationStore: ObservableObject {

    @Published var searchPhrase: String = ""
    @Published private var originalData: [OutlineItem]
    @Published var data: [OutlineItem]

    private var cancellables: Set<AnyCancellable> = .init()

    init() {
        self.originalData = [OutlineItem].defaultData
        self.data = [OutlineItem].defaultData

        $searchPhrase
            .dropFirst()
            .debounce(for: .seconds(0.5), scheduler: RunLoop.main)
            .sink { [weak self] newValue in
                guard let self = self else { return }
                self.data = filteredData(by: newValue)
            }
            .store(in: &cancellables)
    }

    private func filteredData(by searchPhrase: String?) -> [OutlineItem] {
        print("filteredData = \(self.searchPhrase)")

        guard let searchPhrase = searchPhrase,
              !searchPhrase.isEmpty
        else {
            return originalData
        }

        return [
            .init(type: .project, title: "Project", image: .init(systemName: "doc"), indentation: 0)
        ]
    }
}

private extension Array where Element == OutlineItem {

    static var defaultData: [OutlineItem] {
        return [
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
                        children: nil
                    ),
                    .init(
                        type: .textures,
                        title: "Textures",
                        image: .init(systemName: "photo"),
                        indentation: 1,
                        children: nil
                    ),
                    .init(
                        type: .textures,
                        title: "Settings",
                        image: .init(systemName: "photo"),
                        indentation: 1,
                        children: nil
                    ),
                ]
            )
        ]
    }
}
