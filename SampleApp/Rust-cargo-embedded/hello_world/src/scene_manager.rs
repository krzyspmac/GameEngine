// include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

// use std::cmp;

// pub struct SceneManager {

//     pub wantedWidth: f32,
//     pub wantedHeight: f32,
// }

// impl SceneManager {

//     pub fn initialize(&self) {
//         unsafe {
//             let engineState = engine_Globals::engineState();
//             engine_EngineState_SetOnScreenSizeChange(engineState, Some(Self::screenUpdateEx))
//         }
//     }

//     unsafe extern "C" fn screenUpdateEx(size: engine_Size, dencity: f32) {
//         println!("changed2 to {}", size.width);
//         // println!("self {}", elf);
    
//         let width: f32 = size.width as f32;
//         let height: f32 = size.height as f32;
//         let scaleX: f32 = width / 1280.0;
//         let scaleY: f32 = height / 720.0;
//         let scale = scaleX.min(scaleY);
    
//         let engineState = engine_Globals::engineState();
//         engine_EngineState_SetViewportSize(engineState, engine_Size{width: 1280, height: 720}, scale);
//     }    
// }
