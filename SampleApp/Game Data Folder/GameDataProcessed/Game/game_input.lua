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
end

mt.Register = function(self)
    EventsManager:RegisterKeyDown(function(key)
        self.keys[key] = true
        if self.keys[self.keyRight] then
            self.vector:setX(1.0)
        end
        if self.keys[self.keyLeft] then
            self.vector:setX(-1.0)
        end
        if self.keys[self.keyUp] then
            self.vector:setY(-1.0)
        end
        if self.keys[self.keyDown] then
            self.vector:setY(1.0)
        end
    end)

    EventsManager:RegisterKeyUp(function(key)
        self.keys[key] = false
        if self.keys[self.keyRight] ~= true then
            self.vector:setX(0.0)
        end
        if self.keys[self.keyLeft] ~= true then
            self.vector:setX(0.0)
        end
        if self.keys[self.keyUp] ~= true then
            self.vector:setY(0.0)
        end
        if self.keys[self.keyDown] ~= true then
            self.vector:setY(0.0)
        end
    end)
end

-- result
mt.__index = mt

local ctor = function(cls, ...)
    return new(...)
end

return setmetatable({}, {__call = ctor})
