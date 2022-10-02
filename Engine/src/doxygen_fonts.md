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
engine::FontI* font = Globals::fontManager()->LoadFont("MyFont.fnt", "MyFont.png");
```

One loaded the font stays until the font is removed from the FontManager.
Loading the same font twice will just return the previously created instance.

## Sprite representation

Once the font has been loaded a sprite representation can be created. A sprite representation
is being created on a given scene and its lifecycle is linked to that scene.

```
engine::SceneI *scene = Globals::sceneManager()->SceneCreateNew();

engine::SpriteRepresentationTextI* textSprite = scene:SpriteTextLoad(font)
```

Font sprite representations share a number of functions with general sprite representations so the position, color and scale can be set.

```
textSprite->SetText("Test");
textSprite->SetPosition({100.0, 200.0});
textSprite->SetColorMod({1.f, 1.f, 1.f, 1.f});
textSprite->SetHorizontalAlignment("center");
textSprite->SetVerticalAlignment("middle");
textSprite->SetScale(2.0f);
textSprite->SetAlpha(0.0f);
textSprite->SetAcceptsLight(true);
```

Font sprite representation also defines a couple of font-specific functionality.

```
textSprite->SetText("Test");
textSprite->SetHorizontalAlignment("center");
textSprite->SetVerticalAlignment("middle");
```

\see engine::SpriteRepresentationTextI
