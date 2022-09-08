--------------------------------
-- requires

require("game_general")

--------------------------------
-- class definition

GameActionScene = {}
GameActionScene.__index = GameActionScene

function GameActionScene:New()
    o = {}
    setmetatable(o, GameActionScene)
    self.__index = self

    o.confScale = 2.0

    o.scene = SceneManager:SceneCreateNew()
    o.atlas = AtlasManager:SpriteAtlasLoad("background.json", "background.png")
    o.spriteBackground = o.scene:SpriteStaticLoad(o.atlas, "background.png")
    -- o.atlas = AtlasManager:SpriteAtlasLoad("ega.json", "ega.png")
    -- o.spriteBackground = o.scene:SpriteStaticLoad(o.atlas, "background.png")
    -- o.spriteSky = o.scene:SpriteStaticLoad(o.atlas, "sky.png")
    -- o.spriteFloor = o.scene:SpriteStaticLoad(o.atlas, "floor.png")
    return o
end

function GameActionScene:Setup()
    -- self.spriteBackground:SetScale(self.confScale)
    -- self.spriteSky:SetScale(self.confScale)
    -- self.spriteFloor:SetScale(self.confScale)
    self.spriteBackground:SetScale(1)
    -- self.spriteBackground:SetPosition(300, 300)

    EventsManager:RegisterMouseClickedEvents(function(x, y)
        print("GameActionScene Mouse clicked position = " .. x .. ", " .. y)
    end)
end

function GameActionScene:Activate()
    self:Setup()
    SceneManager:SceneMakeActive(self.scene)
end