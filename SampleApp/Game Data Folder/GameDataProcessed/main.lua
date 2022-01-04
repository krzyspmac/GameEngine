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
	character:SetHidden(true)
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
	
	-- texts
	local textsAtlas = AtlasManager:SpriteAtlasLoad("textx.json", "textx.png")
	text = scene:LoadSpriteStatic(textsAtlas, "demo_text.png")
	local textScale = 3
	text:SetScale(textScale)
	local vpW, vpH = EngineState:GetViewportSize()
	local tW, tH = text:GetSize()
	text:SetPosition(((vpW - tW*textScale)/2), ((vpH - tH*textScale)/2))
	text:SetAlpha(0)
	
	-- animations	
	animateIntro()
end

function animateIntro()
	textFadeInAnim = AnimationFactory:CreateLinear(0, 255, 1, 1,
		function(v)
			text:SetAlpha(v)
		end,
		function(anim)
			anim:ReleaseMem()
			textFadeOutAnim:Start()
		end
	)
	textFadeInAnim:Start()
	
	textFadeOutAnim = AnimationFactory:CreateLinear(255, 0, 1, 1,
		function(v)
			text:SetAlpha(v)
		end,
		function(anim)
			anim:ReleaseMem()
			
			fadeInAnimation:Start()
			truckAnim:Start()
		end
	)
	
	fadeInAnimation = AnimationFactory:CreateLinear(0, 255, 0.5, 1.5,
		function(val)
			sky:SetAlpha(val)
		end,
		function(anim)
			anim:ReleaseMem()
			initialAnimationDone = true
		end
	)

	truckAnim = AnimationFactory:CreateLinear(0, 255, 1, 0.5,
		function(val)
			truck:SetAlpha(val)
		end,
		function(anim)
			anim:ReleaseMem()
			
			character:SetHidden(false)
		end
	)
	
--	local introAnim = AnimationSquence:DoAnimations('simultaneus', function()
--			talkAnim:Start()
--		end,
--	, 	textFadeInAnim
--	, 	rockfalling
--	)
--
--	local talkAnim = AnimationSquence:DoAnimations('sequence', function()
--			finish()
--		end,
--	, 	chuckTalk1,
--	, 	chuckTalk2
--	)
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
