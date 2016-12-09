#pragma once
#include "GameClass.h"

GameClass::GameClass()
{

}

bool GameClass::Init()
{
	std::srand(static_cast<unsigned int>(std::time(static_cast<std::time_t>(0)))); // Seed random
	frameRate = 60; // Set frame rate
	prevFrameRate = 60; // Set previous frame rate
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Brick Breaker (Thats probably copyrighted)!"); // Create the render window


	frameCounter = 0; // Create a frame counter

	if (!myFont.loadFromFile("Resources\\arial.ttf"))
		return false;

	framesText.setFont(myFont);
	framesText.setScale(sf::Vector2f(0.4f, 0.4f));
	framesText.setPosition(WIDTH - 150.0f, 10.0f);
	framesText.setFillColor(sf::Color::White); // Set the fps text properties

	clock.restart();
	prevElapsedTime = clock.getElapsedTime(); // Start the clock to keep time
	roundClock.restart();
	updateText.SetFont(myFont); // Set its font

    mouse = {};
    displayIntro = true; // Flag to display intro only once

    gameState = INTRO;
    prevGameState = LOST;

	leftKeyDown = rightKeyDown = false;

	lives = 2;

    return true;
}

void GameClass::Run()
{
	//DEBUG: remove me
	bool autoPlay = false;
	bool retryFlag = false;
    while (window.isOpen()) // Start the window loop
    {
        // Parse and handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Close();
            if (event.type == sf::Event::MouseButtonPressed) {
                switch (event.mouseButton.button) {
                case sf::Mouse::Left: // If left click create a shock wave to the balls around
					
                    break;
                case sf::Mouse::Right: // If right mouse button turn on a point gravity source at the mouse
                    
                    break;
                }
            }
            else if (event.type == sf::Event::MouseMoved) {
                mouse.x = event.mouseMove.x;
                mouse.y = event.mouseMove.y; // Record mouse position when moved
                //updateText.Fade("New pos: " + std::to_string(mouse.x) + ", " + std::to_string(mouse.y), sf::seconds(1.0f));
            }
            else if (event.type == sf::Event::MouseLeft) {
                window.setMouseCursorVisible(true);
            }
            else if (event.type == sf::Event::MouseEntered) {
                window.setMouseCursorVisible(false);
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::O:  // Decrease max frame rate
					break;
                case sf::Keyboard::P: // Increase max frame rate
                    break;
				case sf::Keyboard::R:
					retryFlag = true;
					break;
                case sf::Keyboard::Space: // Pause the program
                    if (frameRate) {
                        prevFrameRate = frameRate;
                        frameRate = 0;
                    }
                    else {
                        frameRate = prevFrameRate;
                    } // Store framerate
                    updateText.Fade("unpaused", sf::seconds(2.0f));
                    break;
                case sf::Keyboard::A: { // Add a new ball
					// DEBUG: remove me
					autoPlay = !autoPlay;
					break; 
                }
                case sf::Keyboard::S: // Remove a ball
                    
                    break;
                case sf::Keyboard::Up: // Add to the global gravity in the negative y direction
                    
                    break;
                case sf::Keyboard::Down: // Increase the global gravity in the positive y direction
                    
                    break;
                case sf::Keyboard::Left: // Increase the global gravity in the (+) x direction
					//paddle.SetSpeed(4.0);
					//paddle.SetDirection(sf::Vector2f(-1.0f, 0.0f));
					//std::cout << "LEFT KEY DOWN" << std::endl;
					leftKeyDown = true;
					break;
                case sf::Keyboard::Right: // Increase the global gravity in the (-) x direction
					//paddle.SetSpeed(4.0);
					//paddle.SetDirection(sf::Vector2f(1.0f, 0.0f));
					rightKeyDown = true;
					break;
                case sf::Keyboard::D: // Decrease the global air friction
                    
                    
                    break;
                case sf::Keyboard::F: // Incrase the global air friction
                    
                    break;
                }
			}
			// This is to avoid the pause when a key is held down for example when a is held down one keypress is sent
			// Then after specified seconds (depends on settings and OS) a repetition of keypress events is set
			else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
				case sf::Keyboard::Left:
					leftKeyDown = false;
					break;
				case sf::Keyboard::Right:
					rightKeyDown = false;
					break;
				}
			}
        }
		if (leftKeyDown) {
			sf::Vector2f velocity = paddle.GetSpeed() * paddle.GetDirection();
			if (hf::Mag(velocity) < 30.0)
				velocity.x -= 0.0005;
			paddle.SetDirection(hf::Normalize(velocity));
			paddle.SetSpeed(hf::Mag(velocity));
		}
		else if (rightKeyDown) {
			sf::Vector2f velocity = paddle.GetSpeed() * paddle.GetDirection();
			if (hf::Mag(velocity) < 30.0) 
				velocity.x += 0.0005;
			paddle.SetDirection(hf::Normalize(velocity));
			paddle.SetSpeed(hf::Mag(velocity));
		}
        sf::Time elapsedTime = clock.getElapsedTime(); // Get time elapsed
        if (elapsedTime.asSeconds() - prevElapsedTime.asSeconds() > 1.0f / static_cast<double>(frameRate)) { // If time elapsed is more than the set time per frame
	        // Play frame
            // Begin drawing loop
            window.clear();

			switch (gameState) {
			case INTRO:
				if (gameState != prevGameState) {
					// Do once:
					updateText.Fade("Welcome to breakout!", sf::seconds(2));
					prevGameState = INTRO;
				}
				else if (updateText.GetText().getFillColor().a < 10) {
					gameState = INIT_ROUND;
				}
				round = 1;
				lives = 2;
				break;
			case INIT_ROUND:
				if (gameState != prevGameState) {
					// Do once:
					prevGameState = INIT_ROUND;
					updateText.Fade("Welcome to round: " + std::to_string(round) + ", extra  lives: " + std::to_string(lives), sf::seconds(4));
					paddle.Reset();
					balls.clear();
					Ball ball;
					balls.push_back(ball);
					balls.at(0).Reset();
					balls.at(0).Freeze();
					bricks.clear();
					powerUps.clear();
					Brick testBrick;
					sf::Vector2f brickDim = testBrick.GetDimensions();
					double numRows = 2 + round;
					double numCols = 7;
					double rowSpacing = 7.0;
					double colSpacing = 7.0;
					switch (round) {
					case 1:
					case 2:
					case 3:
					case 4:
						numRows = 2 + round;
						numCols = 7;
						rowSpacing = 7.0;
						colSpacing = 7.0;
						for (int i = 0; i < numRows; i++) {
							for (int j = 0; j < numCols - i; j++) {
								sf::Vector2f pos;
								double totalSpace = (numCols - i) * (brickDim.x + colSpacing);
								double startMap = (WIDTH - totalSpace) / 2.0;
								double endMap = startMap + totalSpace - (brickDim.x + colSpacing);
								pos.x = hf::Map(0, numCols - i - 1, startMap, endMap, j);
								pos.y = (40.0 * round) + i * brickDim.y + rowSpacing;
								Brick brick(pos, numRows - i);
								bricks.push_back(brick);
							}
						}
						break;
					case 5:
					case 6:
					case 7:
					case 8:
						numRows = 1 + round % 5;
						numCols = 7;
						rowSpacing = 7.0;
						colSpacing = 7.0;
						for (int i = 0; i < numRows; i++) {
							for (int j = 0; j < numCols; j++) {
								sf::Vector2f pos;
								double totalSpace = (numCols) * (brickDim.x + colSpacing);
								double startMap = (WIDTH - totalSpace) / 2.0;
								double endMap = startMap + totalSpace - (brickDim.x + colSpacing);
								pos.x = hf::Map(0, numCols - 1, startMap, endMap, j);
								pos.y = (40.0 * (round % 5 + 1)) + i * brickDim.y + rowSpacing;
								Brick brick(pos, numRows - i);
								bricks.push_back(brick);
							}
						}
						break;
					}
				}
				else if (updateText.GetText().getFillColor().a < 10) {
					gameState = PLAYING;
				}
				balls.at(0).OnFrame(&window);
				paddle.OnFrame(&window);
				for (int i = 0; i < bricks.size(); i++) {
					bricks.at(i).OnFrame(&window);
				}
				break;
			case RESET_BALL:
				
				if (gameState != prevGameState) {
					// Do once:
					prevGameState = RESET_BALL;
					updateText.Fade("extra lives: " + std::to_string(lives), sf::seconds(4));
					paddle.Reset();
					balls.clear();
					Ball ball;
					balls.push_back(ball);
					balls.at(0).Reset();
					balls.at(0).Freeze();
					powerUps.clear();
				}
				else if (updateText.GetText().getFillColor().a < 10) {
					gameState = PLAYING;
				}
				balls.at(0).OnFrame(&window);
				paddle.OnFrame(&window);
				for (int i = 0; i < bricks.size(); i++) {
					bricks.at(i).OnFrame(&window);
				}
				break;
			case PLAYING:
				// DEBUG: remove me
				if (autoPlay) {
					if (balls.size()) {
						sf::Vector2f pos = balls.at(0).GetPosition();
						sf::Vector2f paddlePos = paddle.GetPosition();
						if (pos.x + (balls.at(0).GetDimensions().x / 2.0) < paddlePos.x + (paddle.GetDimensions().x / 2.0)) {
							sf::Vector2f velocity = paddle.GetSpeed() * paddle.GetDirection();
							if (hf::Mag(velocity) < 30.0) {
								if (std::abs(pos.x + (balls.at(0).GetDimensions().x / 2.0) - (paddlePos.x + (paddle.GetDimensions().x / 2.0))) > 120) {
									velocity.x -= 0.34;
								}
								else {
									velocity.x -= 0.128;
								}
							}
							paddle.SetDirection(hf::Normalize(velocity));
							paddle.SetSpeed(hf::Mag(velocity));
						}
						else {
							sf::Vector2f velocity = paddle.GetSpeed() * paddle.GetDirection();
							if (hf::Mag(velocity) < 30.0) {
								if (std::abs(pos.x + (balls.at(0).GetDimensions().x / 2.0) - (paddlePos.x + (paddle.GetDimensions().x / 2.0))) > 120) {
									velocity.x += 0.34;
								}
								else {
									velocity.x += 0.128;
								}
							}
							paddle.SetDirection(hf::Normalize(velocity));
							paddle.SetSpeed(hf::Mag(velocity));
						}
					}

				}
				if (gameState != prevGameState) {
					// Do once: 
					balls.at(0).UnFreeze();
					prevGameState = PLAYING;
				}
				for (int i = 0; i < balls.size(); i++) {
					if (balls.at(i).Loss()) {
						balls.erase(balls.begin() + i);
					}
				}
				if (!balls.size()) {
					if (lives) {
						lives--;
						gameState = RESET_BALL;
					}
					else {
						gameState = LOST;
					}
				}
				for (int i = 0; i < balls.size(); i++) {
					paddle.BallCollision(&balls.at(i));
					balls.at(i).OnFrame(&window);
					for (int j = 0; j < balls.size(); j++) {
						if (j != i) {
							balls.at(i).BodyCollisions(&balls.at(j));
						}
					}
				}
				for (int i = 0; i < bricks.size(); i++) {
					bricks.at(i).OnFrame(&window);
					for (int j = 0; j < balls.size(); j++) {
						bricks.at(i).BallCollision(&balls.at(j));
					}
					if (bricks.at(i).IsBroken()) {
						if (!(rand() % 4)) {
							sf::Vector2f pos;
							PowerUp tempPowerUp;
							pos = bricks.at(i).GetPosition();
							sf::Vector2f brickDimensions = bricks.at(i).GetDimensions();
							sf::Vector2f powerUpDimensions = tempPowerUp.GetDimensions();
							pos.x = pos.x + brickDimensions.x / 2.0 - powerUpDimensions.x / 2.0;
							pos.y = pos.y + bricks.at(i).GetDimensions().y + 1;
							tempPowerUp.SetPosition(pos);
							powerUps.push_back(tempPowerUp); 
						}
						bricks.erase(bricks.begin() + i);
					}
				}
				paddle.OnFrame(&window);
				paddle.WallCollision();
				for (int i = 0; i < powerUps.size(); i++) {
					if (powerUps.at(i).Loss()) {
						powerUps.erase(powerUps.begin() + i);
					}
				}
				for (int i = 0; i < powerUps.size(); i++) {
					if (paddle.PowerUpCollision(&powerUps.at(i))) {
						switch (powerUps.at(i).GetPowerUpType()) {
						case PowerUp::EXTRA_LIFE:
							lives++;
							updateText.Fade("Extra life! extra lives: " + std::to_string(lives), sf::seconds(2.0f));
							break;
						case PowerUp::LARGER_PADDLE:
							updateText.Fade("Large paddle!", sf::seconds(2.0f));
							paddle.LargerPaddle();
							break;
						case PowerUp::NEW_BALL:
							updateText.Fade("New ball!", sf::seconds(2.0f));
							Ball tempBall;
							sf::Vector2f pos;
							pos.x = paddle.GetPosition().x + paddle.GetDimensions().x / 2.0 - tempBall.GetDimensions().x / 2.0;
							pos.y = paddle.GetPosition().y - tempBall.GetDimensions().y - 1;
							tempBall.SetInitialPosition(pos);
							tempBall.SetDirection(sf::Vector2f(cos(-PI / 2.0), sin(-PI / 2.0)));
							balls.push_back(tempBall);
							break;
						}
						powerUps.erase(powerUps.begin() + i);
					}
				}
				for (int i = 0; i < powerUps.size(); i++) {
					for (int j = 0; j < balls.size(); j++) {
						powerUps.at(i).BodyCollisions(&balls.at(j));
					}
					for (int j = 0; j < bricks.size(); j++) {
						bricks.at(j).PowerUpCollision(&powerUps.at(i));
					}
					for (int j = 0; j < powerUps.size(); j++) {
						if (i != j) {
							powerUps.at(i).BodyCollisions(&powerUps.at(j));
						}
					}
					powerUps.at(i).OnFrame(&window);
				}

				if (!bricks.size()) {
					round++;
					if (round == 9) {
						gameState = WON;
					}
					gameState = INIT_ROUND;
				}                

                break;
            case LOST:
                if (prevGameState != gameState) {
                    // Do once:
                    prevGameState = LOST;
					retryFlag = false;
					updateText.Fade("Sorry you lost! Press R to retry.", sf::seconds(7));
                }
				else if (updateText.GetText().getFillColor().a < 10) {
					Close();
				}

				if (retryFlag) {
					gameState = INTRO;
					retryFlag = false;
				}

                break;
            case WON:
                if (prevGameState != gameState) {
                    // Do once: 
					updateText.Fade("Congradulations! You one!", sf::seconds(3));
                    prevGameState = WON;
                } else if (updateText.GetText().getFillColor().a < 10) {
					Close();
				}
                break;
            }


            std::string output = "Frame rate: ";
            // Update frame count
            frameCounter++;
            output = output + std::to_string(1000000.0 / static_cast<double>(clock.getElapsedTime().asMicroseconds() - prevElapsedTime.asMicroseconds()));
            framesText.setString(output);
            window.draw(framesText);

            // Draw updateText
            updateText.DrawText(&window);


            // End drawing loop
            window.display();
            prevElapsedTime = elapsedTime;
        }

    }
}

void GameClass::Close() {
    window.setMouseCursorVisible(true);
    window.close();
}


GameClass::~GameClass()
{
}
