#include "base.h"
#include "usfml.h"
#include "gamerules.h"
#include "saveload.h"
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
/// empty texture
int _nullTexture;
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
	// set all textures to -1
	for (int i = 0; i < 21; i ++){
		_candyTexture[i] = -1;
		_candyIndex[i] = -1;
	}
	_nullTexture = -1;
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

bool candyCrush(int row, int col){
	if (row < 0 || col < 0 || row > ROWS || col > COLS ||
		candyCheck(_grid[row][col], CandyProperty::Crushed))
		return false;
	_score += candyGetPoints(_grid[row][col]);
	_grid[row][col] |= CandyProperty::Crushed;
	return true;
}

void candyCrush(int r1, int c1, int r2, int c2){
	for (int r = r1; r <= r2; r++){
		for (int c = c1; c <= c2; c ++)
			candyCrush(r,c);
	}
}

int candyGetRandom(){
	int candy = 1 << (rand() % 5); // color, 0 to 4
	candy |= CandyProperty::Plain; // property
	/*int rP = 6 + (rand() % 4);
	candy |= 1 << rP;
	if (rP == 8 || rP == 9)
		candy |= CandyProperty::Striped;
	// randomise for color bomb
	if (rand() % 10 == 1)
		candy = CandyProperty::ColorBomb;*/
	return candy;
}

int candyGet(int color, int property){
	return (color & CandyProperty::AllColors) |
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
	return candy & CandyProperty::AllColors;
}

int candyGetType(int candy){
	return candy & CandyProperty::AllProps;
}

bool candyCheck(int candy, int type){
	return type != 0 && (candy & type) == type;
}

bool candyCheck(int candy, int type1, int type2){
	return type1 != 0 && type2 != 0 &&
		(candy & type1) == type1 && (candy & type2) == type2;
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

bool gridTryCrush(int r1, int c1, int r2, int c2){
	// DO NOT CHANGE THE ORDER OF THESE FUNCTIONS
	return move6(_grid) | move5(_grid) | move4(_grid) |
		 move3(_grid) | move2(_grid, r1, c1, r2, c2) | move1(_grid);
}

bool swap(int r1, int c1, int r2, int c2){
	if (!swapIsPossible(r1, c1, r2, c2))
		return false;
	int tempCandy = _grid[r1][c1];
	_grid[r1][c1] = _grid[r2][c2];
	_grid[r2][c2] = tempCandy;
	// try all move functions.
	bool flag = false;
	flag = move12(_grid, r1, c1, r2, c2) | move11(_grid, r1, c1, r2, c2) |
		move10(_grid, r1, c1, r2, c2) | move9(_grid, r1, c1, r2, c2) |
		move8(_grid, r1, c1, r2, c2) | move7(_grid, r1, c1, r2, c2);
	flag = flag | gridTryCrush(r1, r2, c1, c2);
	return flag;
}

void initObjects(){
	_nullTexture = objectLoadTexture((char*)"assets/null.png");
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
	_candyIndex[20] = CandyProperty::ColorBomb;

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
			if (_grid[y][x] != 0)
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
	bool levelPrepared = false;
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
				levelPrepared = true;
				if (!gameLoad(_grid, _score, _scoreTarget, _movesLeft)){
					std::cout << "failed to load, starting new\n";
					gridInit();
				}
				break;
			}
		}
	}
	bool saveAtEnd = true;
	objectSetTexture(_mainBkgObject, _ingameBkgTexture);
	bool texSet = false;
	int frameCount = 0;
	bool stable = false;
	int r1 = -1, c1 = -1;
	// loop for game
	while (isRunning){
		frameClear(0xFFFFFF);
		objectDraw(_mainBkgObject);
		drawGrid();
		drawScore();
		// if a candy is selcted, draw a transparent square around it
		if (r1 >= 0 && c1 >= 0)
			objectDraw(_candySelectedObject);
		// only run these cpu intensive functions if grid is unstable, and only
		// once every second (60fps)
		if (!stable && frameCount == 0){
			gridStep();
			if (!gridHasEmpty())
				stable = !gridTryCrush();
			gridUpdateTextures();
			if (!levelPrepared)
				_score = 0;
			levelPrepared = levelPrepared || stable;
		}
		frameCount = (frameCount + 1) % 60;
		if (_movesLeft <= 0 || _score >= _scoreTarget){
			// set texture of dialog box to win or loose dialog
			if (!texSet){
				if (_score >= _scoreTarget)
					objectSetTexture(_dialogObject, _dialogWinTexture);
				else
					objectSetTexture(_dialogObject, _dialogLoseTexture);
				texSet = true;
				saveAtEnd = false;
			}
			objectDraw(_blurBkgObject);
			objectDraw(_dialogObject);
			// trick it into not taking user input
			stable = false;
		}
		framePush();
		// skip rest of loop body if no user input
		if (!eventGet(event))
			continue;
		if (event.type == EventType::WindowCloseButtonPress){
			// do not save if level not prepared yet
			saveAtEnd = saveAtEnd && levelPrepared;
			break;
		}
		if (stable && event.type == EventType::Mouse &&
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
			}else{
				_movesLeft -= 1*swap(r1, c1, y, x);
				stable = false;
				r1 = -1;
				c1 = -1;
			}
		}
	}
	if (saveAtEnd)
		gameSave(_grid, _score, _scoreTarget, _movesLeft);
	usfmlDestroy();
	std::cout << "bye bye\n";
}
