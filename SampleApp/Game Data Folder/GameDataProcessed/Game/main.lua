------------------------------------------------------------------------------------------
-- requires

require "game_state"
require "game_intro"

------------------------------------------------------------------------------------------
-- globals for the script

character = nil
sky = nil
scene = nil
truck = nil
bg = nil
font = nil
initialAnimationDone = false
light1 = nil
tds = nil
playerSprite = nil
sound = nil
sky5 = nil

gameState = GameState:new()

------------------------------------------------------------------------------------------
-- game state extensions

function GameState:Register()
	EngineState:SetOnScreenSizeChange(function(w, h, d)
		print("Screen parameters changed to " .. w .. "x" .. h .. " at " .. d)
		self:OnResolutionChange(w, h, d)
	end)
	
	EventsManager:RegisterMouseMovedEvents(function(x, y)
		--print("Mouse position = " .. x .. ", " .. y)
	end)
	
	EventsManager:RegisterMouseClickedEvents(function(x, y)
		print("Mouse clicked position = " .. x .. ", " .. y)
		character:SetHidden(false)
		character:WalkTo(x, y)
	end)
	
	EventsManager:RegisterKeyShortcutsEvents("control", "w|t", function()
		print("control & w & t pressed simulataneously")
	end)
end

------------------------------------------------------------------------------------------
-- loading functions

function loadSprites()	

	local atlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )
	scene = SceneManager:SceneCreateNew()
	local roomAtlas = AtlasManager:SpriteAtlasLoad( "parlor.json", "parlor.png" )
	local tdsSprite = AtlasManager:SpriteAtlasLoad( "TDS.json", "TDS.png")

	-- character
	character = scene:LoadCharacter("brett_character.json")
	character:SetScale(1)
	character:PlaceAt(300, 300)
	--character:SetInverseWalkbox("polygons.json")
	character:SetWalkingSpeed(600)
	character:SetHidden(false)
	character:SetZPosition(0)
	scene:SetMouseDownFunction(mouseDown)

	-- sky
	sky2 = scene:SpriteStaticLoad(atlas, "background.png")
	sky2:SetScale(1)
	sky2:SetAlpha(1)
	sky2:SetPosition(0, 0)
	sky2:SetAcceptsLight(true)
	 
	-- sky = scene:SpriteStaticLoad(roomAtlas, "roombg")
	-- sky:SetScale(1)
	-- sky:SetAlpha(0)
	-- sky:SetPosition(1280/2, 300)

    local backgroundAtlas = AtlasManager:SpriteAtlasLoad("set_background.json", "set_background.png")
    -- sky = scene:SpriteStaticLoad(backgroundAtlas, "1.png")

    local sky2 = scene:SpriteStaticLoad(backgroundAtlas, "2.png")
    local sky3 = scene:SpriteStaticLoad(backgroundAtlas, "3.png")
    sky5 = scene:SpriteStaticLoad(backgroundAtlas, "tile79.png")
    sky5:SetScale(0.5)

	tds = scene:SpriteAnimatedLoad(100, tdsSprite)
	tds:SetPosition(410, 180)
	tds:SetAlpha(0.5)
	tds:SetScale(1.5)
	tds:SetAcceptsLight(true)
	tds:SetAnimationFrameDuration(250)
	tds:SetColorMod(0.0, 1.0, 0.0, 1.0)

	-- lights
	light = LightManager:CreateLight("linear", 1, 1, 1, 0.1, 400, 350, 250, 1)
	light1 = scene:CreateLight("exponential", 1, 1, 1, 0.01, 900, 350, 11500, 0.5)
	light:SetName("Main light")
    LightManager:SetLightsActive(false)

	-- player
	local playerAtlas = AtlasManager:SpriteAtlasLoad("player_Idle.json", "player_Idle.png")
	playerSprite = scene:SpriteAnimatedLoad(250, playerAtlas)
	playerSprite:SetPosition(600, 300)
	playerSprite:SetZPosition(0.5)
end

function loadSounds()
    sound = SoundManager:Load("Rondo_Alla_Turka.ogg")
    soundObserverRef = sound:AddObserver(function(state)
    	print("State = " .. state)
    	if state == 10 then
    		sound:RemoveObserver(soundObserverRef)
    	end
    end)
    sound:Play()
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

function animateLights()
	local animatorForward, animatorBackwards
	
	animatorForward = ValueAnimatorFactory:CreateLinear(0, 1280, 2, 0,
		function(val)
			local x, y = light1:GetPosition()
			x = val
			light1:SetPosition(x,y)
		end,
		function()
			animatorBackwards:Start()
	  	end
	)
	
	animatorBackwards = ValueAnimatorFactory:CreateLinear(1280, 0, 2, 0,
		function(val)
			local x, y = light1:GetPosition()
			x = val
			light1:SetPosition(x,y)
		end,
		function()
			animatorForward:Start()
	  	end
	)

	animatorForward:Start()
end

function animateTrees()
    local animatorForward, animatorBackwards

	animatorForward = ValueAnimatorFactory:CreateLinear(0, 50, 1, 0,
		function(val)
			local x, y = sky5:GetPosition()
			x = val
			sky5:SetPosition(x,y)
		end,
		function()
			animatorBackwards:Start()
	  	end
	)

    animatorBackwards = ValueAnimatorFactory:CreateLinear(50, 0, 1, 0,
        function(val)
            local x, y = sky5:GetPosition()
			x = val
			sky5:SetPosition(x,y)
        end,
        function()
            animatorForward:Start()
        end
    )

    animatorForward:Start()
end

function shakeScreen()
    local propertyAnimatorDown, propertyAnimatorUp
    local counter = 0

    propertyAnimatorDown = PropertyAnimatorFactory:SetPosition(EngineScreen, "linear", 0, 10, 0, .5/200, 
        function()
            propertyAnimatorUp:Start()
        end
    )

    propertyAnimatorUp = PropertyAnimatorFactory:SetPosition(EngineScreen, "linear", 0, 0, 0, .5/200, 
        function()
            counter = counter + 1
            if counter < 50 then
                propertyAnimatorDown:Start()
            else
                propertyAnimatorDown:FreeMem()
                propertyAnimatorUp:FreeMem()
            end
        end
    )
    propertyAnimatorDown:Start()
end

------------------------------------------------------------------------------------------
-- event handling functions

function mouseDown(x, y)
end

------------------------------------------------------------------------------------------
-- script entry point functions

function init()
	gameState:Register()
	
  	--animateIntro()
  	
    --loadSounds()
    
   local gameIntro = GameIntroScene:New()
   gameIntro:Setup()
   gameIntro:Start(function()
	   loadSprites()
	   SceneManager:SceneMakeActive(scene)
	   animateLights()
       animateTrees()

    --    EngineScreen:SetOffset(0, 0)
       shakeScreen()
	   --loadSounds()
   end)
end

function update ()
end
