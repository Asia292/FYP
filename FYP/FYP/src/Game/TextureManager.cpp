#include "TextureManager.h"

TextureManager::TextureManager()
{
	//// SET SPRITES ////
	spritesheets["menu"] = loadSprite(".\\assets\\menuBG.png");
	spritesheets["levelSelect"] = loadSprite(".\\assets\\select.png");
	spritesheets["lvl1"] = loadSprite(".\\assets\\levels\\Lvl1.png");
	spritesheets["lvl2"] = loadSprite(".\\assets\\levels\\Lvl2.png");
	spritesheets["lvl3"] = loadSprite(".\\assets\\levels\\Lvl3.png");
	spritesheets["lvl4"] = loadSprite(".\\assets\\levels\\Lvl4.png");
	spritesheets["lvl5"] = loadSprite(".\\assets\\levels\\Lvl5.png");
	spritesheets["lvl1Cover"] = loadSprite(".\\assets\\levels\\Lvl1Cover.png");
	spritesheets["lvl2Cover"] = loadSprite(".\\assets\\levels\\Lvl2Cover.png");
	spritesheets["lvl3Cover"] = loadSprite(".\\assets\\levels\\Lvl3Cover.png");
	spritesheets["lvl4Cover"] = loadSprite(".\\assets\\levels\\Lvl4Cover.png");
	spritesheets["lvl5Cover"] = loadSprite(".\\assets\\levels\\Lvl5Cover.png");
	spritesheets["all"] = loadSprite(".\\assets\\allSprites.png");
	spritesheets["characters"] = loadSprite(".\\assets\\allCharacters.png");
	spritesheets["over"] = loadSprite(".\\assets\\over.png");

	//// LEVEL PREVIEWS ////
	spritesheets["onePreview"] = loadSprite(".\\assets\\levelPreview\\1Preview.png");
	spritesheets["twoPreview"] = loadSprite(".\\assets\\levelPreview\\2Preview.png");
	spritesheets["threePreview"] = loadSprite(".\\assets\\levelPreview\\3Preview.png");
	spritesheets["fourPreview"] = loadSprite(".\\assets\\levelPreview\\4Preview.png");
	spritesheets["fivePreview"] = loadSprite(".\\assets\\levelPreview\\5Preview.png");

	//// SET INT RECS ////
	//// LIGHT PLAYER ////
	setFrames("lightIdle", std::vector<sf::IntRect> { sf::IntRect(108, 123, 153, 382) });

	setFrames("lightRun", std::vector<sf::IntRect>
	{ sf::IntRect(49, 656, 124, 370),
		sf::IntRect(270, 658, 124, 370),
		sf::IntRect(495, 656, 124, 370),
		sf::IntRect(270, 658, 124, 370)});

	setFrames("lightJump", std::vector<sf::IntRect>
	{ sf::IntRect(945, 682, 137, 359),
		sf::IntRect(1224, 675, 137, 361),
		sf::IntRect(1501, 678, 138, 361),
		sf::IntRect(270, 658, 124, 370),
		sf::IntRect(1790, 665, 138, 361),
		sf::IntRect(2055, 664, 138, 361),
		sf::IntRect(2319, 663, 137, 361)});

	//// DARK PLAYER ////
	setFrames("darkIdle", std::vector<sf::IntRect> { sf::IntRect(406, 197, 231, 309) });

	setFrames("darkRun", std::vector<sf::IntRect>
	{ sf::IntRect(23, 1184, 163, 291),
		sf::IntRect(260, 1183, 163, 291),
		sf::IntRect(503, 1183, 163, 291),
		sf::IntRect(260, 1183, 163, 291)});

	setFrames("darkJump", std::vector<sf::IntRect>
	{ sf::IntRect(931, 1180, 160, 283),
		sf::IntRect(1169, 1180, 160, 283),
		sf::IntRect(1421, 1177, 160, 283),
		sf::IntRect(260, 1183, 169, 291),
		sf::IntRect(1698, 1180, 165, 291),
		sf::IntRect(1944, 1178, 165, 291),
		sf::IntRect(2190, 1180, 165, 291)});

	//// DOORS //// 
	setFrames("lightDoor", std::vector<sf::IntRect> { sf::IntRect(24, 24, 67, 92) });
	setFrames("darkDoor", std::vector<sf::IntRect> { sf::IntRect(108, 24, 67, 92) });

	//// PLATFORMS ////
	setFrames("tiltingPlat", std::vector<sf::IntRect> { sf::IntRect(287, 8, 619, 41) });
	setFrames("lvl2Tilt", std::vector<sf::IntRect> { sf::IntRect(863, 450, 128, 27) });

	setFrames("yellowGlow", std::vector<sf::IntRect> { sf::IntRect(538, 239, 150, 35) });
	setFrames("purpleGlow", std::vector<sf::IntRect> { sf::IntRect(711, 239, 150, 35) });
	setFrames("blueGlow", std::vector<sf::IntRect> { sf::IntRect(540, 295, 150, 35) });
	setFrames("greenGlow", std::vector<sf::IntRect> { sf::IntRect(711, 295, 150, 35) });
	setFrames("redGlow", std::vector<sf::IntRect> { sf::IntRect(539, 346, 150, 35) });
	setFrames("whiteGlow", std::vector<sf::IntRect> { sf::IntRect(710, 345, 150, 35) });

	setFrames("yellowPlat", std::vector<sf::IntRect> { sf::IntRect(23, 144, 150, 35) });
	setFrames("purplePlat", std::vector<sf::IntRect> { sf::IntRect(23, 200, 150, 35) });
	setFrames("bluePlat", std::vector<sf::IntRect> { sf::IntRect(22, 253, 150, 35) });
	setFrames("greenPlat", std::vector<sf::IntRect> { sf::IntRect(21, 306, 150, 35) });
	setFrames("redPlat", std::vector<sf::IntRect> { sf::IntRect(21, 357, 150, 35) });
	setFrames("whitePlat", std::vector<sf::IntRect> { sf::IntRect(19, 407, 150, 35) });

	//// BUTTONS ////
	setFrames("yellowButton", std::vector<sf::IntRect> { sf::IntRect(882, 151, 82, 28) });
	setFrames("purpleButton", std::vector<sf::IntRect> { sf::IntRect(884, 199, 82, 28) });
	setFrames("blueButton", std::vector<sf::IntRect> { sf::IntRect(885, 243, 82, 28) });
	setFrames("greenButton", std::vector<sf::IntRect> { sf::IntRect(885, 291, 82, 28) });
	setFrames("redButton", std::vector<sf::IntRect> { sf::IntRect(884, 342, 82, 28) });
	setFrames("whiteButton", std::vector<sf::IntRect> { sf::IntRect(884, 390, 82, 28) });

	//// LEVERS ////
	setFrames("yellowLever", std::vector<sf::IntRect>
	{ sf::IntRect(486, 51, 86, 79),
		sf::IntRect(387, 52, 86, 79),
		sf::IntRect(288, 53, 86, 79)});
	setFrames("yellowLeverReverse", std::vector<sf::IntRect>
	{ sf::IntRect(288, 53, 86, 79),
		sf::IntRect(387, 52, 86, 79),
		sf::IntRect(486, 51, 86, 79)});
	setFrames("purpleLever", std::vector<sf::IntRect>
	{ sf::IntRect(424, 154, 86, 79),
		sf::IntRect(320, 153, 86, 79),
		sf::IntRect(213, 152, 86, 79)});
	setFrames("purpleLeverReverse", std::vector<sf::IntRect>
	{ sf::IntRect(213, 152, 86, 79),
		sf::IntRect(320, 153, 86, 79),
		sf::IntRect(424, 154, 86, 79)});
	setFrames("blueLever", std::vector<sf::IntRect>
	{ sf::IntRect(753, 134, 86, 79),
		sf::IntRect(651, 132, 86, 79),
		sf::IntRect(548, 133, 86, 79)});
	setFrames("blueLeverReverse", std::vector<sf::IntRect>
	{ sf::IntRect(548, 133, 86, 79),
		sf::IntRect(651, 132, 86, 79),
		sf::IntRect(753, 134, 86, 79)});
	setFrames("greenLever", std::vector<sf::IntRect>
	{ sf::IntRect(421, 255, 86, 79),
		sf::IntRect(319, 253, 86, 79),
		sf::IntRect(212, 253, 86, 79)});
	setFrames("greenLeverReverse", std::vector<sf::IntRect>
	{ sf::IntRect(212, 253, 86, 79),
		sf::IntRect(319, 253, 86, 79),
		sf::IntRect(421, 255, 86, 79)});
	setFrames("redLever", std::vector<sf::IntRect>
	{ sf::IntRect(417, 353, 86, 79),
		sf::IntRect(313, 351, 86, 79),
		sf::IntRect(211, 352, 86, 79)});
	setFrames("redLeverReverse", std::vector<sf::IntRect>
	{ sf::IntRect(211, 352, 86, 79),
		sf::IntRect(313, 351, 86, 79),
		sf::IntRect(417, 353, 86, 79)});
	setFrames("whiteLever", std::vector<sf::IntRect>
	{ sf::IntRect(758, 401, 86, 79),
		sf::IntRect(655, 399, 86, 79),
		sf::IntRect(557, 397, 86, 79)});
	setFrames("whiteLeverReverse", std::vector<sf::IntRect>
	{ sf::IntRect(557, 397, 86, 79),
		sf::IntRect(655, 399, 86, 79),
		sf::IntRect(758, 401, 86, 79)});

	//// PICKUPS ////
	setFrames("lightPickUp", std::vector<sf::IntRect> { sf::IntRect(847, 53, 70, 67) });
	setFrames("darkPickUp", std::vector<sf::IntRect> { sf::IntRect(924, 53, 70, 66) });

	//// MISC ////
	setFrames("Block", std::vector<sf::IntRect> { sf::IntRect(193, 40, 76, 76) });
	setFrames("Ball", std::vector<sf::IntRect> { sf::IntRect(951, 7, 38, 37) });
	setFrames("Green", std::vector<sf::IntRect> { sf::IntRect(770, 53, 70, 66) });
	setFrames("Orange", std::vector<sf::IntRect> { sf::IntRect(610, 53, 70, 66) });
	setFrames("Red", std::vector<sf::IntRect> { sf::IntRect(691, 53, 70, 66) });
	setFrames("Empty", std::vector<sf::IntRect> { sf::IntRect(624, 143, 27, 24) });

	//// SET ANIM TIME ////
	animTime["yellowLever"] = 0.3f;
	animTime["yellowLeverReverse"] = 0.3f;
	animTime["blueLever"] = 0.3f;
	animTime["blueLeverReverse"] = 0.3f;
	animTime["greenLever"] = 0.3f;
	animTime["greenLeverReverse"] = 0.3f;
	animTime["purpleLever"] = 0.3f;
	animTime["purpleLeverReverse"] = 0.3f;
	animTime["redLever"] = 0.3f;
	animTime["redLeverReverse"] = 0.3f;
	animTime["whiteLever"] = 0.3f;
	animTime["whiteLeverReverse"] = 0.3f;

	animTime["darkRun"] = 0.5f;
	animTime["lightRun"] = 0.5f;
	animTime["darkJump"] = 1.f;
	animTime["lightJump"] = 1.f;
}


std::shared_ptr<sf::Texture> TextureManager::loadSprite(std::string location)
{
	std::shared_ptr<sf::Texture> tex(new sf::Texture);
	if (!tex->loadFromFile(location))
		std::cout << "Cant load " << location << std::endl;

	return tex;
}

std::shared_ptr<sf::Texture> TextureManager::getTexture(std::string keyName)
{
	return spritesheets[keyName];
}

void TextureManager::setTexture(std::string keyName, Texture * target)
{
	//std::cout << "PASSED: " << spritesheets[keyName] << std::endl;
	target->setSpriteSheet(spritesheets[keyName]);
}

void TextureManager::setFrames(std::string keyName, std::vector<sf::IntRect> keyFrames)
{
	frames[keyName] = keyFrames;
}

void TextureManager::getFrames(std::string keyName, Texture * target)
{
	currState = keyName;
	target->setKeyFrames(frames[keyName], animTime[keyName]);
}

std::string TextureManager::getState()
{
	//std::cout << currState << std::endl;
	return currState;
}

TextureManager * TextureManager::onlyInstance = nullptr;
unsigned short int TextureManager::instanceCount = 0;
TextureManager * TextureManager::getInstance()
{
	if (instanceCount != 0)
		return onlyInstance;
	else
	{
		onlyInstance = new TextureManager;
		instanceCount = 1;
		return onlyInstance;
	}
}

void TextureManager::delInstance()
{
	//delete onlyInstance;
	onlyInstance = nullptr;
	instanceCount = 0;
}

TextureManager::~TextureManager()
{
	delInstance();
}