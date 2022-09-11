-- requires
local Vector2 = require "game_vector"

-- defines
local MAX_SPEED = 100   -- maximum speed (px/s)
local INC_SPEED = 5     -- speed increase when force applied (in px/s)
local DMP_SPEED = -2    -- speed fall when force not applied (in px/s)

-- class definition
local mt = {}

-- constructor
local new = function()
    local obj = {
        position = Vector2()     -- the character position
      , movement = Vector2()     -- the speed in all axis

      , timeMgr   = Time
      , speedIncrease = 0
      , speedDump = 0

      , forceApplied = false
      , lastForceApplied = false
    }
    return setmetatable(obj, mt)
end

mt.__tostring = function(self)
    return "IntertiaManager(" .. "position=" .. self.position:__tostring()  .. ")"
end

-- functions

mt.setForceApplied = function(self, value)
    self.forceApplied = value
end

mt.advance = function(self)
    if self.forceApplied then
        local frameDeltaSecs = self.timeMgr:GetFrameDeltaSec()
        self.speedIncrease = math.min(INC_SPEED, frameDeltaSecs * INC_SPEED)
    else
        self.speedIncrease = 0
    end
end

mt.damper = function(self)
    local frameDeltaSecs = self.timeMgr:GetFrameDeltaSec()
    self.speedDump = math.max(DMP_SPEED, frameDeltaSecs * DMP_SPEED)
end

mt.updatePosition = function(self)
    local movementX, movementY = self.movement:unpack()
    movementX = math.max(0, movementX + self.speedIncrease + self.speedDump)
    self.movement:setX(movementX)
end

mt.afterFrameReset = function(self)
    self.forceApplied = false
end

mt.frameUpdate = function(self)
    if self.lastForceApplied ~= self.forceApplied then
        print("Force applied = " .. tostring(self.forceApplied))

        self.lastForceApplied = self.forceApplied
    end

    local frameDeltaSecs = self.timeMgr:GetFrameDeltaSec()

    -- increse the speed if force applied
    self:advance()

    -- damper the movement vector by env. factor
    self:damper()

    -- apply force to the movement vector if available
    self:updatePosition()

    -- modify the position by the movement vector
    self.position:translateByVector(self.movement)

    -- reset
    self:afterFrameReset()
end

-- closing and definition
mt.__index = mt

-- constructor passing
local ctor = function(cls, ...)
    return new(...)
end

-- return the module
return setmetatable({}, {__call = ctor})
