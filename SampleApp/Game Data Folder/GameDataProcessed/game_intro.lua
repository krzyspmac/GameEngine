------------------------------------------------------------------------------------------
-- game intro
-- created at the start of the script and holds some dear information used later;
-- the initial resolution is kept in the .ini file but the script has the final say
-- in what the resolution will be and what will be the final scale of the frame-buffer

GameIntroScane = {}
GameIntroScane.__index = GameIntroScane

function GameIntroScane:New()
	local o = {};
	setmetatable(o, GameState)
	self.scene = SceneManager:SceneCreateNew()
	return o
end

function GameIntroScene:Setup()
	
end