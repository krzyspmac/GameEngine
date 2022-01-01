print("Total init")

--myFont = nil
--
--backgroundAtlas = nil
--backgroundSprite = nil
--backgroundSkySprite = nil
--backgroundSkyRenderer = nil
--
--brettAtlas = nil

function customLoading()
--	backgroundAtlas = L_spriteAtlasLoad("background.json", "background.png")    
--	backgroundSkySprite = L_spriteAtlasGetSprite(backgroundAtlas, "sky.png")    
--	backgroundSkyRenderer = L_spriteDrawStaticCreate(backgroundSkySprite, 2)
	
	local scene = SceneManager:SceneCreateNew()

	local sceneAtlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )

	background = SpriteRendererManager:SpriteDrawLoadStatic(
		sceneAtlas:GetItemForName("sky.png")
	)
	background:SetScale(2)
	scene:AddSpriteDrawStatic(background)

	rv = SpriteRendererManager:SpriteDrawLoadStatic(
		sceneAtlas:GetItemForName("background.png")
	)
	rv:SetScale(2)
	scene:AddSpriteDrawStatic(rv)
	
	character = scene:LoadCharacter("brett_character.json")
	character:SetScale(3)
	character:PlaceAt(100, 450)
	local x, y = character:GetPosition()
	print(x)
	print(y)
	character:SetInverseWalkbox("polygons.json")
--	character:WalkTo(716, 373)
	scene:SetMainCharacter(character)
	character:SetWalkingSpeed(400)
	
--	character:WalkTo(852, 226)
end

function helperLoading()
	local atlas = AtlasManager:SpriteAtlasLoad( "background.json", "background.png" )
	local scene = SceneManager:SceneCreateNew()

	backgroudnSpr = scene:LoadSpriteStatic(atlas, "sky.png")
	backgroudnSpr:SetScale(3)
	
	local tructSpr = scene:LoadSpriteStatic(atlas, "background.png")
	tructSpr:SetScale(2)
	
	character = scene:LoadCharacter("brett_character.json")
	character:SetScale(3)
	character:PlaceAt(100,450)
	character:SetInverseWalkbox("polygons.json")
	character:SetWalkingSpeed(400)
	
	--scene:SetMainCharacter(character)
	scene:SetMouseDownFunction("mouseDown")
	
	backgroudnSpr:SetAlpha(0)
end

function init()
--	customLoading()
	helperLoading()
end

animationStart = nil
alpha = 0
alpha_max = 255
alpha_speed_per_second = 100 -- change per second

animationCo = coroutine.create(function ()
	while alpha < alpha_max do
		second_change = Time:GetFrameStartSec() - animationStart
		alpha = math.max(0, math.min(255, alpha_speed_per_second * second_change))
		coroutine.yield()
	end
	animationStart = nil
end)

function mouseDown(x, y)
	print ("mouse down " .. x .. ", " .. y)
--	character:WalkTo(x, y)
	animationStart = Time:GetFrameStartSec()
	coroutine.resume(animationCo)
end

function update ()
	--L_spriteDrawRender(backgroundSkyRenderer, 0, 0)
--character:DrawAt(100, 200)
--	print(Time:GetEngineStart())
--	print(Time:GetFrameDeltaSec())
	--print(backgroudnSpr:GetAlpha())
	
--	backgroudnSpr:SetAlpha(120)
	if animationStart then
		backgroudnSpr:SetAlpha(alpha)
		print(coroutine.resume(animationCo))
	end
end
