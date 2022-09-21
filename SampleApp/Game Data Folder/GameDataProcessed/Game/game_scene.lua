--------------------------------
-- requires

require "game_general"
require "game_inertia_manager"
require "game_vector"

local Vector2 = require "game_vector"
local IntertiaManager = require "game_inertia_manager"
local GameInput = require "game_input"

--------------------------------
-- class definition

GameActionScene = {}
GameActionScene.__index = GameActionScene

function GameActionScene:New()
    o = {}
    setmetatable(o, GameActionScene)
    self.__index = self

    o.gameInput = GameInput()
    o.im = IntertiaManager()

    o.scene = SceneManager:SceneCreateNew()
    o.atlas = AtlasManager:SpriteAtlasLoad("background.json", "background.png")
    o.spriteBackground = o.scene:SpriteStaticLoad(o.atlas, "background.png")

    local animatedSpriteAtlas = AtlasManager:SpriteAtlasLoad("player_Idle.json", "player_Idle.tga")
    o.animated = o.scene:SpriteAnimatedLoad(100, animatedSpriteAtlas)
    o.animatedRotation = 0

    return o
end

function GameActionScene:Setup()
    -- setup
    self.gameInput:Register()

    -- sprites
    self.spriteBackground:SetScale(0.25)
    self.spriteBackground:SetPosition(300, 300)
    self.im.position:set(300, 300)

    EventsManager:RegisterMouseClickedEvents(function(x, y)
        print("GameActionScene Mouse clicked position = " .. x .. ", " .. y)
        self:UpdateMovement()
    end)

    EventsManager:RegisterKeyShortcutsEvents("", "w", function()
        self:UpdateMovement()
    end)

    self.scene:RegisterFrameUpdate(function()
        self:Update()
    end)
end

function GameActionScene:Activate()
    self:Setup()
    SceneManager:SceneMakeActive(self.scene)
end

function GameActionScene:UpdateMovement()
    --o.im:advance()
end

function GameActionScene:Update()
    -- apply game input
    self.im:updateForceVector(self.gameInput.vector)

    -- modify the position
    self.im:frameUpdate()

    -- update character location
    local x, y = self.im.position:unpack()
    self.animated:SetPosition(x, y)
end