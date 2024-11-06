#include "Game.h"

Game::Game(Graphics* graphics, HWND window_handle)
{
	srand(time(0));

	this->graphics = graphics;

	GetClientRect(window_handle, &window);
	//ClipCursor(&window);

	gamefield = new Gamefield(graphics);

	for (int i = 0; i < 5; i++) {
		object[i] = new Object(graphics);
	}
	objectArraySize = (int)(sizeof(object) / sizeof(object[0]));
}

Game::~Game()
{
}

bool Game::RectCollide(RECT souceRect, RECT targetRect)
{
	return (souceRect.right > targetRect.left && souceRect.left < targetRect.right && souceRect.bottom > targetRect.top && souceRect.top < targetRect.bottom);
}

void Game::RunObject(int index, bool isFirst)
{
	// COLLIDE WITH BAR
	if (RectCollide(object[index]->GetRect(), gamefield->GetBar()) && object[index]->GetColor() == gamefield->GetBarColor() && isFirst) {
		object[index]->SetStayOnBar(true);
	}
	// COLLIDE WITH OBJECT
	else if (RectCollide(object[index]->GetRect(), gamefield->GetBar()) && object[index]->GetColor() == gamefield->GetBarColor() && !isFirst && !object[index]->GetIsStored()) {
		object[index]->SetStayOnObject(true);
	}

	// STAYING ON BAR
	if (object[index]->GetStayOnBar() && !object[index]->GetIsStored()) {
		int barCenterX = gamefield->GetBar().left + (gamefield->GetBar().right - gamefield->GetBar().left) / 2;
		object[index]->SetTopLeftPos(barCenterX - 5, gamefield->GetBar().top - 10 - 3, barCenterX + 5, gamefield->GetBar().top - 3);
	}
	// STAYING ON OBJECT
	else if (object[index]->GetStayOnObject() && !object[index]->GetIsStored()) {
		int objectCenterX = gamefield->GetBar().left + (gamefield->GetBar().right - gamefield->GetBar().left) / 2;
		object[index]->SetTopLeftPos(objectCenterX - 5, object[index - 1]->GetRect().top - 10 - 3, objectCenterX + 5, object[index - 1]->GetRect().top - 3);
	}
	// DEAD OBJECTS
	else if (object[index]->TouchedBottom() && !object[index]->GetIsStored()) {
		if (!object[index]->GetMinus()) {
			// Decrease Possible Score and Lives
			lives--;
			possibleScore--;

			object[index]->SetMinus(true);
		}

		object[index]->DeadObject();
		// gamefield->ShakeEffect();

		// Move an element from the object array to the end
		auto temp_object = object[index];
		for (int i = index; i < objectArraySize; i++) {
			object[i] = object[i + 1];
		}
		object[objectArraySize - 1] = temp_object;
	}
	else if (object[index]->GetIsStored()) {
		int third_of_field = (gamefield->GetField().right - gamefield->GetField().left) / 3;

		// CHECKING IF ANOTHER OBJECT IS ALREADY STORED
		for (int i = 0; i < index; i++) {
			if (object[i]->GetIsStored() && object[i]->GetColor() == object[index]->GetColor()) {
				storedObjectIndex = i;
				break;
			}
		}
		for (int i = index + 1; i < objectArraySize; i++) {
			if (object[i]->GetIsStored() && object[i]->GetColor() == object[index]->GetColor()) {
				storedObjectIndex = i;
				break;
			}
		}

		if (object[index]->GetStoreBottom()) {
			object[index]->SetTopLeftPos(gamefield->GetField().left + (third_of_field / 2) - 5 + third_of_field * object[index]->GetColor(), window.bottom - 13,
				gamefield->GetField().left + (third_of_field / 2) + 5 + third_of_field * object[index]->GetColor(), window.bottom - 3);
		}
		else if (object[index]->GetStoreOnObject()) {
			object[index]->SetTopLeftPos(object[storedObjectIndex]->GetRect().left, object[storedObjectIndex]->GetRect().top - 13,
				object[storedObjectIndex]->GetRect().right, object[storedObjectIndex]->GetRect().top - 3);
		}
	}
	// KEEP FALLING IF NO CONDITIONS ARE MET
	else {
		object[index]->Fall();
	}

	// DETECTING IF MOUSE PRESSED TO STORE THE OBJECT
	if (Window::GetLBClick() && object[0]->GetColor() == gamefield->GetStorageColor() && !pressed && allObjectUsed && !object[0]->GetIsStored()) {
		// Increase Storage Score
		storageScore[object[0]->GetColor()]++;

		int third_of_field = (gamefield->GetField().right - gamefield->GetField().left) / 3;
		goOffX = gamefield->GetField().left + (third_of_field / 2) - 5 + third_of_field * object[0]->GetColor();

		scoreGoOff = true;
		scoreCounter = 0;

		// Store the bottom object
		object[0]->SetIsStored(true);
		object[0]->SetStayOnBar(false);
		object[0]->SetStayOnObject(false);

		// Checking if the object is stored bottom or on an object
		for (int i = 1; i < objectArraySize; i++) {
			if (object[i]->GetIsStored() && object[i]->GetColor() == object[index]->GetColor()) {
				object[0]->SetStoreOnObject(true);
				object[0]->SetStoreBottom(false);
				break;
			}
			else {
				object[0]->SetStoreBottom(true);
				object[0]->SetStoreOnObject(false);
			}
		}

		// Stick the Next object on the Bar
		if (!object[1]->GetIsDead() && !object[1]->GetIsStored()) {
			object[1]->SetStayOnBar(true);
			object[1]->SetStayOnObject(false);
		}

		// Move the first element to the end
		auto temp_object = object[0];
		for (int i = 0; i < objectArraySize; i++) {
			object[i] = object[i + 1];
		}
		object[objectArraySize - 1] = temp_object;

		pressed = true;
	}
	else if (Window::GetLBClick() && object[0]->GetColor() != gamefield->GetStorageColor() && !pressed && allObjectUsed && !object[0]->GetIsStored()) {
		// Decrease Life
		if (!object[0]->GetStoreMinus()) {
			lives--;
			object[0]->SetStoreMinus(true);
		}
		// Decrease Possible Score
		possibleScore--;

		int third_of_field = (gamefield->GetField().right - gamefield->GetField().left) / 3;
		goOffX = gamefield->GetField().left + (third_of_field / 2) - 5 + third_of_field * gamefield->GetStorageColor();

		scoreGoOffMinus = true;
		scoreCounter = 0;

		// Kill the bottom object
		object[0]->DeadObject();
		object[0]->SetIsStored(false);
		object[0]->SetStayOnBar(false);
		object[0]->SetStayOnObject(false);

		// Stick the Next object on the Bar
		if (!object[1]->GetIsDead() && !object[1]->GetIsStored()) {
			object[1]->SetStayOnBar(true);
			object[1]->SetStayOnObject(false);
		}

		// Move the first element to the end
		auto temp_object = object[0];
		for (int i = 0; i < objectArraySize; i++) {
			object[i] = object[i + 1];
		}
		object[objectArraySize - 1] = temp_object;

		pressed = true;
	}
	else if (!Window::GetLBClick()) {
		pressed = false;
	}

	// RENDER THE OBJECT
	object[index]->Run();
}

void Game::GameOver()
{
	graphics->DrawTexts(L"GAME OVER", 100, 6, 90, 100, D2D1::ColorF(1.0f, 0.0f, 0.0f));
	graphics->DrawTexts(L"Your Number of Lives Ran Out", 30, 25, 200, 250, D2D1::ColorF(1.0f, 1.0f, 1.0f));

	RECT returnMenu = { window.right / 2 - 110, 500, window.right / 2 + 170, 550 };
	if (cursor.x > returnMenu.left && cursor.x < returnMenu.right && cursor.y > returnMenu.top && cursor.y < returnMenu.bottom) {
		graphics->DrawRect(returnMenu, D2D1::ColorF(0.0f, 1.0f, 1.0f));
		graphics->DrawTexts(L"RETURN TO MENU", 30, 10, returnMenu.left + 5, returnMenu.top + 5, D2D1::ColorF(1.0f, 1.0f, 0.0f));
	}
	else {
		graphics->DrawTexts(L"RETURN TO MENU", 30, 10, returnMenu.left + 5, returnMenu.top + 5, D2D1::ColorF(1.0f, 1.0f, 0.0f));
	}

	if (cursor.x > returnMenu.left && cursor.x < returnMenu.right && cursor.y > returnMenu.top && cursor.y < returnMenu.bottom && Window::GetLBClick()) {
		returnMenuScreen = true;
	}
}

void Game::CountDown()
{
	if (countDown) {
		countDownCounter++;

		if (countDownCounter > 0 && countDownCounter < 50) graphics->DrawTexts(L"3", 100, -2, window.right / 2 - 25, window.bottom / 2 - 80, D2D1::ColorF(1.0f, 0.0f, 0.0f));
		else if (countDownCounter > 50 && countDownCounter < 100) graphics->DrawTexts(L"2", 100, -2, window.right / 2 - 25, window.bottom / 2 - 80, D2D1::ColorF(0.0f, 1.0f, 0.0f));
		else if (countDownCounter > 100 && countDownCounter < 150) graphics->DrawTexts(L"1", 100, -2, window.right / 2 - 25, window.bottom / 2 - 80, D2D1::ColorF(0.0f, 0.0f, 1.0f));
		else if (countDownCounter > 150) countDown = false;
	}
}

bool Game::GetReturnMenuScreen()
{
	return returnMenuScreen;
}

bool Game::GetLevelOver()
{
	return levelOver;
}

int Game::GetTotalScore()
{
	return totalScore;
}

void Game::SetAddScore(bool add)
{
	addScore = add;
}
bool Game::GetAddScore()
{
	return addScore;
}
int Game::GetLives()
{
	return lives;
}

void Game::Init(float speed, int maxArcSize, int level)
{
	gameOver = false;
	this->level = level;

	ShowCursor(true);

	gamefield->Init(window);

	for (int i = 0; i < 5; i++) {
		object[i]->Init(gamefield->GetField(), window, speed, maxArcSize);
		object[i]->ChangeColor(rand() % 3);
	}

	for (int i = 0; i < 3; i++) {
		storageScore[i] = 0;
	}
	possibleScore = objectArraySize;
	totalScore = 0;
	totalTotalScore = 0;
	lives = 3;

	minusLives = false;
	anotherObjectStored = false;
	pressed = false;
	allObjectUsed = false;

	addScore = false;
	continueLives = false;

	countDown = true;
	countDownCounter = 0;

	returnMenuScreen = false;
}

void Game::Run(int tScore, int life)
{
	GetCursorPos(&cursor);

	if (!continueLives) {
		lives = life;
		continueLives = true;
	}

	CountDown();
	if (!gameOver) {
		totalScore = +storageScore[0] + storageScore[1] + storageScore[2];
		totalTotalScore = totalScore + tScore;
		gamefield->Run(cursor, totalTotalScore, lives, level, allObjectUsed);
	}
	if (!gameOver && !countDown) {
		if (KEY_DOWN(VK_ESCAPE))
			ShowCursor(true);

		RunObject(0, true);
		if (object[0]->GetStayOnBar() || object[0]->GetStayOnObject() || object[0]->TouchedBottom()) {
			RunObject(1, false);

			if (object[1]->GetStayOnBar() || object[1]->GetStayOnObject() || object[1]->TouchedBottom()) {
				RunObject(2, false);

				if (object[2]->GetStayOnBar() || object[2]->GetStayOnObject() || object[2]->TouchedBottom()) {
					RunObject(3, false);

					if (object[3]->GetStayOnBar() || object[3]->GetStayOnObject() || object[3]->TouchedBottom()) {
						RunObject(4, false);

						if (object[4]->GetStayOnBar() || object[4]->GetStayOnObject() || object[4]->TouchedBottom()) {
							allObjectUsed = true;
						}
					}
				}
			}
		}

		if (scoreGoOff) {
			scoreCounter++;
			if (scoreCounter < 20)
				gamefield->ScoreGoOff(true, goOffX, gamefield->GetField().bottom + 20);
			else
				scoreGoOff = false;
		}
		else if (scoreGoOffMinus) {
			scoreCounter++;
			if (scoreCounter < 20)
				gamefield->ScoreGoOff(false, goOffX, gamefield->GetField().bottom + 20);
			else
				scoreGoOffMinus = false;
		}

		if (totalScore == possibleScore)
			levelOver = true;
		else if (lives <= 0)
			gameOver = true;
	}
	else if (gameOver) {
		GameOver();
	}
}