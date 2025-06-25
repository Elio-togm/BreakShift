#include "raylib.h"

// Function to draw text centered on the screen
void DrawTextCenterScreen(const char* text, const int screenWidth, const int screenHeight, float fontSize, Color color);

// Function to draw text using custom font centered on the screen
void DrawTextCenterScreenEx(Font font, const char* text, const int screenWidth, const int screenHeight, float fontSize, float spacing, Color color);

// Function to draw text using custom font centered on the screen with a rotation
void DrawTextCenterScreenPro(Font font, const char* text, Vector2 position, float rotation, float fontSize, float spacing, Color color);

// Function to draw text using the default font centered at a specific position with a given font size, spacing, and color
void DrawTextCentered(const char* text, Vector2 position, float fontSize, float spacing, Color color, int mode = 0);
/*
* mode: 0 - x-axis & y-axis (default), 1 - x-axis, 2 - y-axis
*/

// Function to draw text using the default font centered at a specific position with a given font size, spacing, color, and rotation.
void DrawTextCenteredPro(const char* text, Vector2 position, float rotation, float fontSize, float spacing, Color color, int mode = 0);

// Function to draw text using a custom font centered at a specific position with a given font size, spacing, color, and rotation.
void DrawTextCenteredEx(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color color, int mode = 0);

// Function to draw text using a custom font centered at a specific position with a given font size, spacing, color, and rotation.
void DrawTextCenteredExPro(Font font, const char* text, Vector2 position, float rotation, float fontSize, float spacing, Color color, int mode = 0);