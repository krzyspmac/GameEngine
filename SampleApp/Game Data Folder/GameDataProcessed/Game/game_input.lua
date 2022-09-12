-- requires
local Vector2 = require "game_vector"

-- class definition
local mt = {}

-- constructor
local new = function()
    local obj = {
        keys = {}
      , keyRight = 'd'
      , keyUp = 'w'
      , keyDown = 's'
      , keyLeft = 'a'
      , directionRight = false
      , vector = Vector2()
    }
    local o = setmetatable(obj, mt)
    o:Setup()
    return o
end

function mt:__tostring()
    return "GameInput"
end

-- functionalities

mt.Setup = function(self)
    self:Update()
end

mt.Register = function(self)
    EventsManager:RegisterKeyDown(function(key)
        self.keys[key] = true
        self:Update()
    end)

    EventsManager:RegisterKeyUp(function(key)
        self.keys[key] = false
        self:Update()
    end)

    EventsManager:RegisterLeftThumbstickAxis(function(x, y)
        self.vector:set(x, y)
    end)
    
    EventsManager:RegisterRightThumbstickAxis(function(x, y)
        self.vector:set(x*3, y*3)
    end)
end

mt.Update = function(self)
    if self.keys[self.keyRight] then
        self.vector:setX(1.0)
    elseif self.keys[self.keyLeft] then
        self.vector:setX(-1.0)
    else
        self.vector:setX(0.0)
    end

    if self.keys[self.keyUp] then
        self.vector:setY(-1.0)
    elseif self.keys[self.keyDown] then
        self.vector:setY(1.0)
    else
        self.vector:setY(0.0)
    end
end

-- result
mt.__index = mt

local ctor = function(cls, ...)
    return new(...)
end

return setmetatable({}, {__call = ctor})
