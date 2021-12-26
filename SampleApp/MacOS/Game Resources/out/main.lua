print("Total init")

myFont = nil

backgroundAtlas = nil
backgroundSprite = nil
backgroundSkySprite = nil
backgroundSkyRenderer = nil

brettAtlas = nil

function init()
    myFont = L_loadFont("EnterCommand.ttf")
    
    backgroundAtlas = L_spriteAtlasLoad("background.json", "background.png")    
    backgroundSkySprite = L_spriteAtlasGetSprite(backgroundAtlas, "sky.png")    
	backgroundSkyRenderer = L_spriteDrawStaticCreate(backgroundSkySprite, 2)
	
	backgroundSprite = L_spriteAtlasGetSprite(backgroundAtlas, "background.png")
	backgroundRenderer = L_spriteDrawStaticCreate(backgroundSprite, 2)
end

function update ()
	L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
	L_spriteDrawRender(backgroundRenderer, 0, 0)
end
