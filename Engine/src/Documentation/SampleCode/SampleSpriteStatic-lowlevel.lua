function init()
	local scene = SceneManager:SceneCreateNew()

	local sceneAtlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )

	background = SpriteRendererManager:SpriteDrawLoadStatic(
		sceneAtlas:GetItemForName("sky.png")
	)
	background:SetScale(2)
	scene:AddSpriteDrawStatic(background)
end
