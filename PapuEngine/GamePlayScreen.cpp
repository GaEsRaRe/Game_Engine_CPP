#include "GamePlayScreen.h"
#include "Game.h"
#include "ScreenIndices.h"
#include <iostream>
#include "ResourceManager.h"
#include <random>
#include <ctime>


bool GamePlayScreen::onExitClicked()
{
	_currentState = ScreenState::EXIT_APPLICATION;
	return true;
}

GamePlayScreen::GamePlayScreen(Window* window) :
	_window(window), _time(0), _score(0)
{
	_screenIndex = SCREEN_INDEX_GAMEPLAY;
}

GamePlayScreen::~GamePlayScreen()
{
}

void GamePlayScreen::build() {

}

void GamePlayScreen::destroy() {
	delete _floor;
	delete _floor2;
	delete _floor3;
	//StaticBody* _floor4;
	delete _background;
	delete _window;
	delete _Player;
}

void GamePlayScreen::onExit() {
}

void GamePlayScreen::onEntry() {
	initWorld();
	initSystem();
	_spriteBatch.init();
	_hudBatch.init();
	initGUI();
	_camera2d.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2d.setPosition(
		glm::vec2(_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f));

	_background = new Background("assets/fondos/game.png");
	
	_Player = new Player(55, 55
		, glm::vec2(_window->getScreenWidth() / 2.0f, 100), "assets/Player.png", &_game->_inputManager);

	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(
		glm::vec2(_window->getScreenWidth() / 2.0f,
			_window->getScreenHeight() / 2.0f));

	_spriteFont = new SpriteFont("Fonts/arial.ttf", 64);
	
	physics.add_body(_Player,1,1);
	_floor = new StaticBody(1000, 20, glm::vec2(0, 60), "assets/floor.png", 1, 5000);
	_floor->id_group = 3;
	//out << _floor->uid << endl << _floor->id_group << endl;
	physics.add_body(_floor,3,5000);

	_floor2 = new StaticBody(500, 20, glm::vec2(0, 200), "assets/floor.png", 1, 5000);
	_floor2->id_group = 3;
	//out << _floor->uid << endl << _floor->id_group << endl;
	physics.add_body(_floor2, 3, 5000);
}

void GamePlayScreen::initWorld() {

}

void GamePlayScreen::initGUI()
{

}

void GamePlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera2d.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();

	_Player->draw(_spriteBatch);
	_background->draw(_spriteBatch);
	_floor->draw(_spriteBatch);
	_floor2->draw(_spriteBatch);

	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->draw(_spriteBatch);
		
	}
	for (size_t i = 0; i < _senemies.size(); i++)
	{
		_senemies[i]->draw(_spriteBatch);

	}


	_spriteBatch.end();
	_spriteBatch.renderBatch();

	drawHUD();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void GamePlayScreen::update() {
	//PARA EL JUGADOR CON LOS ENEMIGOS
	physics.temp = physics.get_collider(1, 2);
	if (physics.temp != -1) {
		physics.delete_with_uid(physics.temp);
		for (size_t i = 0; i < _enemies.size(); i++)
		{
			if (_enemies[i]->uid == physics.temp) {
				cout << "Es Up: " << _enemies[i]->_state;
				if (_enemies[i]->_state == 1) {
					_Player->score = _Player->score + 5;
				}
				else if (_enemies[i]->_state == 2) {
					_Player->score = _Player->score - 10;
				}
				else if (_enemies[i]->_state == 3) {
					if (_Player->_state == 1) {
						_Player->score = _Player->score + 10;
					}
				}
				_enemies.erase(_enemies.begin() + i);
			}

		}
		for (size_t i = 0; i < _senemies.size(); i++)
		{
			if (_senemies[i]->uid == physics.temp) {
				cout << "Es Side: " << _senemies[i]->_state;
				if (_senemies[i]->_state == 1) {
					_Player->score = _Player->score + 5;
				}
				else if (_senemies[i]->_state == 2) {
					_Player->score = _Player->score - 10;
				}else if (_senemies[i]->_state == 3){
					if (_Player->_state == 1) {
						_Player->score = _Player->score + 10;
					}
				}
				_senemies.erase(_senemies.begin() + i);
			}

		}

	}
	if (_Player->score <= 0) {
		_currentState = ScreenState::CHANGE_NEXT;
	}
	// PARA EL JUGADOR CON LAS PLATAFORMAS
	int temp = physics.get_collider(1, 3);
	//physics.run();
	//cout << _floor->uid << endl;
	if (temp == 5000) {
		if (!_Player->is_jumping) {
			_Player->is_falling = false;

			_Player->is_grounded = true;
		}
		else if(_Player->is_grounded == false){
			_Player->is_falling = true;
		}
		
	}
	else if (temp == -1) {
		if (!_Player->is_jumping) {
			_Player->is_falling = true;
		}
		else if (_Player->is_grounded) {
			
		}
	}
	

	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAMETIME = MS_PER_SECOND / _game->getFps();
	float previuosTime = SDL_GetTicks();
	float newTime = SDL_GetTicks();
	float frameTime = newTime - previuosTime;
	previuosTime = newTime;
	float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

	_camera2d.update();
	_hudCamera.update();
	_Player->update(0.01);
	//_floor->update(0.01);
	//physics.debug();
	checkInput();
	_elapsed += 0.1f;
	_timer += 0.1f;
	if (_timer >=6.0f) {
		_timer = 0;
		_time++;
	}
	if (_elapsed >= 20.0f) {
		std::random_device rd;    
		std::mt19937 rng(rd());    
		std::uniform_int_distribution<int> uni(0, 4); 

		auto random_integer = uni(rng);
		int type = 1;
		string texture;
		switch (random_integer) {
		case 1:
			texture = "assets/rabbit.png";
			type = 1;
			break;
		case 2:
			texture = "assets/snake.png";
			type = 2;
			break;
		case 3:
			texture = "assets/parrot.png";
			type = 3;
			break;
		default:
			texture = "assets/rabbit.png";
			type = 1;
		}
		_elapsed = 0;
		std::mt19937 randomEngine;
		randomEngine.seed(time(nullptr));
		std::uniform_real_distribution<float>
			randX(0, _window->getScreenWidth());
		int we = int(randX(randomEngine));
		_enemies.push_back(new EnemyAlien(70, 70, glm::vec2(
			randX(randomEngine), 800),
			texture,type,we));
		physics.add_body(_enemies.at(_enemies.size()-1),2,we);

		//Side Enemy

		auto random_integer2 = uni(rng);
		type = 1;
		switch (random_integer2) {
		case 1:
			texture = "assets/rabbit.png";
			type = 1;
			break;
		case 2:
			texture = "assets/snake.png";
			type = 2;
			break;
		case 3:
			texture = "assets/parrot.png";
			type = 3;
			break;
		default:
			texture = "assets/rabbit.png";
			type = 1;
		}
		_elapsed = 0;
		std::mt19937 randomEngine2;
		randomEngine2.seed(time(nullptr));
		std::uniform_real_distribution<float>
			randX2(0, _window->getScreenWidth());
		we = int(randX2(randomEngine));
		_senemies.push_back(new SideEnemy(70, 70, glm::vec2(
			-10, 70),
			texture, type, we));
		physics.add_body(_senemies.at(_senemies.size() - 1), 2, we);


	}
	//elimino enemigos y saco la puntuacion segun tipo

	for (size_t i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->getPosition().y < 10) {
			_enemies.erase(_enemies.begin() + i);
		}
		
	}

	for (size_t i = 0; i < _senemies.size(); i++)
	{
		if (_senemies[i]->getPosition().x > 680) {
			_senemies.erase(_senemies.begin() + i);
		}

	}
	/*
	//TODAS LAS COLISIONES SE MANEJAN CON LA NUEVA CLASE PHYSICS

	for (size_t i = 0; i < _enemies.size(); i++)
	{
		if (abs(_Player->getPosition().x - _enemies[i]->getPosition().x) < (_enemies[i]->get_collider().x)) {
			if (abs(_Player->getPosition().y - _enemies[i]->getPosition().y) < (_enemies[i]->get_collider().y)) {
				switch (_Player->_state) {
				case 1:
					if (_enemies[i]->_state == 1) {
						_Player->score = _Player->score + 10;
					}
					else if (_enemies[i]->_state == 2) {
						_Player->score = _Player->score - 10;
					}
					else if (_enemies[i]->_state == 3) {
						_Player->score = _Player->score -20;
					}
					break;
				case 2:
					if (_enemies[i]->_state == 2) {
						_Player->score = _Player->score + 20;
					}
					else if (_enemies[i]->_state == 3 || _enemies[i]->_state == 1) {
						_Player->score = _Player->score - 15;
					}
					
					break;
				case 3:
					if (_enemies[i]->_state == 3) {
						_Player->score = _Player->score * 2;
					}
					else if (_enemies[i]->_state == 2) {
						_Player->score = _Player->score - 5;
					}
					else if (_enemies[i]->_state == 1) {
						_Player->score = int(_Player->score /2);
					}
					break;
				default:
					break;
				}
				//_enemies.erase(_enemies.begin() + i);
				
				
			}
		}
	}
	/*
	for (size_t i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->getPosition().y <  _Player->get_collider().y ) {
			//_enemies.erase(_enemies.begin() + i);
		}

	}
	*/



	for (size_t i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update(0.1f);
	}
	for (size_t i = 0; i < _senemies.size(); i++)
	{
		_senemies[i]->update(0.1f);
	}


}



void  GamePlayScreen::drawHUD() {
	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _hudCamera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	_hudBatch.begin();
	if (_Player->score > 100) {
		sprintf_s(buffer, " Ganaste! %d", 10);
		_spriteFont->draw(_hudBatch, buffer, glm::vec2(300, 300),
			glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	}
	else if (_Player->score < 0) {
		sprintf_s(buffer, " Perdiste! %d", 0);
		_spriteFont->draw(_hudBatch, buffer, glm::vec2(300, 300),
			glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	}
	sprintf_s(buffer, " TIME %d", _time);
	_spriteFont->draw(_hudBatch, buffer, glm::vec2(0, 400),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	sprintf_s(buffer, " SCORE %d", _Player->score);
	_spriteFont->draw(_hudBatch, buffer, glm::vec2(0, 36),
		glm::vec2(0.5), 0.0f, ColorRGBA(255, 255, 255, 255));
	_hudBatch.end();
	_hudBatch.renderBatch();

}

void GamePlayScreen::initSystem()
{
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void GamePlayScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		_game->onSDLEvent(evnt);
	}
}

int GamePlayScreen::getNextScreen() const {
	return SCREEN_DEATH;
};

int GamePlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}
