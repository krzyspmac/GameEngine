
print("Total init")
a = 1

co = coroutine.create(function ()
	while true do
	--end
	--for i=1,10 do
    	a = a + 1
    	if a > 60 then a = 0 end

		coroutine.yield()
    end
end)




myTexture = nil
myFont = nil

walkTexture = nil
walkSprite = nil
walkRenderer = nil

atlas = nil
atlasSprite = nil

function init()
    myTexture = L_textureLoad("background.jpg")
    myFont = loadFont("EnterCommand.ttf")
    walkTexture = L_textureLoad("sheriff.png")
    walkSprite = L_spriteLoad(walkTexture, 0, 0, 68, 158)
    walkRenderer = L_spriteDrawCreate(walkSprite, 9, 100)
    
    --atlas = L_spriteAtlasLoad("image.json", "image.png")
    --atlasSprite = L_spriteAtlasGetSprite(atlas, "/characters/sheriff.png", 9, 100)
end

function update ()
    
    coroutine.resume(co)

	L_spriteDrawRender(walkRenderer, 40, 40)

--    drawTexture(myTexture, 0, 0)
--	drawText(myFont, "Lua in a C++ Engine! " .. a, 10, 10, 100, 100, 100, "left")
end
