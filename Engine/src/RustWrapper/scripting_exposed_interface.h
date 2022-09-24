//
//  scripting_exposed_interface.h
//  Default functions that must be exposed in the game scripts
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

#ifndef rust_exposed_h
#define rust_exposed_h

/**
    The default function type that starts the engine. By default two of those must
    be defined:


    #[no_mangle]
    pub extern "C" fn pictel_game_script_init() {
     println!("PictelInit");
    }

    #[no_mangle]
    pub extern "C" fn pictel_game_script_frame_update() {
     println!("PictelFrameUpdate");
    }
 */
typedef void (*ScriptingFunctionVoid) (void);

#endif /* rust_exposed_h */
