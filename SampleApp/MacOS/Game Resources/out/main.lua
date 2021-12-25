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

brettAtlas = nil

brettWalkRSpriteRenderer = nil
brettWalkRHeadRenderer = nil

function init()
--    backgroundTexture = L_textureLoad("background.jpg")
--    backgroundSprite = L_spriteLoad(backgroundTexture, 0, 0, 800, 600)
--    backgroundRenderer = L_spriteDrawStaticCreate(backgroundSprite)
    
    myFont = L_loadFont("EnterCommand.ttf")
    
    backgroundAtlas = L_spriteAtlasLoad("background.json", "background.png")
    
    backgroundSkySprite = L_spriteAtlasGetSprite(backgroundAtlas, "sky.png")    
	backgroundSkyRenderer = L_spriteDrawStaticCreate(backgroundSkySprite, 2)
	
	backgroundSprite = L_spriteAtlasGetSprite(backgroundAtlas, "background.png")
	backgroundRenderer = L_spriteDrawStaticCreate(backgroundSprite, 1)
    
    brettAtlas = L_spriteAtlasLoad("brett.json", "brett.png")
    brettWalkRSpriteRenderer = L_spriteDrawAnimatedCreate(100, 3,
 	  	L_spriteAtlasGetSprite(brettAtlas, "rwalk_body1"),
		L_spriteAtlasGetSprite(brettAtlas, "rwalk_body2"),
		L_spriteAtlasGetSprite(brettAtlas, "rwalk_body3"),
		L_spriteAtlasGetSprite(brettAtlas, "rwalk_body4"),
		L_spriteAtlasGetSprite(brettAtlas, "rwalk_body5"),
		L_spriteAtlasGetSprite(brettAtlas, "rwalk_body6"),
		L_spriteAtlasGetSprite(brettAtlas, "rwalk_body7"),
		L_spriteAtlasGetSprite(brettAtlas, "rwalk_body8")
	)
	
    brettWalkRHeadRenderer = L_spriteDrawAnimatedCreate(100, 3,
 	  	L_spriteAtlasGetSprite(brettAtlas, "rstand_head1")
	)
end

function update ()
    
    coroutine.resume(co)

	L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
	L_spriteDrawRender(backgroundRenderer, 0, 0)
	--L_spriteDrawRender(brettWalkRSpriteRenderer, 40, 150)
	--L_spriteDrawRender(brettWalkRHeadRenderer, 42, 45)

	drawText(myFont, "Lua in a C++ Engine! " .. a, 10, 10, 100, 100, 100, "left")
end
