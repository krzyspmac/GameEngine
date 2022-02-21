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

------------------------------------------------------------------------------------------
-- game state
-- created at the start of the script and holds some dear information used later;
-- the initial resolution is kept in the .ini file but the script has the final say
-- in what the resolution will be and what will be the final scale of the frame-buffer

GameState = {}
GameState.__index = GameState

function GameState:new()
	local o = {}; setmetatable(o, GameState)
	self.wantedWidth = 1280
	self.wantedHeight = 720
	return o
end

function GameState:OnResolutionChange(width, height, density)
	-- Calculate the wanted scale. We want to change the scale instead of changing
	-- the resolution itself. Changing the resolution would mean we have to update
	-- the UI as well.
	local scale = math.min(width / gameState.wantedWidth, height / gameState.wantedHeight)
	
	-- Apply the scale to our original frame-buffer size. We don't want to change
	-- the resolution itself. Scale will suffice.
	EngineState:SetViewportSize(gameState.wantedWidth, gameState.wantedHeight, scale)
end

function GameState:Register()
	EngineState:SetOnScreenSizeChange(function(w, h, d)
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

gameState = GameState:new()


------------------------------------------------------------------------------------------
-- loading functions

function loadSprites()	
	local atlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )
	local scene = SceneManager:SceneCreateNew()
	local roomAtlas = AtlasManager:SpriteAtlasLoad( "parlor.json", "parlor.png" )
	local tdsSprite = AtlasManager:SpriteAtlasLoad( "TDS.json", "TDS.png")

	-- character
	character = scene:LoadCharacter("brett_character.json")
	character:SetScale(1)
	character:PlaceAt(300, 300)
	--character:SetInverseWalkbox("polygons.json")
	character:SetWalkingSpeed(600)
	character:SetHidden(false)
	scene:SetMouseDownFunction(mouseDown)

	-- sky
	sky2 = scene:SpriteStaticLoad(atlas, "background.png")
	sky2:SetScale(1)
	sky2:SetAlpha(1)
	sky2:SetPosition(0, 0)
	sky2:SetAcceptsLight(true)

	sky = scene:SpriteStaticLoad(roomAtlas, "roombg")
	sky:SetScale(1)
	sky:SetAlpha(0)
	sky:SetPosition(1280/2, 200)

	tds = scene:SpriteAnimatedLoad(100, tdsSprite)
	tds:SetPosition(200, 200)
	tds:SetAlpha(0.5)
	tds:SetScale(1.5)
	tds:SetAcceptsLight(true)
	tds:SetAnimationFrameDuration(250)
	tds:SetColorMod(0.0, 1.0, 0.0, 1.0)

	-- lights
	light = LightManager:CreateLight("linear", 1, 1, 1, 0.1, 400, 350, 250, 1)
	light1 = scene:CreateLight("exponential", 1, 1, 1, 0.01, 900, 350, 11500, 0.5)
	light:SetName("Main light")

	-- player
	local playerAtlas = AtlasManager:SpriteAtlasLoad("player_Idle.json", "player_Idle.png")
	playerSprite = scene:SpriteAnimatedLoad(250, playerAtlas)
	playerSprite:SetPosition(600, 300)

	-- font
	local font = FontManager:LoadFont("at01.fnt", "at01.png")
	local textSprite = scene:SpriteTextLoad(font)
	textSprite:SetText("Test")
	textSprite:SetPosition(300, 300)
	textSprite:SetAcceptsLight(true)
	textSprite:SetScale(2)
	textSprite:SetColorMod(1.0, 1.0, 0.0, 1.0)
end

function registerResolutionChange()
--	EngineState:SetOnScreenSizeChange(gameState:onResolutionChange)
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

------------------------------------------------------------------------------------------
-- event handling functions

function mouseDown(x, y)
end

------------------------------------------------------------------------------------------
-- script entry point functions

function init()
	gameState:Register()
	loadSprites()
  	--animateIntro()
  	animateLights()
end

function update ()
end
