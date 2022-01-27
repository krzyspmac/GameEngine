initialAnimationDone = false

------------------------------------------------------------------------------------------
-- globals for the script

character = nil
sky = nil
scene = nil
truck = nil
bg = nil
font = nil

viewportWidth = nil, viewportHeight

------------------------------------------------------------------------------------------
-- loading functions

function loadSprites()
	viewportWidth, viewportHeight = EngineState:GetViewportSize()
	
	local atlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )
	local scene = SceneManager:SceneCreateNew()
	local roomAtlas = AtlasManager:SpriteAtlasLoad( "parlor.json", "parlor.png" )

	-- character
	character = scene:LoadCharacter("brett_character.json")
	character:SetScale(1)
	character:PlaceAt(0,0)
	--character:SetInverseWalkbox("polygons.json")
	character:SetWalkingSpeed(600)
	character:SetHidden(false)
	scene:SetMouseDownFunction(mouseDown)

	-- sky
	sky2 = scene:LoadSpriteStatic(atlas, "background.png")
	sky2:SetScale(1)
	sky2:SetAlpha(1)
	sky2:SetPosition(0, 0)

	sky = scene:LoadSpriteStatic(roomAtlas, "roombg")
	sky:SetScale(1)
	sky:SetAlpha(0)
	sky:SetPosition(1280/2, 200)
end

function registerResolutionChange()
	EngineState:SetOnScreenSizeChange(function(width, height, density)
		print("Size received: width = " .. width .. ", height = " .. height .. " at density = " .. density)
		
		viewportWidth, viewportHeight = EngineState:GetViewportSize()
 		print("Current viewport is " .. viewportWidth .. " x " .. viewportHeight)
	end)
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

--	if initialAnimationDone ~= true then return end
	print ("mouse down " .. x .. ", " .. y)
	character:WalkTo(x, y)
end

------------------------------------------------------------------------------------------
-- script entry point functions

function init()
	registerResolutionChange()
	loadSprites()
  	--animateIntro()
end

function update ()
end
