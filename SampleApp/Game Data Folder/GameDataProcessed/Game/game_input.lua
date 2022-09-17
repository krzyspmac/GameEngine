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
      , gamepad = nil
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
    self:registerKeys()
    
    EventsManager:RegisterGamepadConnection(function(gamepad)
        self:processGamepadConnection()
    end)

    self:processGamepadConnection()
end

mt.registerKeys = function(self)
    EventsManager:RegisterKeyDown(function(key)
        self.keys[key] = true
        self:Update()
    end)

    EventsManager:RegisterKeyUp(function(key)
        self.keys[key] = false
        self:Update()
    end)
end

mt.processGamepadConnection = function(self)
    self.gamepad = EventsManager:GetGamepad()

    if self.gamepad then
        print("Gamepad exists: type=" .. tostring(self.gamepad))

        self.gamepad:RegisterLeftThumbstickAxis(function(x, y)
            self.vector:set(x, y)
        end)

        self.gamepad:RegisterRightThumbstickAxis(function(x, y)
            self.vector:set(x*3, y*3)
        end)

        self.gamepad:RegisterDpadAxis(function(x, y)
            self.vector:set(x/2, y/2)
        end)

        self.gamepad:RegisterButtonTapped(function(buttonType, buttonAction, buttonValue)
            print("Button = " .. buttonType .. ", buttonAciton = " .. buttonAction .. ", buttonValue = " .. buttonValue)
        end)

        self.gamepad:SetLight(1, 0, 0)
    else
        print("No gamepad")
    end
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
