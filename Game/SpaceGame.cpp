#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "Scene.h"

using namespace nu;

bool SpaceGame::Initialize()
{
	Game::Initialize();

	m_scene = new Scene();
	m_scene->SetGame(this);

	m_titleFont = new Font();
	m_titleFont->Load("fonts/Blaster.ttf", 100);

	m_titleText = new Text(m_titleFont);
	m_titleText->Create(Engine::Get().GetRenderer(), "Space Game", Color{ 1.0f, 1.0f, 1.0f });

	m_gameFont = new Font();
	m_gameFont->Load("fonts/Blaster.ttf", 32);

	m_scoreText = new Text(m_gameFont);
	Engine::Get().GetAudio().AddSound("AsteroidTitle", "audio/AsteroidTitle.mp3");
	return true;
}

void SpaceGame::Update(float dt)
{
	switch (m_gamestate)
	{
	case SpaceGame::GameState::Title:

		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gamestate = GameState::StartGame;
		}
		break;
	case SpaceGame::GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_gamestate = GameState::StartLevel;

		break;
	case SpaceGame::GameState::StartLevel:
		SpawnPlayer();
		m_gamestate = GameState::Game;
		break;
	case SpaceGame::GameState::Game:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0.0f)
		{
			m_spawnTimer = nu::RandomFloat(3.0f, 5.0f);
			SpawnEnemy();

		}
		break;
	case SpaceGame::GameState::GameOver:
		m_scene->RemoveAllActors();
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_gamestate = GameState::Title;
		}
		break;
	default:
		break;
	}


	Game::Update(dt);
}

void SpaceGame::Draw(nu::Renderer& renderer)
{
	switch (m_gamestate)
	{
	case SpaceGame::GameState::Title:
		//Draw title
		m_titleText->Draw(renderer, 600, 400);
		break;
	case SpaceGame::GameState::StartGame:
		break;
	case SpaceGame::GameState::StartLevel:
		m_scene->RemoveAllActors();
		SpawnPlayer();
		m_gamestate = GameState::Game;
		break;
	case SpaceGame::GameState::Game:
		//Draw score and lives
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30.0f, 30.0f);

		m_scoreText->Create(renderer, "Health: " + std::to_string(Player::Get().GetHealth()), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30.0f, 60.0f);

		m_scoreText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, (float) renderer.GetWidth() - 120, 30.0f);
		break;
	case SpaceGame::GameState::GameOver:
		//Draw game over
		break;
	default:
		break;
	}
	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
	isHit++;
	if (!(isHit % 2))
	{
		m_lives = m_lives - 1;
		if (m_lives <= 0) { m_gamestate = GameState::GameOver; }
		else m_gamestate = GameState::StartLevel;

	}
}

void SpaceGame::SpawnPlayer()
{
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	
	playerDesc.model = assets::playerModel;
	playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
	playerDesc.velocity = Vector2{ 0.0f, 0.0f };
	playerDesc.damping = 1.0f;
	playerDesc.speed = 150000.0f;

	std::unique_ptr<Player> player = std::make_unique<Player>( playerDesc );
	m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy()
{
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	enemyDesc.model = assets::enemyModel;
	enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
	enemyDesc.velocity = Vector2{ 0.0f, 0.0f };
	enemyDesc.speed = RandomFloat(10000.0f, 15000.0f);
	enemyDesc.damping = 3.0f;


	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}
