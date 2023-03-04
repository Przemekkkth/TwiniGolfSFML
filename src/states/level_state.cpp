#include "level_state.h"
#include "game_state.h"
#include "../utils/resource_holder.h"
#include "../GUI/button.h"
#include <SFML/Graphics/RenderWindow.hpp>

LevelState::LevelState(StateStack &stack, Context context)
    : State(stack, context)
{
    sf::Texture& texture = context.textures->get(Textures::Title);
    mTitleStringSprite.setTexture(texture);
    mTitleStringSprite.setPosition(30, 30);

    //0row
    auto level0Btn = std::make_shared<GUI::Button>(context);
    level0Btn->setPosition(13, 200);
    level0Btn->setText("Level 0");
    level0Btn->setCallback([this] ()
    {
        GameState::choosenLevel = 0;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto level1Btn = std::make_shared<GUI::Button>(context);
    level1Btn->setPosition(226, 200);
    level1Btn->setText("Level 1");
    level1Btn->setCallback([this] ()
    {
        GameState::choosenLevel = 1;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto level2Btn = std::make_shared<GUI::Button>(context);
    level2Btn->setPosition(439, 200);
    level2Btn->setText("Level 2");
    level2Btn->setCallback([this] ()
    {
        GameState::choosenLevel = 2;
        requestStackPop();
        requestStackPush(States::Game);
    });
//1row
    auto level3Btn = std::make_shared<GUI::Button>(context);
    level3Btn->setPosition(13, 275);
    level3Btn->setText("Level 3");
    level3Btn->setCallback([this] ()
    {
        GameState::choosenLevel = 3;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto level4Btn = std::make_shared<GUI::Button>(context);
    level4Btn->setPosition(226, 275);
    level4Btn->setText("Level 4");
    level4Btn->setCallback([this] ()
    {
        GameState::choosenLevel = 4;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto level5Btn = std::make_shared<GUI::Button>(context);
    level5Btn->setPosition(439, 275);
    level5Btn->setText("Level 5");
    level5Btn->setCallback([this] ()
    {
        GameState::choosenLevel = 5;
        requestStackPop();
        requestStackPush(States::Game);
    });
//2row
    auto level6Btn = std::make_shared<GUI::Button>(context);
    level6Btn->setPosition(13, 350);
    level6Btn->setText("Level 6");
    level6Btn->setCallback([this] ()
    {
        GameState::choosenLevel = 6;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto level7Btn = std::make_shared<GUI::Button>(context);
    level7Btn->setPosition(226, 350);
    level7Btn->setText("Level 7");
    level7Btn->setCallback([this] ()
    {
        GameState::choosenLevel = 7;
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto level8Btn = std::make_shared<GUI::Button>(context);
    level8Btn->setPosition(439, 350);
    level8Btn->setText("Level 8");
    level8Btn->setCallback([this] ()
    {
        GameState::choosenLevel = 8;
        requestStackPop();
        requestStackPush(States::Game);
    });
//4row


    auto menuBtn = std::make_shared<GUI::Button>(context);
    menuBtn->setPosition(439, 425);
    menuBtn->setText("Menu");
    menuBtn->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Menu);
    });

    mGUIContainer.pack(level0Btn);
    mGUIContainer.pack(level1Btn);
    mGUIContainer.pack(level2Btn);
    mGUIContainer.pack(level3Btn);
    mGUIContainer.pack(level4Btn);
    mGUIContainer.pack(level5Btn);
    mGUIContainer.pack(level6Btn);
    mGUIContainer.pack(level7Btn);
    mGUIContainer.pack(level8Btn);
    mGUIContainer.pack(menuBtn);
}

void LevelState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(mTitleStringSprite);
    window.draw(mGUIContainer);
}

bool LevelState::update(sf::Time dt)
{
    return true;
}

bool LevelState::handleEvent(const sf::Event &event)
{
    mGUIContainer.handleEvent(event);
    return true;
}
