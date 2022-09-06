--------------------------------
-- requires

--------------------------------
-- global variables

gameState = nil

--------------------------------
-- script entry point

function init()
    print("Main init function called")

    setup()
    showIntroScene()
end

function update ()
    --print("Main update function called")
end

--------------------------------
-- actions

function setup()
    -- setup game state
    require "game_state"

    gameState = GameState:new()
    gameState:PerformRegister()    
end

function showIntroScene()
    require "game_intro"

    local gameIntro = GameIntroScene:New()
    gameIntro:Setup()
    gameIntro:Start(function()
        showActionScene()
    end)
end

function showActionScene()
    require "game_scene"

    local gameAction = GameActionScene:New()
    gameAction:Activate()
end

--------------------------------
-- extensions

-- function GameState:Register()
-- 	EngineState:SetOnScreenSizeChange(function(w, h, d)
-- 		print("Screen parameters changed to " .. w .. "x" .. h .. " at " .. d)
-- 		self:OnResolutionChange(w, h, d)
-- 	end)
	
-- 	EventsManager:RegisterMouseMovedEvents(function(x, y)
-- 		--print("Mouse position = " .. x .. ", " .. y)
-- 	end)
	
-- 	EventsManager:RegisterMouseClickedEvents(function(x, y)
-- 		print("Mouse clicked position = " .. x .. ", " .. y)
-- 		-- character:SetHidden(false)
-- 		-- character:WalkTo(x, y)
-- 	end)
	
-- 	EventsManager:RegisterKeyShortcutsEvents("control", "w|t", function()
-- 		print("control & w & t pressed simulataneously")
-- 	end)
-- end
