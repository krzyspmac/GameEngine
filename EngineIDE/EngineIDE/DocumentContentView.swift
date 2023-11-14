//
//  DocumentContentView.swift
//  EngineIDE
//
//  Created by krzysp on 14/11/2023.
//

import SwiftUI

struct DocumentContentView: View {
    @Binding var document: EngineIDEDocument

    var body: some View {
        TextEditor(text: $document.text)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        DocumentContentView(document: .constant(EngineIDEDocument()))
    }
}
