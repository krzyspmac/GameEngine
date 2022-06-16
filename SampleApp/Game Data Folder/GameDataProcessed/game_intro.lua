print("module.game_intro loaded")

require("game_general")

------------------------------------------------------------------------------------------
-- GameIntroScene
-- animate over a bunch of text lines

GameIntroScene = {}
GameIntroScene.__index = GameIntroScene

function GameIntroScene:New()
	o = {};
	setmetatable(o, GameIntroScene)
	self.__index = self
	
	o.scene = SceneManager:SceneCreateNew()
	o.font = FontManager:LoadFont("at01.fnt", "at01.png")
	o.texts = {
		  "Gallia est omnis divisa in partes tres️."
	   }
	o.textsCount = tableLength(o.texts)
	o.textsIndex = 1
	
	return o
end

function GameIntroScene:Setup()
	textSprite = self.scene:SpriteTextLoad(self.font)
	textSprite:SetText("Gallia\nest omnis divisa\nin partes tres")
	textSprite:SetPosition(gameState.wantedWidth/2, gameState.wantedHeight/2)
	textSprite:SetAcceptsLight(true)
	textSprite:SetScale(2)
	textSprite:SetColorMod(1.0, 1.0, 1.0, 1.0)
	textSprite:SetLineHeightMultiplier(1.5)
	textSprite:SetAlignment("center")
	textSprite:SetZPosition(0.4)
	textSprite:SetAlpha(0)

	self.textSprite = textSprite
end

function GameIntroScene:Start(endFunction)
	self.endFunction = endFunction					-- store end function
	SceneManager:SceneMakeActive(self.scene)		-- make the scene active
	
	-- wait a bit at first
	AnimationGroupFactory:GroupAnimations(
		'sequence'
		, PropertyAnimatorFactory:Wait(0, 2)
		, function()
			self:Continue()							-- start the text fade ins and outs
		  end
	):Start()
end

function GameIntroScene:Continue()
	self.textSprite:SetText(self.texts[self.textsIndex])
	self:FadeTexts()
end

function GameIntroScene:Next()
	local nextIndex = self.textsIndex + 1;

	if nextIndex <= self.textsCount then
		self.textsIndex = nextIndex
		self:Continue()
	else
		self:End()
	end
end

function GameIntroScene:FadeTexts()

	local group = AnimationGroupFactory:GroupAnimations(
		'sequence'
	,	PropertyAnimatorFactory:FadeIn(self.textSprite, "linear", 0, 0.5)
	,	PropertyAnimatorFactory:Wait(0, 2)
	,	PropertyAnimatorFactory:FadeOut(self.textSprite, "linear", 0, 0.5)
	,	PropertyAnimatorFactory:Wait(0, 1)
	,	function()
			self:Next()
		end
	)
	
	group:Start()
end

function GameIntroScene:End()
	self.endFunction()
end
