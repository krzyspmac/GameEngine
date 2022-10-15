-- class definition
local mt = {}

-- check
local function is_vector(t)
    return getmetatable(t) == mt
end

-- constructor
local new = function(x, y)
    local obj = {
        x = x or 0,
        y = y or 0
    }

    return setmetatable(obj, mt)
end

-- operator overloading

function mt.__add(lhs, rhs)
    assert(is_vector(lhs) and is_vector(rhs), "Type mismatch: vector expected.")
    return new(lhs.x + rhs.x, lhs.y + rhs.y)
end

function mt.__sub(lhs, rhs)
    assert(is_vector(lhs) and is_vector(rhs), "Type mismatch: vector expected.")
    return new(lhs.x - rhs.x, lhs.y - rhs.y)
end

function mt.__mul(lhs, value)
    return new(lhs.x * value, lhs.y * value)
end

function mt.__eq(lhs, rhs)
    assert(is_vector(lhs) and is_vector(rhs), "Type mismatch: vector expected.")
    return lhs.x == rhs.x and lhs.y == rhs.y
end

function mt.__lt(lhs, rhs)
    assert(is_vector(lhs) and is_vector(rhs), "Type mismatch: vector expected.")
    return lhs.x < rhs.x or (not (rhs.x < lhs.x) and lhs.y < rhs.y)
end

function mt.__le(lhs, rhs)
    assert(is_vector(lhs) and is_vector(rhs), "Type mismatch: vector expected.")
    return lhs.x <= rhs.x or lhs.y <= rhs.y
end

function mt:__tostring()
    return "Vector2("..self.x..", "..self.y..")"
end

-- functionalities

mt.x = function(self)
    return self.x
end

mt.y = function(self)
    return self.y
end

mt.set = function(self, x, y)
    self.x = x
    self.y = y
end

mt.setX = function(self, x)
    self.x = x
end

mt.setY = function(self, y)
    self.y = y
end

mt.translateBy = function(self, x, y)
    self.x = self.x + x
    self.y = self.y + y
end

mt.translateByVector = function(self, rhs)
    assert(is_vector(rhs), "Type mismatch: vector expected.")
    local x, y = rhs:unpack()
    self.x = self.x + x
    self.y = self.y + y
end

mt.inversed = function(self)
    return new(-self.x, -self.y)
end

mt.scale = function(self, value)
    self.x = self.x * value
    self.y = self.y * value
end

mt.copy = function(self)
    return new(self.x, self.y)
end

mt.length = function(self)
    return math.sqrt(self.x * self.x + self.y * self.y)
end

mt.length_squared = function(self)
    return self.x * self.x + self.y * self.y
end

mt.is_unit = function(self)
    return self:length_squared() == 1
end

mt.unpack = function(self)
    return self.x, self.y
end

mt.normalize = function(self)
    local len = self:length()
    if len ~= 0 and len ~= 1 then
        self.x = self.x / len
        self.y = self.y / len
    end
    return self
end

mt.normalized = function(self)
    return self:copy():normalize()
end

-- closing and definition
mt.__index = mt

-- constructor passing
local ctor = function(cls, ...)
    return new(...)
end

-- return the module
return setmetatable({}, { __call = ctor })
