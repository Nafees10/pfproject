#ifndef MICROSFML_H
#define MICROSFML_H

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

/// Clears window
void frameClear();

/// display frame
void framePush();



#endif
