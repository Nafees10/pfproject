#include "base.h"
#include "usfml.h"
#include "gamerules.h"
#include <stdlib.h>
#include <iostream>
#include <string>

/// grid of candies
int _grid[ROWS][COLS];
/// objects
int _objects[ROWS][COLS];
/// score
int _score;
/// target score
int _scoreTarget;
/// number of moves left
int _movesLeft;

/// offset X of grid
int _offX;
/// offset Y of grid
int _offY;
/// length of cell
int _cellLength;
/// border width
int _borderWidth;

/// texture IDs for candies
int _candyTexture[21];
/// index of candyObject ID in _candyIndex array
int _candyIndex[21];
/// selected candy texture
int _candySelectedTexture;
/// main bkg texture
int _mainBkgTexture;
/// play button texture
int _playBtnTexture;
/// load button texture
int _loadBtnTexture;
/// ingame background
int _ingameBkgTexture;
/// background blur texture
int _blurBkgTexture;
/// dialog win texture
int _dialogWinTexture;
/// dialog lose texture
int _dialogLoseTexture;

/// candy selected object
int _candySelectedObject;
/// object ID for main menu background
int _mainBkgObject;
/// object ID for play play button
int _playBtnObject;
/// object ID for load button
int _loadBtnObject;
/// blur background object
int _blurBkgObject;
/// dialog win object
int _dialogObject;

/// score text
int _scoreText;
/// target score text
int _scoreTargetText;
/// moves text
int _movesText;

void init(){
	gridInit();
	for (int i = 0; i < 21; i ++){
		_candyTexture[i] = -1;
		_candyIndex[i] = -1;
	}
	_candySelectedTexture = -1;
	_mainBkgTexture = -1;
	_playBtnTexture = -1;
	_loadBtnTexture = -1;
	_ingameBkgTexture = -1;
	_blurBkgTexture = -1;
	_dialogWinTexture = -1;
	_dialogLoseTexture = -1;

	_candySelectedObject = -1;
	_mainBkgObject = -1;
	_playBtnObject = -1;
	_loadBtnObject = -1;
	_blurBkgObject = -1;
	_dialogObject = -1;

	_scoreText = -1;
	_scoreTargetText = -1;
	_movesText = -1;

	_scoreTarget = MIN_TARGET + (rand() % (MAX_TARGET - MIN_TARGET));
	_movesLeft = MIN_MOVES + (rand() % (MAX_MOVES - MIN_MOVES));
	for (int x = 0; x < COLS; x ++){
		for (int y = 0; y < ROWS; y ++){
			_objects[y][x] = objectCreate(-1);
			objectMove(_objects[y][x], _offX + x *(_borderWidth + _cellLength),
					   _offY + y * (_borderWidth + _cellLength));
		}
	}
	_score = 0;
}

void gridInit(){
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++)
			_grid[r][c] = 0;
	}
}

bool gridHasEmpty(){
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			if (_grid[r][c] == 0)
				return true;
		}
	}
	return false;
}

void gridStep(){
	// replace crushed with 0
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			if (candyCheck(_grid[r][c], CandyProperty::Crushed)){
				_grid[r][c] = 0;
			}
		}
	}
	for (int c = 0; c < COLS; c ++){
		for (int r = ROWS -1; r > 0; r --){
			if (_grid[r][c] == 0){
				_grid[r][c] = _grid[r - 1][c];
				_grid[r - 1][c] = 0;
			}
		}
		if (_grid[0][c] == 0)
			_grid[0][c] = candyGetRandom();
	}
}

void gridUpdateTextures(){
	for (int r = 0; r < ROWS; r ++){
		for (int c = 0; c < COLS; c ++){
			int candy = _grid[r][c];
			int textureId = -1;
			for (int i = 0; i < 21 && textureId == -1; i ++){
				if (candyCheck(_candyIndex[i], candyGetColor(candy),
							   candyGetType(candy)))
					textureId = _candyTexture[i];
			}
			if (textureId > -1){
				objectSetTexture(_objects[r][c], textureId);
			}
		}
	}
}

bool candyCrush(int row, int col, bool incrementScore){
	if (row < 0 || col < 0 || row > ROWS || col > COLS ||
		!candyCheck(_grid[row][col], CandyProperty::Crushed))
		return false;
	if (incrementScore)
		_score += candyGetPoints(_grid[row][col]);
	_grid[row][col] |= CandyProperty::Crushed;
	return true;
}

int candyGetRandom(){
	int candy = 1 << (rand() % 5); // color, 0 to 4
	candy |= CandyProperty::Plain; // property
	// randomise for color bomb
	if (rand() % 10 == 1)
		candy = CandyProperty::ColorBomb | CandyProperty::Plain;
	return candy;
}

int candyGet(int color, int property){
	return (color & CandyProperty::ColorBomb) |
		(property & CandyProperty::AllProps);
}

int candyGetPoints(int candy){
	if (candyCheck(candy, CandyProperty::Crushed))
		return 0; // candy already marked as crushed
	switch (candyGetColor(candy)){
		case CandyProperty::Red:
		case CandyProperty::Yellow:
			return 30;
		case CandyProperty::Green:
			return 40;
		case CandyProperty::Blue:
			return 50;
		case CandyProperty::Orange:
			return 60;
		default:
			return 0;
	}
}

int candyGetColor(int candy){
	return candy & CandyProperty::ColorBomb;
}

int candyGetType(int candy){
	return candy & CandyProperty::AllProps;
}

bool candyCheck(int candy, int type){
	return (candy & type) != 0;
}

bool candyCheck(int candy, int type1, int type2){
	return (candy & type1) != 0 && (candy & type2) != 0;
}

bool swapIsPossible(int r1, int c1, int r2, int c2){
	if (c1 < 0 || c2 < 0 || c1 >= COLS || c2 >= COLS ||
		r1 < 0 || r2 < 0 || r1 >= ROWS || r2 >= ROWS)
		return false;
	if (r1 == r2)
		return abs(c1 - c2) == 1;
	if (c1 == c2)
		return abs(r1 - r2) == 1;
	return false;
}

void gridTryCrush(){
	bool flag = false;

}

bool swap(int r1, int c1, int r2, int c2){
	if (!swapIsPossible(r1, c1, r2, c2))
		return false;
	int tempCandy = _grid[r1][c1];
	_grid[r1][c1] = _grid[r2][c2];
	_grid[r2][c2] = tempCandy;
	// try all move functions
	bool flag = false;
	// TODO: finish this
	if (!flag)
		gridTryCrush();
	return true;
}

void initObjects(){
	_candySelectedTexture = objectLoadTexture((char*)"assets/candy-selected.png");
	_mainBkgTexture = objectLoadTexture((char*)"assets/bkg.png");
	_playBtnTexture = objectLoadTexture((char*)"assets/playbtn.png");
	_loadBtnTexture = objectLoadTexture((char*)"assets/loadbtn.png");
	_ingameBkgTexture = objectLoadTexture((char*)"assets/ingamebkg.png");
	_blurBkgTexture = objectLoadTexture((char*)"assets/bkg-blur.png");
	_dialogWinTexture = objectLoadTexture((char*)"assets/win.png");
	_dialogLoseTexture = objectLoadTexture((char*)"assets/lose.png");
	_mainBkgObject =  objectCreate(_mainBkgTexture);
	_playBtnObject = objectCreate(_playBtnTexture);
	_loadBtnObject = objectCreate(_loadBtnTexture);
	_blurBkgObject = objectCreate(_blurBkgTexture);
	_candySelectedObject = objectCreate(_candySelectedTexture);
	_dialogObject = objectCreate(_dialogLoseTexture);
	_candyTexture[0] = objectLoadTexture((char*)"assets/red.png");
	_candyIndex[0] = candyGet(CandyProperty::Red, CandyProperty::Plain);
	_candyTexture[1] = objectLoadTexture((char*)"assets/red-wrapped.png");
	_candyIndex[1] = candyGet(CandyProperty::Red, CandyProperty::Wrapped);
	_candyTexture[2] = objectLoadTexture((char*)"assets/red-hstriped.png");
	_candyIndex[2] = candyGet(CandyProperty::Red, CandyProperty::HStriped);
	_candyTexture[3] = objectLoadTexture((char*)"assets/red-vstriped.png");
	_candyIndex[3] = candyGet(CandyProperty::Red, CandyProperty::VStriped);
	_candyTexture[4] = objectLoadTexture((char*)"assets/yellow.png");
	_candyIndex[4] = candyGet(CandyProperty::Yellow, CandyProperty::Plain);
	_candyTexture[5] = objectLoadTexture((char*)"assets/yellow-wrapped.png");
	_candyIndex[5] = candyGet(CandyProperty::Yellow, CandyProperty::Wrapped);
	_candyTexture[6] = objectLoadTexture((char*)"assets/yellow-hstriped.png");
	_candyIndex[6] = candyGet(CandyProperty::Yellow, CandyProperty::HStriped);
	_candyTexture[7] = objectLoadTexture((char*)"assets/yellow-vstriped.png");
	_candyIndex[7] = candyGet(CandyProperty::Yellow, CandyProperty::VStriped);
	_candyTexture[8] = objectLoadTexture((char*)"assets/green.png");
	_candyIndex[8] = candyGet(CandyProperty::Green, CandyProperty::Plain);
	_candyTexture[9] = objectLoadTexture((char*)"assets/green-wrapped.png");
	_candyIndex[9] = candyGet(CandyProperty::Green, CandyProperty::Wrapped);
	_candyTexture[10] = objectLoadTexture((char*)"assets/green-hstriped.png");
	_candyIndex[10] = candyGet(CandyProperty::Green, CandyProperty::HStriped);
	_candyTexture[11] = objectLoadTexture((char*)"assets/green-vstriped.png");
	_candyIndex[11] = candyGet(CandyProperty::Green, CandyProperty::VStriped);
	_candyTexture[12] = objectLoadTexture((char*)"assets/blue.png");
	_candyIndex[12] = candyGet(CandyProperty::Blue, CandyProperty::Plain);
	_candyTexture[13] = objectLoadTexture((char*)"assets/blue-wrapped.png");
	_candyIndex[13] = candyGet(CandyProperty::Blue, CandyProperty::Wrapped);
	_candyTexture[14] = objectLoadTexture((char*)"assets/blue-hstriped.png");
	_candyIndex[14] = candyGet(CandyProperty::Blue, CandyProperty::HStriped);
	_candyTexture[15] = objectLoadTexture((char*)"assets/blue-vstriped.png");
	_candyIndex[15] = candyGet(CandyProperty::Blue, CandyProperty::VStriped);
	_candyTexture[16] = objectLoadTexture((char*)"assets/orange.png");
	_candyIndex[16] = candyGet(CandyProperty::Orange, CandyProperty::Plain);
	_candyTexture[17] = objectLoadTexture((char*)"assets/orange-wrapped.png");
	_candyIndex[17] = candyGet(CandyProperty::Orange, CandyProperty::Wrapped);
	_candyTexture[18] = objectLoadTexture((char*)"assets/orange-hstriped.png");
	_candyIndex[18] = candyGet(CandyProperty::Orange, CandyProperty::HStriped);
	_candyTexture[19] = objectLoadTexture((char*)"assets/orange-vstriped.png");
	_candyIndex[19] = candyGet(CandyProperty::Orange, CandyProperty::VStriped);
	_candyTexture[20] = objectLoadTexture((char*)"assets/colorbomb.png");
	_candyIndex[20] = candyGet(CandyProperty::ColorBomb, CandyProperty::Plain);

	// now for text/fonts
	fontLoad((char*)"assets/font.ttf");
	_scoreText = textCreate(48, 0x501c2d);
	textSet(_scoreText, _score);
	_scoreTargetText = textCreate(48, 0x501c2d);
	textSet(_scoreTargetText, _scoreTarget);
	_movesText = textCreate(48, 0x501c2d);
	textSet(_movesText, _movesLeft);
	// position stuff
	objectMove(_dialogObject, 152, 130);
	textMove(_scoreText, 86, 460);
	textMove(_scoreTargetText, 96,580);
	textMove(_movesText, 96, 180);
}

void drawScore(){
	textSet(_scoreText, _score);
	textDraw(_scoreText);
	textSet(_scoreTargetText, _scoreTarget);
	textDraw(_scoreTargetText);
	textSet(_movesText, _movesLeft);
	textDraw(_movesText);
}

void drawGrid(){
	for (int y = 0; y < ROWS; y ++){
		for (int x = 0; x < COLS; x ++){
			objectDraw(_objects[y][x]);
		}
	}
}

void run(){
	usfmlInit(1024, 768, (char*)"Candy Crush Game");
	_offX = 276;
	_offY = 0;
	_cellLength = 70;
	_borderWidth = 15;
	init();
	initObjects();
	objectMove(_playBtnObject, 352, 510);
	objectMove(_loadBtnObject, 352, 638);
	Event event;
	bool isRunning = true;
	// loop for main menu
	while (isRunning){
		frameClear(0xFFFFFF);
		objectDraw(_mainBkgObject);
		objectDraw(_playBtnObject);
		objectDraw(_loadBtnObject);
		framePush();
		if (!eventGet(event))
			continue;
		if (event.type == EventType::WindowCloseButtonPress){
			isRunning = false;
			break;
		}
		if (event.type == EventType::Mouse &&
			event.mouse.button == MouseButton::Left && event.mouse.pressed){
			std::cout << "click detected\n";
			if (event.mouse.x < 352 || event.mouse.x > 352 + 223)
				continue;
			if (event.mouse.y >= 510 && event.mouse.y <= 510 + 64){
				std::cout << "starting game\n";
				break;
			}
			if (event.mouse.y >= 638 && event.mouse.y <= 638 + 64){
				std::cout << "loading game\n";
				// TODO: call load function
				break;
			}
		}
	}
	bool readyForInput = false;
	bool startedPlaying = false;
	bool saveAtEnd = true;
	objectSetTexture(_mainBkgObject, _ingameBkgTexture);
	bool texSet = false;
	// loop for game
	int frameCount = 0;
	int r1 = -1, c1 = -1;
	while (isRunning){
		frameClear(0xFFFFFF);
		readyForInput = !gridHasEmpty();
		objectDraw(_mainBkgObject);
		gridUpdateTextures();
		drawGrid();
		drawScore();
		if (r1 >= 0 && c1 >= 0)
			objectDraw(_candySelectedObject);
		// do not let player start until grid is stable:
		if (!startedPlaying && readyForInput){
			gridTryCrush();
			readyForInput = !gridHasEmpty();
			startedPlaying = readyForInput;
		}
		if (_movesLeft <= 0 || _score >= _scoreTarget){
			if (!texSet){
				if (_score >= _scoreTarget)
					objectSetTexture(_dialogObject, _dialogWinTexture);
				else
					objectSetTexture(_dialogObject, _dialogLoseTexture);
				texSet = true;
				saveAtEnd = false;
				readyForInput = false;
			}
			objectDraw(_dialogObject);
		}
		if (frameCount == 0)
			gridStep();
		frameCount = (frameCount + 1) % 60;
		framePush();
		if (!eventGet(event))
			continue;
		if (event.type == EventType::WindowCloseButtonPress){
			break;
		}
		if (readyForInput && startedPlaying && event.type == EventType::Mouse &&
			event.mouse.pressed && event.mouse.button == MouseButton::Left){
			int x = event.mouse.x, y = event.mouse.y;
			x -= _offX;
			y -= _offY;
			if (x < 0 || y < 0)
				continue;
			y /= _borderWidth + _cellLength;
			x /= _borderWidth + _cellLength;
			if ((r1 == -1 && c1 == -1) || (!swapIsPossible(r1, c1, y, x))){
				r1 = y;
				c1 = x;
				x = _offX + c1 * (_cellLength + _borderWidth);
				y = _offY + r1 * (_cellLength + _borderWidth);
				objectMove(_candySelectedObject, x, y);
				std::cout << x << " " << y << "\n";
			}else{
				swap(r1, c1, y, x);
				r1 = -1;
				c1 = -1;
			}
		}
	}
	if (saveAtEnd){
		// TODO: call save function
	}
	usfmlDestroy();
	std::cout << "bye bye\n";
}
