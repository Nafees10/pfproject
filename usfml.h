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

/// Returns: true if an event has occurred
bool eventOccurred();

/// Waits for an event to occur
void eventWait();

#endif
