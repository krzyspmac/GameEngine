--------------------------------
-- requires

require "game_general"
require "game_inertia_manager"
require "game_vector"

local Vector2 = require "game_vector"
local IntertiaManager = require "game_inertia_manager"

--------------------------------
-- class definition

GameActionScene = {}
GameActionScene.__index = GameActionScene

function GameActionScene:New()
    o = {}
    setmetatable(o, GameActionScene)
    self.__index = self

    o.im = IntertiaManager()

    o.scene = SceneManager:SceneCreateNew()
    o.atlas = AtlasManager:SpriteAtlasLoad("background.json", "background.png")
    o.spriteBackground = o.scene:SpriteStaticLoad(o.atlas, "background.png")

    local animatedSpriteAtlas = AtlasManager:SpriteAtlasLoad("TDS.json", "TDS.png")
    o.animated = o.scene:SpriteAnimatedLoad(100, animatedSpriteAtlas)
    o.animatedRotation = 0

    return o
end

function GameActionScene:Setup()
    self.spriteBackground:SetScale(0.25)
    self.spriteBackground:SetPosition(300, 300)

    self.im.position:set(300, 300)

    EventsManager:RegisterMouseClickedEvents(function(x, y)
        print("GameActionScene Mouse clicked position = " .. x .. ", " .. y)
        self:UpdateMovement()
    end)

    EventsManager:RegisterKeyShortcutsEvents("", "w", function()
        print("w pressed")
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
    o.im:advance()
end

function GameActionScene:Update()
    -- modify the position
    self.im:frameUpdate()

    -- update character location
    local x, y = self.im.position:unpack()
    self.animated:SetPosition(x, y)
end