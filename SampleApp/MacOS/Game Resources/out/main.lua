initialAnimationDone = false

function loadSprites()
	local atlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )
	local scene = SceneManager:SceneCreateNew()
	
	-- character
	character = scene:LoadCharacter("brett_character.json")
	character:SetScale(3)
	character:PlaceAt(100,450)
	character:SetInverseWalkbox("polygons.json")
	character:SetWalkingSpeed(400)
	--scene:SetMainCharacter(character)
	scene:SetMouseDownFunction(mouseDown)

	-- sky
	sky = scene:LoadSpriteStatic(atlas, "sky.png")
	sky:SetScale(3)
	sky:SetAlpha(0)

	-- truck
	truck = scene:LoadSpriteStatic(atlas, "background.png")
	truck:SetScale(2)
	truck:SetAlpha(0)
	
	fadeInAnimation = AnimationFactory:CreateLinear(0, 255, 0.5, 1.5,
		function(val)
			sky:SetAlpha(val)
		end,
		function()
			fadeInAnimation:ReleaseMem()
			initialAnimationDone = true
		end
	)
	fadeInAnimation:Start()
	
	truckAnim = AnimationFactory:CreateLinear(0, 255, 1, 0.5,
		function(val)
			truck:SetAlpha(val)
		end,
		function()
			truckAnim:ReleaseMem()
		end
	)
	truckAnim:Start()
end

function init()
	loadSprites()
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
