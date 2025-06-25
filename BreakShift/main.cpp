#include "raylib.h" // Include raylib header for graphics and window management
#include "text.hpp" // Include the text header for custom text functions

const int screenWidth = 800; // Width of the window
const int screenHeight = 600; // Height of the window

struct Paddle {
    Vector2 position; // Position of the paddle
    float width; // Width of the paddle
	float height; // Height of the paddle
};

struct Ball {
	Vector2 position; // Position of the ball
	Vector2 speed; // Speed of the ball
	float radius; // Radius of the ball
};

struct Brick {
	Rectangle rect; // Rectangle representing the brick
	Color color; // Color of the brick
	bool isActive; // Flag to check if the brick is active
};

struct GameState {
	Paddle player; // Player paddle
	Ball ball; // Ball in the game
	int score; // Player's score
	int numberOfBalls; // Number of balls remaining
	bool startGame; // Flag to check if the game has started
	bool lostBall; // Flag to check if a ball has been lost
	bool gameOver; // Flag to check if the game is over

	void ResetLife() { // Function to reset the ball
		ball.position = { static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f }; // Reset ball position to center
		ball.speed = { 0.0f, GetRandomValue(0, 1) ? -5.0f : 5.0f }; // Reset ball speed
		player.position = { static_cast<float>(screenWidth) / 2.0f - 50.0f, static_cast<float>(screenHeight) - 30.0f }; // Reset paddle position
		startGame = false; // Set start game flag to false
		lostBall = false; // Reset lost ball flag
	}
};

GameState UpdateBall(Ball& ball, Paddle& player, GameState gameState, int screenWidth, int screenHeight); // Function declaration for updating the ball

Rectangle UpdatePaddle(Paddle& player, Rectangle player_rect, int screenWidth); // Function declaration for updating the paddle

GameState CheckGameState(GameState& gameState, const int screenWidth, const int screenHeight); // Function declaration for checking the game state

void CheckBallBrickCollision(Ball &ball, GameState &gameState); // Function declaration for checking ball-brick collision

int CheckClearBricks(); // Function declaration for checking if all bricks are cleared

void SetupBricks(); // Function declaration for setting up the bricks

const int BRICK_ROWS = 16; // Number of rows of bricks
const int BRICK_COLUMNS = 8; // Number of columns of bricks

const float RATE_OF_CHANGE = 0.025f; // Rate of change for the ball speed

const int MOVE_SPEED = 12; // Speed at which the paddle moves

Brick bricks[BRICK_ROWS][BRICK_COLUMNS]; // Array to hold the bricks in the game

int main() {
		// Initialize the parameters for BreakShift

		InitWindow(screenWidth, screenHeight, "BreakShift"); // Create a window with the specified width, height, and title
		SetTargetFPS(60); // Set the target frames per second

		Font defaultFont = GetFontDefault(); // Load the default font

		Paddle player = { { screenWidth / 2 - 50, screenHeight - 30 }, 100, 20 }; // Initialize the player paddle
		Rectangle player_rect = { player.position.x, player.position.y, player.width, player.height }; // Create a rectangle for the paddle

		Ball ball = { { screenWidth / 2, screenHeight / 2 }, {0.0f, GetRandomValue(0, 1) ? -5.0f : 5.0f}, 10}; // Initialize the ball with position, speed, and radius

		SetupBricks(); // Set up the bricks in the game

		GameState gameState = {player, ball, 0, 3, false, false, false}; // Create a game state object to hold the game parameters

	// Start the game loop as long as the window is open and escape key is not pressed
    while (!WindowShouldClose()) {

		gameState.ball = ball; // Update the ball in the game state
		gameState.player = player; // Update the player paddle in the game state

		gameState = CheckGameState(gameState, screenWidth, screenHeight); // Check the game state

		// Update the game logic here
		ball = gameState.ball; // Update the ball from the game state

		// Update the ball position based on its speed
		if (gameState.startGame) {
			gameState = UpdateBall(ball, player, gameState, screenWidth, screenHeight);
		}
		ball = gameState.ball; // Update the ball from the game state

		CheckBallBrickCollision(ball, gameState);

		player = gameState.player; // Update the player paddle from the game state
		player_rect = UpdatePaddle(player, player_rect, screenWidth); // Update the paddle position based on user input

        // Draw the game frame
		if (!gameState.startGame and gameState.numberOfBalls > 0) {
			BeginDrawing();
				ClearBackground(BLACK);
				DrawRectangleRec(player_rect, RAYWHITE); // Draw the player paddle
				for (int row = 0; row < 16; row++) { // Initialize the bricks
					for (int col = 0; col < 8; col++) {
						if (bricks[row][col].isActive) {
							DrawRectangleRec(bricks[row][col].rect, bricks[row][col].color); // Draw each active brick
						}
					}
				}
				DrawTextCenterScreen("Use LEFT/RIGHT or A/D to move the paddle", screenWidth, screenHeight, 20, RAYWHITE); // Display instructions
				DrawTextCentered("Press SPACE to start the game", { screenWidth / 2, screenHeight / 2 + 30 }, 20, 2, RAYWHITE); // Display start message
				DrawText(TextFormat("Score: %i", gameState.score), 10, 10, 20, RAYWHITE); // Display the score
				DrawText(TextFormat("Balls remaining: %i", gameState.numberOfBalls), screenWidth - 200, 10, 20, RAYWHITE); // Display the number of balls remaining
			EndDrawing();
		}
		else if (gameState.numberOfBalls > 0) {
			BeginDrawing();
				ClearBackground(BLACK);
				DrawRectangleRec(player_rect, RAYWHITE); // Draw the player paddle
				DrawCircleV(ball.position, ball.radius, RAYWHITE); // Draw the ball
				for (int row = 0; row < 16; row++) { // Initialize the bricks
					for (int col = 0; col < 8; col++) {
						if (bricks[row][col].isActive) {
							DrawRectangleRec(bricks[row][col].rect, bricks[row][col].color); // Draw each active brick
						}
					}
				}
				DrawText(TextFormat("Score: %i", gameState.score), 10, 10, 20, RAYWHITE); // Display the score
				DrawText(TextFormat("Balls remaining: %i", gameState.numberOfBalls), screenWidth - 200, 10, 20, RAYWHITE); // Display the number of balls remaining
			EndDrawing();
		}
		// Check for game over condition
		if (gameState.gameOver) {
			ball.position = { screenWidth / 2, screenHeight / 2 }; // Reset the ball position
			ball.speed = { 0, 0 }; // Stop the ball
			gameState.ball = ball; // Update the ball in the game state
			BeginDrawing();
				ClearBackground(BLACK);
				DrawTextCenterScreen("Game Over!", screenWidth, screenHeight, 20, RAYWHITE); // Display game over message
				DrawTextCentered(TextFormat("Score: %i", gameState.score), { screenWidth / 2, screenHeight / 2 + 20}, 20, 2, RAYWHITE); // Display the score
			EndDrawing();
		}
    }

	CloseRaylibWindow(); // Close the window and unload resources
    return 0;
}

GameState UpdateBall(Ball &ball, Paddle &player, GameState gameState, int screenWidth, int screenHeight) {
	ball.position.x += ball.speed.x; // Update the ball's x position
	ball.position.y += ball.speed.y; // Update the ball's y position
	if (ball.position.x <= ball.radius or ball.position.x >= screenWidth - ball.radius // Check if the ball hits the left or right wall
		or (ball.position.x >= player.position.x - ball.radius and ball.position.x <= player.position.x + player.width + ball.radius and ball.position.y > player.position.y)) { // If the ball hits the left or right side of the paddle
		ball.speed.x *= -1; // Reverse the ball's x speed if it hits the left or right wall
		float ySpeedChange = GetRandomValue(0, 3) * RATE_OF_CHANGE; // Randomly change the y speed
		if (ball.speed.y < 0) {
			ySpeedChange *= -1; // Ensure the y speed change is negative if the ball is moving up
		}
		ball.speed.y += ySpeedChange; // Change the x speed slightly to make the game less predictable
	}
	if (ball.position.y > screenHeight - ball.radius) {
		gameState.lostBall = true; // Set the lost ball flag if the ball goes below the screen
	}
	if (ball.position.y < ball.radius or (ball.position.y > player.position.y - ball.radius
		and player.position.x <= ball.position.x and ball.position.x <= player.position.x + player.width)) {
		ball.speed.y *= -1; // Reverse the ball's y speed if it hits the top wall or the paddle
		float xSpeedChange = GetRandomValue(0, 3) * RATE_OF_CHANGE; // Randomly change the x speed
		if (ball.speed.x < 0) {
			xSpeedChange *= -1; // Ensure the y speed change is negative if the ball is moving up
		}
		ball.speed.x += xSpeedChange; // Change the x speed slightly to make the game less predictable
	}

	gameState.ball = ball; // Update the ball in the game state
	return gameState; // Return the updated game state
}

Rectangle UpdatePaddle(Paddle &player, Rectangle player_rect, int screenWidth) {
	// Update the game logic here
	if (IsKeyDown(KEY_LEFT) or IsKeyDown(KEY_A)) {
		player.position.x -= MOVE_SPEED; // Move the paddle left
	}
	if (IsKeyDown(KEY_RIGHT) or IsKeyDown(KEY_D)) {
		player.position.x += MOVE_SPEED; // Move the paddle right
	}
	if (player.position.x < 0) {
		player.position.x = 0; // Prevent the paddle from going off the left edge
	}
	if (player.position.x + player.width > screenWidth) {
		player.position.x = screenWidth - player.width; // Prevent the paddle from going off the right edge
	}
	Rectangle rect = { player.position.x, player.position.y, player.width, player.height }; // Create a rectangle for the paddle
	return rect; // Update the paddle rectangle
}

GameState CheckGameState(GameState &gameState, int screenWidth, int screenHeight) {
    // Check to see if a ball has been lost
    if (gameState.ball.position.y > static_cast<float>(screenHeight) - gameState.ball.radius) {
        gameState.lostBall = true; // Set the lost ball flag
        gameState.score -= 10; // Decrease the score when a ball is lost
    }

    // Check for game over condition
    if (gameState.lostBall) {
        gameState.numberOfBalls--; // Decrease the number of balls when a ball is lost
        if (gameState.numberOfBalls > 0) {
			gameState.ResetLife(); // Reset the ball and paddle positions
        }
        else {
            gameState.startGame = false;
            gameState.gameOver = true; // Stop the game if no balls are left
        }
    }

	// Check if all bricks are cleared
	if (CheckClearBricks()) {
		gameState.ResetLife(); // Reset the ball and paddle positions
		gameState.score += 100; // Increase the score when all bricks are cleared
		SetupBricks(); // Reset the bricks for a new game
	}

    if (IsKeyPressed(KEY_SPACE) && !gameState.gameOver) {
        gameState.startGame = true; // Start the game when space is pressed
    }
    return gameState; // Return the updated game state
}

void CheckBallBrickCollision(Ball &ball, GameState &gameState) {
	for (int row = 0; row < BRICK_ROWS; row++) {
		for (int col = 0; col < BRICK_COLUMNS; col++) {
			Brick& brick = bricks[row][col];

			if (brick.isActive && CheckCollisionCircleRec(ball.position, ball.radius, brick.rect)) {
				brick.isActive = false;

				if ((brick.rect.x > ball.position.x or brick.rect.x + brick.rect.width < ball.position.x) and (brick.rect.y < ball.position.y and brick.rect.y + brick.rect.height > ball.position.y)) {
					ball.speed.x *= -1; // Reverse the ball's x speed if it hits the left or right side of the brick
					float ySpeedChange = GetRandomValue(0, 5) * RATE_OF_CHANGE; // Randomly change the y speed
					if (ball.speed.y < 0) {
						ySpeedChange *= -1; // Ensure the y speed change is negative if the ball is moving up
					}
				}
				else {			// Reflect the ball — based on where the ball hit
					// For now, simply reverse vertical direction:
					ball.speed.y *= -1;
					float xSpeedChange = GetRandomValue(0, 5) * RATE_OF_CHANGE; // Randomly change the x speed
					if (ball.speed.x < 0) {
						xSpeedChange *= -1; // Ensure the x speed change is negative if the ball is moving left
					}
					ball.speed.x += xSpeedChange; // Change the x speed slightly to make the game less predictable
				}
				gameState.score += 10; // Increase the score when a brick is hit

				// Optional: add score, sound, etc.
				return; // Exit after first collision to avoid double collisions
			}
		}
	}
}

int CheckClearBricks() {
	for (int row = 0; row < BRICK_ROWS; row++) {
		for (int col = 0; col < BRICK_COLUMNS; col++) {
			if (bricks[row][col].isActive) {
				return 0; // Exit if any brick is active
			}
		}
	}
	// If all bricks are active, reset the game or increase difficulty
	return 1; // Return 1 if all bricks are inactive
}

void SetupBricks() {
	for (int row = 0; row < BRICK_ROWS; row++) { // Initialize the bricks
		for (int col = 0; col < BRICK_COLUMNS; col++) {
			bricks[row][col].rect = { static_cast<float>(row) * 50 + 5, static_cast<float>(col) * 20 + 50, 40, 15 }; // Set the rectangle for each brick
			bricks[row][col].color = (row % 2 == 0) ? RED : BLUE; // Alternate colors for the bricks
			bricks[row][col].isActive = true; // Set all bricks to active initially
		}
	}
}