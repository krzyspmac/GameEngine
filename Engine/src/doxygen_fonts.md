#  Fonts Reference

## Font types used
The Engine uses bitmap fonts. Those are comprised of the .fnt file (ascii) and the texture that
includes all the glyphs for that particular font.

Bitmap fonts are simply a collection of glyphs that are treated like sprites by the engine.
The drawing function converts the character in the text drawn into glyphs and those tell the engine
which sprite to put where.

The engine does not use TTF or OTF fonts due to time constraints and efficiency. Besides creating
your own bitmap font existing TTF or OTF fonts can be converted into bitmap fonts. 
There is a number of tools. \see https://github.com/vladimirgamalyan/fontbm

## Loading

To load the font simply call up a global manager called *FontManager* and load the font by
providing .fnt and the texture file.

```
local font = FontManager:LoadFont("MyFont.fnt", "MyFont.png)
```

One loaded the font stays until the scene manager clears the font cache.

## Drawing

Once the font has been loaded it can be drawn in the *Update* function of your script.
Like everything the font must be drawn in each frame.

```
font:DrawAt("Some text!", 100, 100, 255, 0, 0, 255, "left")
```
