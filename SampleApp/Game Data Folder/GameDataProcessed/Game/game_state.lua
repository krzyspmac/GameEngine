print("module.game_state loaded")

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
