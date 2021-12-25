#ifndef USFML_H
#define USFML_H

/// Creates a window of width x height size, with title
///
/// Returns: true if done, false if already created
bool createWindow(int width, int height, char *title);

/// Destroys the created window
///
/// Returns: true if done, false if window was never created
bool destroyWindow();

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
enum SpecialKeys : int{
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
	/// if it was a character or a special key
	bool isSpecial;
	union{
		/// character key
		char key;
		/// special key
		SpecialKeys spKey;
	};
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
	ScrollUp,
	/// Scroll down
	ScrollDown,
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


#endif
