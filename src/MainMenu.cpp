#include "MainMenu.h"

MainMenu::MainMenu(std::string name, Audio& audio) :
	Screen(name),
	m_playGameBtn(sf::Vector2f(640, 144), "play game", "Crossed Sword Icon"),
	m_optionsBtn(sf::Vector2f(640, 288), "options", "Options Icon"),
	m_helpBtn(sf::Vector2f(640, 432), "help", "Help Icon"),
	m_exitBtn(sf::Vector2f(640, 576), "exit", "Exit Icon"),
	m_audioMainScreen(audio),
	m_btnIndex(0),
	m_btnToFadeIn(0),
	m_navigateLabel("navigation",sf::Vector2f(150, 683), resourceManager.getFontHolder()["oxinFont"]),
	m_selectLabel("select", sf::Vector2f(400,683), resourceManager.getFontHolder()["oxinFont"])
{
	setIconSprite(m_navigateIcon, resourceManager.getTextureHolder()["Lanalog Icon"], sf::Vector2f(70, 683));
	setIconSprite(m_selectIcon, resourceManager.getTextureHolder()["A Icon"], sf::Vector2f(345, 683));

	m_menuIcon.setTexture(resourceManager.getTextureHolder()["Main Menu Indicator"]);
	m_menuIcon.setOrigin(m_menuIcon.getLocalBounds().width / 2.0f, m_menuIcon.getLocalBounds().height / 2.0f);
	m_menuIcon.setPosition(640, 50);

	//adding our buttons to our buttons map
	m_buttons[m_playGameBtn.getName()] = &m_playGameBtn; 
	m_buttons[m_optionsBtn.getName()] = &m_optionsBtn;
	m_buttons[m_helpBtn.getName()] = &m_helpBtn;
	m_buttons[m_exitBtn.getName()] = &m_exitBtn;

	m_btnList.push_back(&m_playGameBtn);
	m_btnList.push_back(&m_optionsBtn);
	m_btnList.push_back(&m_helpBtn);
	m_btnList.push_back(&m_exitBtn);

	m_buttonNavigator[&m_playGameBtn] = "pre game";
	m_buttonNavigator[&m_optionsBtn] = "options";
	m_buttonNavigator[&m_helpBtn] = "help";
	m_buttonNavigator[&m_exitBtn] = "exit";



	//Set the alpha of all of our buttons to 0
	for (auto& btn : m_buttons)
		btn.second->setAlpha(0);

	//Set the first button to fade in
	m_btnList.at(m_btnToFadeIn)->setFadeIn(true);
}

void MainMenu::update()
{
	//loop through our buttons map and update each one
	for (auto key : m_buttons)
		key.second->update();

	if (m_btnToFadeIn < 3 && m_btnList.at(m_btnToFadeIn)->getAlpha() == 255)
	{
		m_btnToFadeIn++;
		m_btnList.at(m_btnToFadeIn)->setFadeIn(true);
	}
}

void MainMenu::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);

	window.draw(m_menuIcon);

	window.draw(m_selectIcon);
	window.draw(m_navigateIcon);
	m_navigateLabel.draw(window);
	m_selectLabel.draw(window);
	//loop through our buttons map and render each one
	for (auto key : m_buttons)
		key.second->render(window);
}

void MainMenu::start()
{
	m_active = true;
	m_audioMainScreen.updateMusic("Main");

	bool btnAlreadySelected = false;
	for (auto& btn : m_btnList)
	{
		if (btn->getSelected())
			btnAlreadySelected = true;
	}

	if (false == btnAlreadySelected)
	{
		//Selects the first button in our list as the currently selected button if no othe rbutton was previously selected
		selectButton(0);
	}
}

void MainMenu::end()
{
	m_active = false;
}

std::string MainMenu::handleInput(JoystickController& controller1, JoystickController& controller2)
{
	bool navigated = false;
	//assing the new index the same value as our current index
	auto newIndex = m_btnIndex;

	auto currentScreen = m_name; //the current screen we are on is m_name ie. "mainMenu"

	if (controller1.isButtonPressed("A"))
	{
		m_audioMainScreen.m_soundMap["SelectMenuItem"].play();
		currentScreen = m_buttonNavigator.at(m_btnList.at(m_btnIndex)); //assign the current screen the value of the button navigator with the key of the button
	}
	if (controller1.isButtonPressed("LeftThumbStickUp") || controller1.isButtonPressed("DpadUp"))
	{
		m_audioMainScreen.m_soundMap["MoveMenu"].play();
		navigated = true;
		newIndex--;
	}
	if (controller1.isButtonPressed("LeftThumbStickDown") || controller1.isButtonPressed("DpadDown"))
	{
		m_audioMainScreen.m_soundMap["MoveMenu"].play();
		navigated = true;
		newIndex++;
	}

	//if we have navigated through the menu then changed buttons
	if (navigated)
	{
		//checking if our newIndex has gone out of bounds
		if (newIndex > 3)
			newIndex = 0;
		else if (newIndex < 0)
			newIndex = 3;

		selectButton(newIndex); //focus our button at index: newIndex
	}


	return currentScreen;
}

void MainMenu::selectButton(int newIndex)
{
	//if our new index is out of range then output an error message
	if (newIndex < 0 || newIndex > 3)
	{
		std::cout << newIndex + " is not within range of the vector: m_btnList" << std::endl;
	}
	else
	{
		m_btnList.at(m_btnIndex)->deSelect(); //deselect the current button

		m_btnIndex = newIndex; //reassign the button index to the new index

		m_btnList.at(m_btnIndex)->select(); //select the button at the new index
	}
}

void MainMenu::setIconSprite(sf::Sprite & sprite, sf::Texture & texture, sf::Vector2f position)
{
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2.0f);
	sprite.setPosition(position);
}

std::string MainMenu::getName()
{
	return m_name;
}