#include <SFML/Window.hpp>
#include <iostream>
#include "usfml.h"

/// if everything has been initialised
bool _initialised = false;
/// SFML window
sf::Window *_window = nullptr;
/// clock
sf::Clock *_clock = nullptr;
/// sf event
sf::Event *_sfEvent = nullptr;
/// if an event is waiting in _sfEvent
bool _eventWaiting = false;

bool createWindow(int width, int height, char *title){
	if (_initialised)
		return false;
	_initialised = true;
	_window = new sf::Window(sf::VideoMode(width, height), title,
							 sf::Style::Titlebar | sf::Style::Close); // do not allow resizing
	_sfEvent = new sf::Event();
	_clock = new sf::Clock();
	_eventWaiting = false;
	return true;
}

bool destroyWindow(){
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

bool eventGet(Event *event){
	if (!eventOccurred())
		return false;
	if (_sfEvent->type == sf::Event::Closed){
		event->type = EventType::WindowCloseButtonPress;
	}else if (_sfEvent->type == sf::Event::MouseButtonPressed || _sfEvent->type == sf::Event::MouseButtonReleased){
		event->type = EventType::Mouse;
		event->mouse.x = _sfEvent->mouseButton.x;
		event->mouse.y = _sfEvent->mouseButton.y;
		if (_sfEvent->mouseButton.button == sf::Mouse::Button::Left)
			event->mouse.button = MouseButton::Left;
		else if (_sfEvent->mouseButton.button == sf::Mouse::Button::Right)
			event->mouse.button = MouseButton::Right;
		else if (_sfEvent->mouseButton.button == sf::Mouse::Button::Middle)
			event->mouse.button = MouseButton::Middle;
		event->mouse.pressed = _sfEvent->type == sf::Event::MouseButtonPressed;
	}else if (_sfEvent->type == sf::Event::MouseLeft || _sfEvent->type == sf::Event::MouseMoved){
		event->type = EventType::Mouse;
		if (_sfEvent->type == sf::Event::MouseMoved){
			event->mouse.x = _sfEvent->mouseButton.x;
			event->mouse.y = _sfEvent->mouseButton.y;
		}else{
			event->mouse.x = -1;
			event->mouse.y = -1;
		}
		event->mouse.button = MouseButton::None;
	}else if (_sfEvent->type == sf::Event::MouseWheelScrolled){
		event->type = EventType::Mouse;
		event->mouse.x = _sfEvent->mouseWheelScroll.x;
		event->mouse.y = _sfEvent->mouseWheelScroll.y;
		event->mouse.button = MouseButton::ScrollDown;
		if (_sfEvent->mouseWheelScroll.delta > 0)
			event->mouse.button = MouseButton::ScrollUp;
	}else if (_sfEvent->type == sf::Event::TextEntered){
		event->type = EventType::Keyboard;
		event->keyboard.pressed = true;
		event->keyboard.key = _sfEvent->text.unicode;
	}else if (_sfEvent->type == sf::Event::KeyPressed || _sfEvent->type == sf::Event::KeyReleased){
		event->type = EventType::Keyboard;
		event->keyboard.pressed = _sfEvent->type == sf::Event::KeyPressed;
		if (_sfEvent->key.code == sf::Keyboard::Escape)
			event->keyboard.spKey = SpecialKeys::Escape;
		else if (_sfEvent->key.code == sf::Keyboard::LControl ||
				_sfEvent->key.code == sf::Keyboard::RControl)
			event->keyboard.spKey = SpecialKeys::Ctrl;
		else if (_sfEvent->key.code == sf::Keyboard::LShift ||
				_sfEvent->key.code == sf::Keyboard::RShift)
			event->keyboard.spKey = SpecialKeys::Shift;
		else if (_sfEvent->key.code == sf::Keyboard::LAlt ||
				_sfEvent->key.code == sf::Keyboard::RAlt)
			event->keyboard.spKey = SpecialKeys::Alt;
		else if (_sfEvent->key.code == sf::Keyboard::Backspace)
			event->keyboard.spKey = SpecialKeys::Backspace;
		else if (_sfEvent->key.code == sf::Keyboard::Tab)
			event->keyboard.spKey = SpecialKeys::Tab;
		else if (_sfEvent->key.code == sf::Keyboard::PageUp)
			event->keyboard.spKey = SpecialKeys::PgUp;
		else if (_sfEvent->key.code == sf::Keyboard::PageDown)
			event->keyboard.spKey = SpecialKeys::PdDn;
		else if (_sfEvent->key.code == sf::Keyboard::Home)
			event->keyboard.spKey = SpecialKeys::Home;
		else if (_sfEvent->key.code == sf::Keyboard::End)
			event->keyboard.spKey = SpecialKeys::End;
		else if (_sfEvent->key.code == sf::Keyboard::Left)
			event->keyboard.spKey = SpecialKeys::ArrowLeft;
		else if (_sfEvent->key.code == sf::Keyboard::Right)
			event->keyboard.spKey = SpecialKeys::ArrowRight;
		else if (_sfEvent->key.code == sf::Keyboard::Up)
			event->keyboard.spKey = SpecialKeys::ArrowUp;
		else if (_sfEvent->key.code == sf::Keyboard::Down)
			event->keyboard.spKey = SpecialKeys::ArrowDown;
		else if (_sfEvent->key.code == sf::Keyboard::Enter)
			event->keyboard.spKey = SpecialKeys::Enter;
		else if (_sfEvent->key.code == sf::Keyboard::F1)
			event->keyboard.spKey = SpecialKeys::F1;
		else if (_sfEvent->key.code == sf::Keyboard::F2)
			event->keyboard.spKey = SpecialKeys::F2;
		else if (_sfEvent->key.code == sf::Keyboard::F3)
			event->keyboard.spKey = SpecialKeys::F3;
		else if (_sfEvent->key.code == sf::Keyboard::F4)
			event->keyboard.spKey = SpecialKeys::F4;
		else if (_sfEvent->key.code == sf::Keyboard::F5)
			event->keyboard.spKey = SpecialKeys::F5;
		else if (_sfEvent->key.code == sf::Keyboard::F6)
			event->keyboard.spKey = SpecialKeys::F6;
		else if (_sfEvent->key.code == sf::Keyboard::F7)
			event->keyboard.spKey = SpecialKeys::F7;
		else if (_sfEvent->key.code == sf::Keyboard::F8)
			event->keyboard.spKey = SpecialKeys::F8;
		else if (_sfEvent->key.code == sf::Keyboard::F9)
			event->keyboard.spKey = SpecialKeys::F9;
		else if (_sfEvent->key.code == sf::Keyboard::F10)
			event->keyboard.spKey = SpecialKeys::F10;
		else if (_sfEvent->key.code == sf::Keyboard::F11)
			event->keyboard.spKey = SpecialKeys::F11;
		else if (_sfEvent->key.code == sf::Keyboard::F12)
			event->keyboard.spKey = SpecialKeys::F12;
	}
	_eventWaiting = false;
	return true;
}
