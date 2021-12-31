function setup()
	local scene = SceneManager:sceneCreateNew()
	
	local sceneAtlas = AtlasManager:spriteAtlasLoad( "background.json", "background.png" )

	background = SpriteRendererManager:spriteDrawLoadStatic(
		sceneAtlas:getItemForName("sky.png")
	  , 3
	)
	scene:addSpriteDrawStatic(background)
end

function init()
	helperLoading()
end
