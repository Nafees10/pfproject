#ifndef MICROSFML_H
#define MICROSFML_H

#define MAX_OBJECTS 256

/// Creates a window of width x height size, with title
///
/// Returns: true if done, false if already created
bool usfmlInit(int width, int height, char *title);

/// Destroys the created window
///
/// Returns: true if done, false if window was never created
bool usfmlDestroy();

/// Returns: true if window has focus
bool windowHasFocus();

/// Returns: true if window is open (not closed)
bool windowIsOpen();

/// sets VSync
void windowSetVSync(bool val);

/// Returns: number of milliseconds since creation of window, or timerReset()
int timerMsecs();

/// Resets timer
void timerReset();

/// Returns: true if an event has occurred
bool eventOccurred();

/// Waits for an event to occur
void eventWait();

/// Special keyboard keys
enum SpecialKey : char{
	Escape,
	Ctrl,
	Shift,
	Alt,
	Backspace,
	Tab,
	PgUp,
	PdDn,
	Home,
	End,
	ArrowLeft,
	ArrowRight,
	ArrowUp,
	ArrowDown,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	Enter,
};
/// Keyboard event
struct KeyboardEvent{
	/// if it was pressed (true), or released (false)
	bool pressed;
	/// if it is special key (`SpecialKey`)
	bool isSpecial;
	/// key
	char key;
};

/// Mouse buttons
enum MouseButton : char{
	/// Left button
	Left = 'L',
	/// Right button
	Right = 'R',
	/// Middle button
	Middle = 'M',
	/// Scroll up
	ScrollUp = 'U',
	/// Scroll down
	ScrollDown = 'D',
	/// no button, just hover
	None = '\0',
};
/// MouseEvent
struct MouseEvent{
	/// what button was pressed/released
	MouseButton button;
	/// if it was pressed (true) or released (false). Undefined in case of button.None, or Scroll wheel
	bool pressed;
	/// X and Y position of mouse. -1 if mouse outside window
	int x, y;
};

/// Event type
enum EventType{
	Unknown,
	WindowCloseButtonPress,
	Keyboard,
	Mouse,
};

/// Event
struct Event{
	/// type of event
	EventType type;
	union{
		/// mouse event
		MouseEvent mouse;
		/// keyboard event
		KeyboardEvent keyboard;
	};
};

/// Gets event.
///
/// Returns: true if a event was returned, false if no
bool eventGet(Event &event);

/// Sleep for milliseconds
void sleep(int msecs);

/// Clears window
void frameClear(unsigned int color = 0x000000);

/// display frame
void framePush();

/// Loads a texture
///
/// Returns: teture index, or -1 if maximum textures loaded, or -2 if failed.
int objectLoadTexture(char* imagePath);

/// Creates an object, from texture
///
/// Returns: object ID (0 - 255), or -1 if max objects reached
int objectCreate(int textureIndex);

/// sets a texture for a object
///
/// Returns: true if done, false if index out of bounds or no exist
bool objectSetTexture(int index, int textureIndex);

/// Returns: true if an object with object id = index exists
bool objectExists(int index);

/// Moves an object
///
/// Returns: true if done, false if object doesnt exist
bool objectMove(int index, int x, int y);

/// Draws the object
///
/// Returns: true if done, false if not
bool objectDraw(int index);

/// Deletes an object
///
/// Returns: true if destroyed, false if doesnt exist
bool objectDestroy(int index);

#endif
