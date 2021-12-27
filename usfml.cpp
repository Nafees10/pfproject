#include <SFML/Graphics.hpp>
#include "usfml.h"

/// if everything has been initialised
bool _initialised = false;
/// SFML window
sf::RenderWindow *_window = nullptr;
/// clock
sf::Clock *_clock = nullptr;
/// sf event
sf::Event *_sfEvent = nullptr;
/// if an event is waiting in _sfEvent
bool _eventWaiting = false;
/// Textures
sf::Texture *_texture[MAX_OBJECTS] = {nullptr};
/// Sprites
sf::Sprite *_sprite[MAX_OBJECTS] = {nullptr};

bool usfmlInit(int width, int height, char *title){
	if (_initialised)
		return false;
	_initialised = true;
	_window = new sf::RenderWindow(sf::VideoMode(width, height), title,
							 sf::Style::Titlebar | sf::Style::Close);
	_sfEvent = new sf::Event();
	_clock = new sf::Clock();
	_eventWaiting = false;
	return true;
}

bool usfmlDestroy(){
	if (!_initialised)
		return false;
	delete _window;
	delete _sfEvent;
	delete _clock;
	_window = nullptr;
	_sfEvent = nullptr;
	_clock = nullptr;
	_initialised = false;
	_eventWaiting = false;
	return true;
}

bool windowHasFocus(){
	if (_initialised)
		return _window->hasFocus();
	return false;
}

bool windowIsOpen(){
	if (_initialised)
		return _window->isOpen();
	return false;
}

void windowSetVSync(bool val){
	if (_initialised)
		_window->setVerticalSyncEnabled(val);
}

int timeMsecs(){
	if (_initialised)
		return _clock->getElapsedTime().asMilliseconds();
	return -1;
}

void timerReset(){
	if (_initialised)
		_clock->restart();
}

bool eventOccurred(){
	if (!_initialised)
		return false;
	if (_eventWaiting)
		return true;
	_eventWaiting = _window->pollEvent(*_sfEvent);
	return _eventWaiting;
}

void eventWait(){
	if (_initialised && !_eventWaiting){
		_window->waitEvent(*_sfEvent);
		_eventWaiting = true;
	}
}

bool eventGet(Event &event){
	if (!eventOccurred())
		return false;
	if (_sfEvent->type == sf::Event::Closed){
		event.type = EventType::WindowCloseButtonPress;
	}else if (_sfEvent->type == sf::Event::MouseButtonPressed || _sfEvent->type == sf::Event::MouseButtonReleased){
		event.type = EventType::Mouse;
		event.mouse.x = _sfEvent->mouseButton.x;
		event.mouse.y = _sfEvent->mouseButton.y;
		if (_sfEvent->mouseButton.button == sf::Mouse::Button::Left)
			event.mouse.button = MouseButton::Left;
		else if (_sfEvent->mouseButton.button == sf::Mouse::Button::Right)
			event.mouse.button = MouseButton::Right;
		else if (_sfEvent->mouseButton.button == sf::Mouse::Button::Middle)
			event.mouse.button = MouseButton::Middle;
		event.mouse.pressed = _sfEvent->type == sf::Event::MouseButtonPressed;
	}else if (_sfEvent->type == sf::Event::MouseLeft || _sfEvent->type == sf::Event::MouseMoved){
		event.type = EventType::Mouse;
		event.mouse.pressed = false;
		if (_sfEvent->type == sf::Event::MouseMoved){
			event.mouse.x = _sfEvent->mouseButton.x;
			event.mouse.y = _sfEvent->mouseButton.y;
		}else{
			event.mouse.x = -1;
			event.mouse.y = -1;
		}
		event.mouse.button = MouseButton::None;
	}else if (_sfEvent->type == sf::Event::MouseWheelScrolled){
		event.type = EventType::Mouse;
		event.mouse.x = _sfEvent->mouseWheelScroll.x;
		event.mouse.y = _sfEvent->mouseWheelScroll.y;
		event.mouse.button = MouseButton::ScrollDown;
		if (_sfEvent->mouseWheelScroll.delta > 0)
			event.mouse.button = MouseButton::ScrollUp;
	}else if (_sfEvent->type == sf::Event::TextEntered){
		event.type = EventType::Keyboard;
		event.keyboard.pressed = true;
		event.keyboard.key = _sfEvent->text.unicode;
	}else if (_sfEvent->type == sf::Event::KeyPressed || _sfEvent->type == sf::Event::KeyReleased){
		event.type = EventType::Keyboard;
		event.keyboard.pressed = _sfEvent->type == sf::Event::KeyPressed;
		if (_sfEvent->key.code == sf::Keyboard::Escape)
			event.keyboard.key = SpecialKey::Escape;
		else if (_sfEvent->key.code == sf::Keyboard::LControl ||
				_sfEvent->key.code == sf::Keyboard::RControl)
			event.keyboard.key = SpecialKey::Ctrl;
		else if (_sfEvent->key.code == sf::Keyboard::LShift ||
				_sfEvent->key.code == sf::Keyboard::RShift)
			event.keyboard.key = SpecialKey::Shift;
		else if (_sfEvent->key.code == sf::Keyboard::LAlt ||
				_sfEvent->key.code == sf::Keyboard::RAlt)
			event.keyboard.key = SpecialKey::Alt;
		else if (_sfEvent->key.code == sf::Keyboard::Backspace)
			event.keyboard.key = SpecialKey::Backspace;
		else if (_sfEvent->key.code == sf::Keyboard::Tab)
			event.keyboard.key = SpecialKey::Tab;
		else if (_sfEvent->key.code == sf::Keyboard::PageUp)
			event.keyboard.key = SpecialKey::PgUp;
		else if (_sfEvent->key.code == sf::Keyboard::PageDown)
			event.keyboard.key = SpecialKey::PdDn;
		else if (_sfEvent->key.code == sf::Keyboard::Home)
			event.keyboard.key = SpecialKey::Home;
		else if (_sfEvent->key.code == sf::Keyboard::End)
			event.keyboard.key = SpecialKey::End;
		else if (_sfEvent->key.code == sf::Keyboard::Left)
			event.keyboard.key = SpecialKey::ArrowLeft;
		else if (_sfEvent->key.code == sf::Keyboard::Right)
			event.keyboard.key = SpecialKey::ArrowRight;
		else if (_sfEvent->key.code == sf::Keyboard::Up)
			event.keyboard.key = SpecialKey::ArrowUp;
		else if (_sfEvent->key.code == sf::Keyboard::Down)
			event.keyboard.key = SpecialKey::ArrowDown;
		else if (_sfEvent->key.code == sf::Keyboard::Enter)
			event.keyboard.key = SpecialKey::Enter;
		else if (_sfEvent->key.code >= sf::Keyboard::F1 &&
			_sfEvent->key.code <= sf::Keyboard::F12){
			event.keyboard.key = SpecialKey::F1 + (_sfEvent->key.code - sf::Keyboard::F1);
		}
	}
	_eventWaiting = false;
	return true;
}

void sleep(int msecs){
	sf::sleep(sf::Time(sf::milliseconds(msecs)));
}

void frameClear(unsigned int color = 0x000000){
	if (!_initialised)
		return;
	_window->clear(sf::Color(color));
}

void framePush(){
	_window->display();
}

int objectCreate(char* imagePath){
	// look for nullptr
	int index = 0;
	while (index < MAX_OBJECTS && _texture[index] != nullptr)
		index ++;
	if (index >= MAX_OBJECTS)
		return -1;
	_texture[index] = new sf::Texture();
	if (_texture[index]->loadFromFile(imagePath)){
		_sprite[index] = new sf::Sprite(*(_texture[index]));
		return index;
	}
	delete _texture[index];
	return -2;
}

bool objectExists(int index){
	return index >= 0 && index < MAX_OBJECTS && _sprite[index] != nullptr;
}

bool objectMove(int index, int x, int y){
	if (!objectExists(index))
		return false;
	_sprite[index]->move(x, y);
	return true;
}

bool objectDraw(int index){
	if (!_initialised || !objectExists(index))
		return false;
	_window->draw(*(_sprite[index]));
	return true;
}

bool objectDestroy(int index){
	if (!objectExists(index))
		return false;
	delete _sprite[index];
	delete _texture[index];
	_sprite[index] = nullptr;
	_texture[index] = nullptr;
	return true;
}
