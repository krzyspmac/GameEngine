-- requires
local Vector2 = require "game_vector"

-- class definition
local mt = {}

-- constructor
local new = function()
    local obj = {
        position = Vector2()
    }
    return setmetatable(obj, mt)
end

mt.__tostring = function(self)
    return "IntertiaManager(" .. "position=" .. self.position:__tostring()  .. ")"
end

-- functions

mt.advance = function(self)
    self.position:translateBy(1, 0)
end

-- closing and definition
mt.__index = mt

-- constructor passing
local ctor = function(cls, ...)
    return new(...)
end

-- return the module
return setmetatable({}, {__call = ctor})
