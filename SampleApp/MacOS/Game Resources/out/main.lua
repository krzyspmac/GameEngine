print("Total init")
a = 1

co = coroutine.create(function ()
	while true do
	--end
	--for i=1,10 do
    	a = a + 1
    	if a > 60 then a = 0 end

		coroutine.yield()
    end
end)


--backgroundTexture = nil
--backgroundSprite = nil
--backgroundRenderer = nil

myFont = nil

walkTexture = nil
walkSprite = nil
walkRenderer = nil

backgroundAtlas = nil
backgroundSprite = nil
backgroundSkySprite = nil
backgroundSkyRenderer = nil

atlas = nil
atlasSprite = nil
atlasSpriteRenderer = nil

function init()
--    backgroundTexture = L_textureLoad("background.jpg")
--    backgroundSprite = L_spriteLoad(backgroundTexture, 0, 0, 800, 600)
--    backgroundRenderer = L_spriteDrawStaticCreate(backgroundSprite)
    
    myFont = L_loadFont("EnterCommand.ttf")
    
    backgroundAtlas = L_spriteAtlasLoad("background.json", "background.png")
    
    backgroundSkySprite = L_spriteAtlasGetSprite(backgroundAtlas, "sky.png")    
	backgroundSkyRenderer = L_spriteDrawStaticCreate(backgroundSkySprite)
	
	backgroundSprite = L_spriteAtlasGetSprite(backgroundAtlas, "background.png")
	backgroundRenderer = L_spriteDrawStaticCreate(backgroundSprite)
    
   atlas = L_spriteAtlasLoad("brett.json", "brett.png")
   atlasSprite = L_spriteAtlasGetSprite(atlas, "rwalk_body1")
   atlasSpriteRenderer = L_spriteDrawAnimatedCreate(atlasSprite, 100)
end

function update ()
    
    coroutine.resume(co)

	L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
	L_spriteDrawRender(backgroundRenderer, 0, 0)
--	L_spriteDrawRender(atlasSpriteRenderer, 40, 50)

--	drawText(myFont, "Lua in a C++ Engine! " .. a, 10, 10, 100, 100, 100, "left")
end
