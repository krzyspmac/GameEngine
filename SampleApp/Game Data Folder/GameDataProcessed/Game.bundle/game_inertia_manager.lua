-- requires
local Vector2 = require "game_vector"
local ValueAnimator = require "game_values_over_time"

-- defines
local MAX_SPEED = 20     -- maximum speed (px/s)
local INC_SPEED = 10     -- speed increase when force applied (in px/s)
local DMP_SPEED = 0.05   -- speed fall when force not applied (in px/s)

-- class definition
local mt = {}

-- constructor
local new = function()
    local obj = {
        position = Vector2()           -- the character position
      , movementVector = Vector2()     -- the movement vector; will directly affect the position
      , forceVector = Vector2()        -- the force vector (normalized)
      , timeMgr = Time
      , frameDeltaSec = 0
    }
    return setmetatable(obj, mt)
end

mt.__tostring = function(self)
    return "IntertiaManager(" .. "position=" .. self.position:__tostring()  .. ")"
end

-- functions

mt.updateForceVector = function(self, value)
    self.forceVector = value
end

mt.advance = function(self)
    local speedIncrease = math.min(INC_SPEED, self.frameDeltaSec * INC_SPEED)
    local incVector = self.forceVector * speedIncrease
    self.movementVector = self.movementVector + incVector
end

mt.damper = function(self)
    local dmpFactor = math.max(DMP_SPEED, self.frameDeltaSec * DMP_SPEED)
    local damperVector = self.movementVector:normalized():inversed() * dmpFactor
    self.movementVector = self.movementVector + damperVector
end

mt.limit = function(self)
    local length = math.min(MAX_SPEED, self.movementVector:length())
    self.movementVector = self.movementVector:normalized() * length
end

mt.updatePosition = function(self)
    self.position:translateByVector(self.movementVector)
end

mt.frameUpdate = function(self)
    self.frameDeltaSec = self.timeMgr:GetFrameDeltaSec()
    self:advance()
    self:damper()
    self:limit()
    self:updatePosition()
end

-- closing and definition
mt.__index = mt

-- constructor passing
local ctor = function(cls, ...)
    return new(...)
end

-- return the module
return setmetatable({}, {__call = ctor})
