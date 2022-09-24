extern crate bindgen;

use std::env;
use std::path::PathBuf;

fn main() {
    // Tell cargo to not worry about some of the missing symbols
    println!("cargo:rustc-link-arg=-Wl,-undefined,dynamic_lookup");

    // Tell cargo to look for shared libraries in the specified directory
    // println!("cargo:rustc-link-search=/Users/Shared/Shared Documents/NoBackup/xcode_temporary/Build/Products/Debug");

    let bindings = bindgen::Builder::default()
        .header("/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/RustWrapper/globals.hpp")

        .clang_arg("-std=c++20")
        .clang_arg("-DSCRIPTING_WRAPPER_BUILD")

        // system includes
        .clang_arg("-I/Applications/Xcode_13.4.1.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/sys")

        .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src")
        .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Common")
        .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/RustWrapper")

        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Animations")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Character Movement")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Console")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Drawables")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Engine")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Engine Provider")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/File Access")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Fonts")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Gamepad")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Interfaces")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Lights")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Loaders")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Managers")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Memory")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Scene")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Screen")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Scripting")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Sound")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Sprites")
        .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/States")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Static Objects")
        // .clang_arg("-I/Users/krzysp/Documents/Projekty/Programistyczne/GameEngine/Engine/src/Renderer/Textures")

        // .opaque_type("engine::TimeBase")
        // .opaque_type("TimeBase")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}