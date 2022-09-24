include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

mod scene_manager;
use crate::scene_manager::SceneManager;

static mut mainSceneManager:SceneManager = SceneManager { };

// let sceneManager = SceneManager { };

// let a

#[no_mangle]
pub extern "C" fn pictel_game_script_init() {
    println!("PictelInit");

    unsafe {
        mainSceneManager.initialize();
    }
    // let sceneManager = SceneManager { };
}

#[no_mangle]
pub extern "C" fn pictel_game_script_frame_update() {
    unsafe {
        let timeGlobal = engine_Globals::time();
        println!("Time from last frame in seconds {}", engine_Time_GetFrameDeltaSec(timeGlobal));
        // println!("Time from last frame in seconds {}", timeGlobal.GetEngineStart());
    }
}
