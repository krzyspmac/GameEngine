-- requires
local Vector2 = require "game_vector"

-- defines
local MAX_SPEED = 100   -- maximum speed (px/s)
local INC_SPEED = 10    -- speed increase when force applied (in px/s)
local FLL_SPEED = 20    -- speed fall when force not applied (in px/s)

-- class definition
local mt = {}

-- constructor
local new = function()
    local obj = {
        position = Vector2()     -- the character position
      , timeMgr   = Time
      , maxSpeed  = MAX_SPEED    -- the maxmum speed
      , incSpeed  = INC_SPEED    -- the speed increase
      , fallSpeed = FLL_SPEED    -- the speed fallout
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

mt.frameUpdate = function(self)
    local frameDeltaSecs = self.timeMgr:GetFrameDeltaSec()
end

-- closing and definition
mt.__index = mt

-- constructor passing
local ctor = function(cls, ...)
    return new(...)
end

-- return the module
return setmetatable({}, {__call = ctor})
