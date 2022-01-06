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
--	textFadeInAnim = ValueAnimatorFactory:CreateLinear(0, 255, 1, 1,
--		function(v)
--			text:SetAlpha(v)
--		end,
--		function(anim)
--			anim:ReleaseMem()
--			textFadeOutAnim:Start()
--		end
--	)
--	textFadeInAnim:Start()
--	
--	textFadeOutAnim = ValueAnimatorFactory:CreateLinear(255, 0, 1, 1,
--		function(v)
--			text:SetAlpha(v)
--		end,
--		function(anim)
--			anim:ReleaseMem()
--			
--			fadeInAnimation:Start()
--			truckAnim:Start()
--		end
--	)
--	
--	fadeInAnimation = ValueAnimatorFactory:CreateLinear(0, 255, 0.5, 1.5,
--		function(val)
--			sky:SetAlpha(val)
--		end,
--		function(anim)
--			anim:ReleaseMem()
--			initialAnimationDone = true
--		end
--	)
--
--	truckAnim = ValueAnimatorFactory:CreateLinear(0, 255, 1, 0.5,
--		function(val)
--			truck:SetAlpha(val)
--		end,
--		function(anim)
--			anim:ReleaseMem()
--			
--			character:SetHidden(false)
--		end
--	)

--	skyFadeIn = PropertyAnimatorFactory:FadeIn(sky, 1, 2, function()
--		skyFadeOut:Start()
--	end)
--	
--	skyFadeOut = PropertyAnimatorFactory:FadeOut(sky, 1, 2, function()
--		truckFadeIn:Start()	
--	end)
--	
--	truckFadeIn = PropertyAnimatorFactory:FadeIn(truck, 0, 0.5, function(sender)
--		character:SetHidden(false)
--		initialAnimationDone = true
--	end)
--	
--	
--	skyFadeIn:Start()
	
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

	local group = AnimationGroupFactory:GroupAnimations(
		'sequence'
	,	PropertyAnimatorFactory:FadeIn(text, 0, 3)
	,	PropertyAnimatorFactory:FadeOut(text, 0, 1)
	, 	PropertyAnimatorFactory:FadeIn(truck, 5, 3)
	, 	PropertyAnimatorFactory:FadeIn(sky, 0.5, 5)
	, 	function()
			print("did finish")
			character:SetHidden(false)
		end
	)
	group:Start()
end

function init()
	loadSprites()
end

function mouseDown(x, y)
	MemoryReleasePool:Drain()

--	if initialAnimationDone ~= true then
--		return
--	end
--	print ("mouse down " .. x .. ", " .. y)
--	character:WalkTo(x, y)
end

function update ()
	--L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
end
