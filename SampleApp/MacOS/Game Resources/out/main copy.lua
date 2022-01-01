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
	
	character = scene:LoadCharacter("brett_character.json")
	character:SetScale(3)
	character:PlaceAt(100, 450)
	local x, y = character:GetPosition()
	print(x)
	print(y)
	character:SetInverseWalkbox("polygons.json")
--	character:WalkTo(716, 373)
	scene:SetMainCharacter(character)
	character:SetWalkingSpeed(400)
end

initialAnimationDone = false

function helperLoading()
	local atlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )
	local scene = SceneManager:SceneCreateNew()

	backgroudnSpr = scene:LoadSpriteStatic(atlas, "sky.png")
	backgroudnSpr:SetScale(3)
	
	local tructSpr = scene:LoadSpriteStatic(atlas, "background.png")
	tructSpr:SetScale(2)
	
	character = scene:LoadCharacter("brett_character.json")
	character:SetScale(3)
	character:PlaceAt(100,450)
	character:SetInverseWalkbox("polygons.json")
	character:SetWalkingSpeed(400)
	
	--scene:SetMainCharacter(character)
	scene:SetMouseDownFunction("mouseDown")
	
	tructSpr:SetAlpha(0)
	backgroudnSpr:SetAlpha(0)
	
	fadeInAnimation = AnimationFactory:CreateLinear(0, 255, 0.5, 1.5,
		function(val)
			backgroudnSpr:SetAlpha(val)
		end,
		function()
			fadeInAnimation:ReleaseMem()
			initialAnimationDone = true
		end
	)
	fadeInAnimation:Start()
	
	truckAnim = AnimationFactory:CreateLinear(0, 255, 1, 0.5,
		function(val)
			tructSpr:SetAlpha(val)
		end,
		function()
			truckAnim:ReleaseMem()
		end
	)
	truckAnim:Start()
end

function init()
	--customLoading()
	helperLoading()
end

function mouseDown(x, y)
	if initialAnimationDone ~= true then
		return
	end
	print ("mouse down " .. x .. ", " .. y)
	character:WalkTo(x, y)
end

function update ()
	--L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
end
