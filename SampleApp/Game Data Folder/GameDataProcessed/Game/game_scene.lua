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

    foo = {}
    table.insert(foo, "bar")

    o.objCount = 1000

    o.objects = {}

    local x = 0
    local y = 0

    for index=0,o.objCount do
        object = o.scene:SpriteStaticLoad(o.atlas, "background.png")

        table.insert(
            o.objects
          , object
        )

        object:SetScale(0.25)
        object:SetPosition(x, y)
        object:SetRotation(0, -1, -1)

        x = x + 10
        y = y + 10

        if x > 1000 then 
            x = 0
        end

        if y > 200 then
            y = 0
        end
        
    end

    local angle = 0

    for index=1,o.objCount do
        local object = o.objects[index]
        object:SetRotation(angle, -1, -1)

        angle = angle + 10
        if angle > 360 then
            angle = 0
        end
    end

    return o
end

function GameActionScene:Setup()
    -- self.spriteBackground:SetScale(self.confScale)
    -- self.spriteSky:SetScale(self.confScale)
    -- self.spriteFloor:SetScale(self.confScale)
    self.spriteBackground:SetScale(0.25)
    -- self.spriteBackground:SetRotation(0, -1, -1);
    self.spriteBackground:SetPosition(300, 300)

    EventsManager:RegisterMouseClickedEvents(function(x, y)
        print("GameActionScene Mouse clicked position = " .. x .. ", " .. y)
    end)

    self.scene:RegisterFrameUpdate(function()
        self:Update()
    end)
end

function GameActionScene:Activate()
    self:Setup()
    SceneManager:SceneMakeActive(self.scene)
end

function GameActionScene:Update()
    for index=1,o.objCount do
        local object = self.objects[index]
        local angle, v1, v2 = object:GetRotation()
        angle = angle + 1
        if angle > 360 then
            angle = 0
        end

        object:SetRotation(angle, v1, v2)
    end
end