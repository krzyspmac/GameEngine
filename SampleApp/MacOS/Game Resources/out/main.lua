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
	
	local scene = SceneManager:SceneCreateNew()

	local sceneAtlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )

	background = SpriteRendererManager:SpriteDrawLoadStatic(
		sceneAtlas:GetItemForName("sky.png")
	)
	background:SetScale(2)
	scene:AddSpriteDrawStatic(background)

	rv = SpriteRendererManager:SpriteDrawLoadStatic(
		sceneAtlas:GetItemForName("background.png")
	)
	rv:SetScale(2)
	scene:AddSpriteDrawStatic(rv)
end

function helperLoading()
	local atlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )
	local scene = SceneManager:SceneCreateNew()

	local backgroudnSpr = scene:LoadSpriteStatic(atlas, "sky.png")
	backgroudnSpr:SetScale(3)
	
	local tructSpr = scene:LoadSpriteStatic(atlas, "background.png")
	tructSpr:SetScale(2)
end

function init()
--	customLoading()
	helperLoading()
end

function update ()
	--L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
end
