#include "TextureManager.h"

TextureManager::TextureManager()
{
	//// SET SPRITES ////
	spritesheets["lvl1"] = loadSprite(".\\assets\\Lvl1.png");
	spritesheets["all"] = loadSprite(".\\assets\\allSprites.png");
	spritesheets["characters"] = loadSprite(".\\assets\\allCharacters.png");

	//// SET INT RECS ////
	//// LIGHT PLAYER ////
	setFrames("lightIdle", std::vector<sf::IntRect> { sf::IntRect(90, 13, 210, 492) });

	setFrames("lightRun", std::vector<sf::IntRect>
	{ sf::IntRect(21, 576, 177, 451),
		sf::IntRect(240, 579, 177, 451),
		sf::IntRect(468, 579, 177, 451),
		sf::IntRect(240, 579, 177, 451)});

	setFrames("lightJump", std::vector<sf::IntRect>
	{ sf::IntRect(915, 601, 192, 442),
		sf::IntRect(1183, 596, 192, 442),
		sf::IntRect(1457, 602, 192, 442),
		sf::IntRect(240, 579, 177, 451),
		sf::IntRect(1760, 586, 199, 441),
		sf::IntRect(2026, 585, 199, 441),
		sf::IntRect(2284, 584, 199, 441)});

	//// DARK PLAYER ////
	setFrames("darkIdle", std::vector<sf::IntRect> { sf::IntRect(397, 182, 259, 326) });

	setFrames("darkRun", std::vector<sf::IntRect>
	{ sf::IntRect(23, 1184, 163, 291),
		sf::IntRect(260, 1183, 163, 291),
		sf::IntRect(503, 1183, 163, 291),
		sf::IntRect(260, 1183, 163, 291)});

	setFrames("darkJump", std::vector<sf::IntRect>
	{ sf::IntRect(931, 1180, 160, 283),
		sf::IntRect(1169, 1180, 160, 283),
		sf::IntRect(1421, 1177, 160, 283),
		sf::IntRect(260, 1183, 169, 228),
		sf::IntRect(1698, 1180, 165, 291),
		sf::IntRect(1944, 1178, 165, 291),
		sf::IntRect(2190, 1180, 165, 291)});

	//// DOORS //// 
	setFrames("lightDoor", std::vector<sf::IntRect> { sf::IntRect(24, 24, 67, 92) });
	setFrames("darkDoor", std::vector<sf::IntRect> { sf::IntRect(108, 24, 67, 92) });

	//// PLATFORMS ////
	setFrames("tiltingPlat", std::vector<sf::IntRect> { sf::IntRect(256, 6, 625, 43) });

	setFrames("yellowGlow", std::vector<sf::IntRect> { sf::IntRect(538, 239, 150, 35) });
	setFrames("purpleGlow", std::vector<sf::IntRect> { sf::IntRect(711, 239, 150, 35) });
	setFrames("blueGlow", std::vector<sf::IntRect> { sf::IntRect(540, 295, 150, 35) });
	setFrames("greenGlow", std::vector<sf::IntRect> { sf::IntRect(712, 204, 150, 35) });

	setFrames("yellowPlat", std::vector<sf::IntRect> { sf::IntRect(23, 144, 150, 35) });
	setFrames("purplePlat", std::vector<sf::IntRect> { sf::IntRect(23, 200, 150, 35) });
	setFrames("bluePlat", std::vector<sf::IntRect> { sf::IntRect(22, 253, 150, 35) });
	setFrames("greenPlat", std::vector<sf::IntRect> { sf::IntRect(21, 306, 150, 35) });

	//// BUTTONS ////
	setFrames("yellowButton", std::vector<sf::IntRect> { sf::IntRect(882, 151, 82, 28) });
	setFrames("purpleButton", std::vector<sf::IntRect> { sf::IntRect(884, 199, 82, 28) });
	setFrames("blueButton", std::vector<sf::IntRect> { sf::IntRect(885, 243, 82, 28) });
	setFrames("greenButton", std::vector<sf::IntRect> { sf::IntRect(885, 291, 82, 28) });

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

	//// PICKUPS ////
	setFrames("lightPickUp", std::vector<sf::IntRect> { sf::IntRect(793, 59, 69, 67) });
	setFrames("darkPickUp", std::vector<sf::IntRect> { sf::IntRect(892, 58, 70, 67) });

	//// MISC ////
	setFrames("Block", std::vector<sf::IntRect> { sf::IntRect(193, 40, 76, 76) });


	//// SET ANIM TIME ////
	animTime["yellowLever"] = 0.3f;
	animTime["yellowLeverReverse"] = 0.3f;
	animTime["blueLever"] = 0.3f;
	animTime["blueLeverReverse"] = 0.3f;
	animTime["greenLever"] = 0.3f;
	animTime["greenLeverReverse"] = 0.3f;
	animTime["purpleLever"] = 0.3f;
	animTime["purpleLeverReverse"] = 0.3f;

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