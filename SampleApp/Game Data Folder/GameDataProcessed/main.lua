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
	local scene = SceneManager:SceneCreateNew()
--	
	local roomAtlas = AtlasManager:SpriteAtlasLoad( "parlor.json", "parlor.png" )
--
--	-- character
--	character = scene:LoadCharacter("brett_character.json")
--	character:SetScale(3)
--	character:PlaceAt(100,450)
--	character:SetInverseWalkbox("polygons.json")
--	character:SetWalkingSpeed(400)
--	character:SetHidden(true)
--	--scene:SetMainCharacter(character)
--	scene:SetMouseDownFunction(mouseDown)
--
	-- sky
	sky = scene:LoadSpriteStatic(roomAtlas, "roombg")
	sky:SetScale(4)
	sky:SetAlpha(255)
	sky:SetPosition(0, 0)
	
--	-- sky
sky2 = scene:LoadSpriteStatic(atlas, "sky.png")
sky2:SetScale(2)
sky2:SetAlpha(255)
sky2:SetPosition(0, 0)

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
		PropertyAnimatorFactory:FadeIn(sky, 1, 3)
	, 	function() -- on finish
			character:SetHidden(false)
		end
	)
	group:Start()
end

------------------------------------------------------------------------------------------
-- event handling functions

function mouseDown(x, y)
--	MemoryReleasePool:Drain()

--	if initialAnimationDone ~= true then
--		return
--	end
--	print ("mouse down " .. x .. ", " .. y)
--	character:WalkTo(x, y)
end

------------------------------------------------------------------------------------------
-- script entry point functions

function init()
	loadSprites()
--	animateIntro()
end

function update ()
	--L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
--	font:DrawAt("This is a sample!", 200, 200, 255, 0, 0, 255, "left")
end

--function io.write (...)
--	print ("mine")

--end
