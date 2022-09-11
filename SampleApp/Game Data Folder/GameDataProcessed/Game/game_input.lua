-- class definition
local mt = {}

-- constructor
local new = function()
    local obj = {
        keys = {}
      , keyRight = 'd'
      , directionRight = false
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
            self.directionRight = true
        end
    end)

    EventsManager:RegisterKeyUp(function(key)
        self.keys[key] = false
        if self.keys[self.keyRight] ~= true then
            self.directionRight = false
        end
    end)
end

-- result
mt.__index = mt

local ctor = function(cls, ...)
    return new(...)
end

return setmetatable({}, {__call = ctor})
