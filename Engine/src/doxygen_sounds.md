#  Sound Reference

## Sound files used

Uses the OGG/Vorbis sound files exclusively. A custom implementation of
Vorbis is included in a form a [Pictel Sound Library](https://krzyspmac.github.io/Pictel/).

Note: C++ documentation missing.

## Loading

To load the file simply call up a global manager called *SoundManager* and load the file by
providing an ogg/vorbis file that's located within your game data folder.

```
local sound = SoundManager:Load("Rondo_Alla_Turka.ogg")
```

## Control

```
sound:Play()
```

```
sound:Pause()
```

```
sound:Stop()
```

```
sound:SetVolume(0.5)
```

```
sound:SetLoops(1)
```
