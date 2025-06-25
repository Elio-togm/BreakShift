#include "text.hpp"

void DrawTextCenterScreen(const char* text, const int screenWidth, const int screenHeight, float fontSize, Color color) {
    Font defaultFont = GetFontDefault(); // Ensure the default font is loaded
    float spacing = fontSize / 10; // Calculate spacing based on font size
    DrawTextCenterScreenEx(defaultFont, text, screenWidth, screenHeight, fontSize, spacing, color);
}

void DrawTextCenterScreenEx(Font font, const char* text, const int screenWidth, const int screenHeight, float fontSize, float spacing, Color color) {
    Vector2 position = { (float)screenWidth, (float)screenHeight };
    float rotation = 0.0f; // No rotation
    // Draw the text at the calculated position
    DrawTextCenterScreenPro(font, text, position, rotation, fontSize, spacing, color);
}

void DrawTextCenterScreenPro(Font font, const char* text, Vector2 screenDimensions, float rotation, float fontSize, float spacing, Color color) {
    // Calculate the width and height of the text
    Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);
    float textWidth = textSize.x;
    float textHeight = textSize.y;
    // Calculate the position to center the text
    float x = (screenDimensions.x) / 2;
    float y = (screenDimensions.y) / 2;
    Vector2 position = { x, y };
    Vector2 origin = { textWidth / 2, textHeight / 2 }; // Center the origin
    // Draw the text at the calculated position
    DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, color);
}

void DrawTextCentered(const char* text, Vector2 position, float fontSize, float spacing, Color color, int mode) {
    // Draw the text at the calculated position
    DrawTextCenteredPro(text, position, 0.0f, fontSize, spacing, color, mode);
}

void DrawTextCenteredPro(const char* text, Vector2 position, float rotation, float fontSize, float spacing, Color color, int mode) {
    Font defaultFont = GetFontDefault(); // Use the default font
    DrawTextCenteredExPro(defaultFont, text, position, rotation, fontSize, spacing, color, mode);
}

void DrawTextCenteredEx(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color color, int mode) {
    DrawTextCenteredExPro(font, text, position, 0.0f, fontSize, spacing, color, mode);
}

void DrawTextCenteredExPro(Font font, const char* text, Vector2 position, float rotation, float fontSize, float spacing, Color color, int mode) {
    // Calculate the width and height of the text
    Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);
    float textWidth = textSize.x;
    float textHeight = textSize.y;
    Vector2 origin = { textWidth / 2, textHeight / 2 }; // Center the origin
    DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, color);
}