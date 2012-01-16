#ifndef _GAMEMENU_HPP_
#define _GAMEMENU_HPP_

#include <iostream>

// Should help somewhere.
enum MenuType {MENU_PAUSE, MENU_SPLASH, MENU_START, MENU_CREDITS, NO_MENU};

// SDL needed import #include

class GameMenu {
	// attributes and methods needed by SDL
	private :
		MenuType m_type;
		
	public :
		GameMenu(MenuType type = NO_MENU) :
			m_type(type)
		{
			switch(type) {
				case MENU_SPLASH :
					// do all that
					break;
				// @TODO configure each kind of game menu
				case MENU_PAUSE :
				case MENU_START :
				case MENU_CREDITS :
				default:
					break;
			}
		}
		
		GameMenu(const GameMenu & gameMenu) :
			m_type(gameMenu.m_type)
		{
		}
		
		~GameMenu() {
		}
		
		const unsigned int type() const {
			return m_type;
		}
		
		void exit() {
			// @TODO : save parameters if they aren't save on event (click or select)
			switch(m_type) {
				case MENU_SPLASH :
				case MENU_PAUSE :
				case MENU_START :
				case MENU_CREDITS :
				default :
					break;
			}
		}
		
		// where all the magic happens
		void show() const {
			
		}
};

#endif // _GAMEMENU_HPP_
