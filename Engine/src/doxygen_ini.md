# Ini file

By default the engine reads a file called *main.ini*. It holds certain default parameters,
some of which can be modified at a later date.

# Sections

## RESOLUTION

| Parameter Name    | Values    | Default       |  Description      |
|-------------------|-----------|---------------|-------------------|
|width              |integer    |none           |desired width of the viewport |
|height             |integer    |none           |desired height of the viewport |

## PHONE

| Parameter Name    | Values    | Default       |  Description      |
|-------------------|-----------|---------------|-------------------|
|orientation        | combination |none           | portrait, landscape or combination of both with delimiter of \| |

## RENDERER

| Parameter Name    | Values    | Default       | Description      |
|-------------------|-----------|---------------|------------------|
|game_folder        |string     |@rpath | The folder at which the engine will try to load the data. Provide a full path or use _@rpath_ variable to locate the data. _@path_ points to the .app/Contents/Resources bundle on MacOS and to the folder containing .exe file on Windows.|
|clear_color        |r,g,b,a i.e. 0.0,0.0,0.0,1.0     | magenta  | the background color of the renderer before any modifications applied  |

## INPUT
| Parameter Name    | Values    | Default       |  Description      |
|-------------------|-----------|---------------|-------------------|
|gamepad_support    | bool      |false          | turns on gamepad supoprt |
|gamepad_virtual_support    | bool      |false          | turns on virtual gamepad supoprt, MacOS/iOS/TVOS only for now |
|gamepad_virtual_buttons    | string, combination      |none          | various buttons for the gamepad |

Possible gamepad_virtual_buttons 
- DirectionPad
- LeftThumbstick
- RightThumbstick
- ButtonA
- ButtonB
- ButtonX
- ButtonY
- LeftShoulder
- RightShoulder
- LeftTrigger
- RightTrigger
- LeftThumbstickButton
- RightThumbstickButton
