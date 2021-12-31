print("Total init")

--myFont = nil
--
--backgroundAtlas = nil
--backgroundSprite = nil
--backgroundSkySprite = nil
--backgroundSkyRenderer = nil
--
--brettAtlas = nil

function customLoading()
--	backgroundAtlas = L_spriteAtlasLoad("background.json", "background.png")    
--	backgroundSkySprite = L_spriteAtlasGetSprite(backgroundAtlas, "sky.png")    
--	backgroundSkyRenderer = L_spriteDrawStaticCreate(backgroundSkySprite, 2)
	
	local scene = SceneManager:sceneCreateNew()
	
	-- Custom loading: scene atlas -> atlas item -> sprite renderer
	local sceneAtlas = AtlasManager:spriteAtlasLoad( "background.json", "background.png" )

	background = SpriteRendererManager:spriteDrawLoadStatic(
		sceneAtlas:getItemForName("sky.png")
	  , 3
	)
	scene:addSpriteDrawStatic(background)

	rv = SpriteRendererManager:spriteDrawLoadStatic(
		sceneAtlas:getItemForName("background.png")
	  , 2
	)	
	scene:addSpriteDrawStatic(rv)
end

function helperLoading()
end

function init()
	customLoading()
	--helperLoading()
end

function update ()
	L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
end
