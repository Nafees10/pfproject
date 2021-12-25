#include <SFML/Window.hpp>

sf::Window *_window;
bool _initialised = false;

sf::Event *_event;
bool _eventWaiting = false;

sf::Clock *_clock;

bool createWindow(int width, int height, char *title){
	if (_initialised)
		return false;
	_initialised = true;
	_window = new sf::Window(sf::VideoMode(width, height), title,
							 sf::Style::Titlebar | sf::Style::Close); // do not allow resizing
	_event = new sf::Event();
	_clock = new sf::Clock();
	_eventWaiting = false;
	return true;
}

bool destroyWindow(){
	if (!_initialised)
		return false;
	delete _window;
	delete _event;
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

bool eventOccurred(){
	if (!_initialised)
		return false;
	if (_eventWaiting)
		return true;
	_eventWaiting = _window->pollEvent(*_event);
	return _eventWaiting;
}

void eventWait(){
	if (_initialised && !_eventWaiting){
		_window->waitEvent(*_event);
		_eventWaiting = true;
	}
}

int timeMsecs(){
	if (_initialised)
		return _clock->getElapsedTime().asMilliseconds();
	return -1;
}
