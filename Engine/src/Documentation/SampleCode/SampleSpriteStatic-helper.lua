function init()
	local atlas = AtlasManager:spriteAtlasLoad( "background.json", "background.png" )
	local scene = SceneManager:sceneCreateNew()

	local backgroudnSpr = scene:LoadSpriteStatic(atlas, "sky.png")
	backgroudnSpr:SetScale(3)
	
	local tructSpr = scene:LoadSpriteStatic(atlas, "background.png")
	tructSpr:SetScale(2)
end
