initialAnimationDone = false

------------------------------------------------------------------------------------------
-- globals for the script

character = nil
sky = nil
scene = nil
truck = nil
bg = nil
font = nil

------------------------------------------------------------------------------------------
-- loading functions

function loadSprites()
	local atlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )
--atlas:SetFlippedVertically(1)
	
	local scene = SceneManager:SceneCreateNew()
--	
	local roomAtlas = AtlasManager:SpriteAtlasLoad( "parlor.json", "parlor.tga" )

	-- character
--	character = scene:LoadCharacter("brett_character.json")
--	character:SetScale(3)
--	character:PlaceAt(100,450)
--	character:SetInverseWalkbox("polygons.json")
--	character:SetWalkingSpeed(400)
--	character:SetHidden(false)
--	scene:SetMainCharacter(character)
--	scene:SetMouseDownFunction(mouseDown)

	-- sky
	
--	initialAnimationDone = true
	
--	-- sky
sky2 = scene:LoadSpriteStatic(atlas, "background.png")
sky2:SetScale(0.5)
sky2:SetAlpha(1)
sky2:SetPosition(1280/2, 720/2)

sky = scene:LoadSpriteStatic(roomAtlas, "roombg")
sky:SetScale(1)
sky:SetAlpha(0)
sky:SetPosition(1280/2, 200)


--another = scene:LoadSpriteStatic(roomAtlas, "cupboard-r")
--another = scene:LoadSpriteStatic(roomAtlas, "cupboard-l")

--sky3 = scene:LoadSpriteStatic(atlas, "background.png")
--sky3:SetScale(1)
--sky3:SetAlpha(255)
--sky2:SetPosition(1280/4, 400/4)



--	
--	-- room
--	bg = scene:LoadSpriteStatic(roomAtlas, "roombg")
--	bg:SetScale(4)
--	
--	cupboardL = scene:LoadSpriteStatic(roomAtlas, "cupboard-l")
--	cupboardL:SetScale(4)
--	
--	cupboardR = scene:LoadSpriteStatic(roomAtlas, "cupboard-r")
--	cupboardR:SetScale(4)
--	cupboardR:SetPosition(235*4, 0)
--	
----	cupboardL = scene:LoadSpriteStatic(roomAtlas, "cupboard-l")
--	
--	font = FontManager:LoadFont("DialogFont_retro.fnt", "DialogFont_retro.png")
end

function animateIntro()
	local group = AnimationGroupFactory:GroupAnimations(
		'sequence',
		PropertyAnimatorFactory:FadeIn(sky, 1, 5)
	,	PropertyAnimatorFactory:FadeOut(sky, 1, 3)
	, 	function() -- on finish
			--character:SetHidden(false)
			initialAnimationDone = true
		end
	)
	group:Start()
end

------------------------------------------------------------------------------------------
-- event handling functions

function mouseDown(x, y)
--	MemoryReleasePool:Drain()

	if initialAnimationDone ~= true then return end
	print ("mouse down " .. x .. ", " .. y)
	character:WalkTo(x, y)
end

------------------------------------------------------------------------------------------
-- script entry point functions

function init()
	loadSprites()
  	animateIntro()
end

function update ()
	--L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
--	font:DrawAt("This is a sample!", 200, 200, 255, 0, 0, 255, "left")
end

--function io.write (...)
--	print ("mine")

--end
