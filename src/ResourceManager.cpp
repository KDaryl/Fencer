#include "ResourceManager.h"

/// <summary>
/// Authors: Daryl Keogh
/// Description: The resource manager is responsible for loading in any textures/fonts/sounds or videos we need.
/// Time Spent: 10 Minutes
/// </summary>

ResourceManager::ResourceManager()
{
	//load all of our resources
	try 
	{
		//load GUI
		acquireResource("Button Spritesheet Reversed", m_buttonLayoutReversed);
		acquireResource("Button Spritesheet", m_buttonLayout);
		acquireResource("Sound Icon", m_soundIcon);
		acquireResource("Music Icon", m_musicIcon);
		acquireResource("Button Selected", m_buttonSelected);
		acquireResource("Options Icon", m_optionsIcon);
		acquireResource("Exit Icon", m_exitIcon);
		acquireResource("Main Menu Icon", m_mainMenuIcon);
		acquireResource("Help Icon", m_helpIcon);
		acquireResource("Crossed Sword Icon", m_crossedSwordIcon);
		acquireResource("Arrow Icon", m_arrowIcon);
		acquireResource("Timer Icon", m_timerIcon);
		acquireResource("Kill Icon", m_killIcon);
		acquireResource("Map Icon", m_mapIcon);
		acquireResource("Player Icons", m_playerIcons);
		acquireResource("Plus Score Icon", m_plusScoreIcon);
		acquireResource("Minus Score Icon", m_minusScoreIcon);
		acquireResource("Pre Game Icon", m_preGameIcon);
		acquireResource("Main Menu Indicator", m_mainMenuIndicator);
		acquireResource("Options Indicator", m_optionsIndicator);

		//controller icons
		acquireResource("Start Icon", m_startIcon);
		acquireResource("B Icon", m_bIcon);
		acquireResource("A Icon", m_aIcon);
		acquireResource("Y Icon", m_yIcon);
		acquireResource("X Icon", m_xIcon);
		acquireResource("LT Icon", m_ltIcon);
		acquireResource("Dpad Icon", m_dpadIcon);
		acquireResource("Lanalog Icon", m_lanalogIcon);
		acquireResource("Draw Indicator", m_drawIndicator);
		acquireResource("Win Indicator", m_winIndicator);
		acquireResource("Lose Indicator", m_loseIndicator);

		//Load particle
		acquireResource("Particle", m_particle);

		//Load level textures
		acquireResource("Castle BG", m_castleBg);
		acquireResource("Castle CTF BG", m_castleCtfBg);
		acquireResource("windowTile", m_windowTile);
		acquireResource("stoneTile", m_stoneTile);
		acquireResource("torch", m_torch);
		acquireResource("torchLight", m_torchLight);
		acquireResource("Yellow Flag", m_yellowFlag);
		acquireResource("Blue Flag", m_blueFlag);
		acquireResource("Flag Base", m_flagBase);
		acquireResource("Capture Indicator", m_captureIndicator);
		acquireResource("Player Pos Indicator", m_playerPosIndicator);

		//Load player textures
		acquireResource("playerIdle", m_idlePlayer, false); //setting our animations to not smooth eliminates artefacts
		acquireResource("playerAttack", m_playerAttack, false);
		acquireResource("playerRun", m_playerRun, false);
		acquireResource("playerJump", m_playerJump, false);
		acquireResource("playerPickup", m_playerPickup, false);
		acquireResource("playerLight", m_playerLight);
		acquireResource("swordLight", m_swordLight);
		acquireResource("sword", m_sword, false);

		//Load our shaders
		acquireShader("recolourShader", m_recolourShaderPath);

		//Load Fonts
		acquireResource("oxinFont", m_oxinFont);
		acquireResource("arialFont", m_arialFont);
	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cout << e.what() << std::endl; //output error
	}
}

ResourceManager::~ResourceManager()
{
	//unload assets
}

//This method acquires our texture and then sets our texture smooth to true
void ResourceManager::acquireResource(std::string resourceId, thor::ResourceLoader<sf::Texture> textureLoader, bool isSmooth)
{
	m_textureHolder.acquire(resourceId, textureLoader);
	m_textureHolder[resourceId].setSmooth(isSmooth);
}

//This method acquires our fonts
void ResourceManager::acquireResource(std::string resourceId, thor::ResourceLoader<sf::Font> fontLoader)
{
	m_fontHolder.acquire(resourceId, fontLoader);
}

//loads in our shaders
void ResourceManager::acquireShader(std::string resourceId, std::string shaderPath)
{
	//adds a string with the key 'resourceId' with the path to the shader
	m_shaderHolder[resourceId] = shaderPath;
}

thor::ResourceHolder<sf::Texture, std::string>& ResourceManager::getTextureHolder()
{
	return m_textureHolder;
}

thor::ResourceHolder<sf::Font, std::string>& ResourceManager::getFontHolder()
{
	return m_fontHolder;
}

std::map<std::string, std::string>& ResourceManager::getShaderHolder()
{
	return m_shaderHolder;
}
