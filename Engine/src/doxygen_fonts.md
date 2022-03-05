#  Fonts Reference

## Font types used
The Engine uses bitmap fonts. Those are comprised of the .fnt file (ascii) and the texture that
includes all the glyphs for that particular font.

Bitmap fonts are simply a collection of glyphs that are treated like sprites by the engine.
The drawing functions simply layout glyphs at given coordinates.

The engine does not use TTF or OTF fonts. Creating
your own bitmap fonts from existing TTF or OTF fonts can be achieved by using a wide variety
of tools.\see https://github.com/vladimirgamalyan/fontbm

## Loading

To load the font simply call up a global manager called *FontManager* and load the font by
providing .fnt and the texture file.

```
local font = FontManager:LoadFont("MyFont.fnt", "MyFont.png)
```

One loaded the font stays until the scene manager clears the font cache.

## Sprite representation

Once the font has been loaded a sprite representation can be created. A sprite representation
is being created on a given scene and its lifecycle is linked to that scene.

```
local textSprite = scene:SpriteTextLoad(font)
```

Font sprite representations share a number of functions with general sprite representations.

```
textSprite:SetText("Test")
textSprite:SetPosition(300, 300)
textSprite:SetAcceptsLight(true)
textSprite:SetScale(2)
textSprite:SetColorMod(1.0, 1.0, 0.0, 1.0)
textSprite:SetShadowColor(1.0, 0.0, 0.0, 1.0)
textSprite:SetShadowOffset(2, 2)
```

\see SpriteRepresentationText
