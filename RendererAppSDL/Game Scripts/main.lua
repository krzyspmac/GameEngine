
a = 1

myTexture = nil

function init()
    myTexture = loadTexture("background.jpg")
end

function update ()
    a = a + 1
    if a > 60 then a = 0 end

    drawDebugText(0, 1, 0x0f, "Lua in a C++ Engine! " .. a)
    drawTexture(myTexture, 0, 0)
end
