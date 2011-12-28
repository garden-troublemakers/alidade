#ifndef _MENUS_HPP_
#define _MENUS_HPP_

// Should help somewhere.
#define MENU_PAUSE	 0
#define MENU_SPLASH	 1
#define MENU_START	 2
#define MENU_CREDITS 3
#define NO_MENU		 4

// SDL needed import #include

class GameMenu {
	// attributes and methods needed by SDL
	private :
		unsigned int m_type;
		
	public :
		GameMenu(const unsigned int & type = NO_MENU) : 
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
		
		~GameMenu();
		
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
