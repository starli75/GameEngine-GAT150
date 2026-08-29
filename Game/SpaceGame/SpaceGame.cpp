#include "pch.h"
#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Scene.h"


using namespace nu;

bool SpaceGame::Initialize()
{
	SetWorkingDirectory("SpaceGame");

	Game::Initialize();


	m_scene = std::make_unique<Scene>();
	m_scene->SetGame(this);
	m_scene->Load("data/scene.json");

	std::string fontName = "fonts/Blaster.ttf";
	std::string titleIDString = "title_font";
	std::string gameIDString = "game_font";

	m_titleText = new Text(Resources().GetWithID<Font>(titleIDString, fontName, 100.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "Space Game", Color{ 1.0f, 1.0f, 1.0f });

	m_scoreText = new Text(Resources().GetWithID<Font>(gameIDString, fontName, 32.0f));
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
		m_scene->RemoveAllActors();
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
	renderer.DrawTexture(*nu::Resources().Get<Texture>("Textures/background.jpg", Engine::Get().GetRenderer()), 1000, 700);
	switch (m_gamestate)
	{
	case SpaceGame::GameState::Title:
		//Draw title
		m_titleText->Draw(renderer, 600, 400);
		break;
	case SpaceGame::GameState::StartGame:
		break;
	case SpaceGame::GameState::StartLevel:
		//m_scene->RemoveAllActors();
		//SpawnPlayer();
		//m_gamestate = GameState::Game;
		break;
	case SpaceGame::GameState::Game: {
		//Draw score and lives
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30.0f, 30.0f);

		auto test = m_scene->GetActorByName<Player>("PlayerPrototype");
		if (test) 
		{
			//Player* currentPlayer = static_cast<Player*>(test);
			m_scoreText->Create(renderer, "Health: " + std::to_string(test->GetHealth()), { 1.0f, 1.0f, 1.0f });
			m_scoreText->Draw(renderer, 30.0f, 60.0f);
		}

		m_scoreText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, (float)renderer.GetWidth() - 120, 30.0f);
		break;
	}
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
	/*isHit++;
	if (!(isHit % 2))
	{*/
		m_lives = m_lives - 1;
		if (m_lives <= 0) { m_gamestate = GameState::GameOver; }
		else m_gamestate = GameState::StartLevel;

	//}
}

void SpaceGame::SpawnPlayer()
{
	auto actor = Factory::Instance().Create<Actor>("PlayerPrototype");
	//actor->SetPosition(nu::Vector2{ 30.0f, 30.0f });

	m_scene->AddActor(std::move(actor));
}

void SpaceGame::SpawnEnemy()
{
	int enemyIndex = nu::RandomInt(2);
	if (enemyIndex == 0)
	{
		auto actor = Factory::Instance().Create<Actor>("EnemyPrototype");
		actor->SetPosition({nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });

		m_scene->AddActor(std::move(actor));
	}
	else if (enemyIndex == 1)
	{
		auto actor = Factory::Instance().Create<Actor>("EnemyPrototype");
		actor->SetPosition({ nu::RandomFloat(1024.0f), nu::RandomFloat(800.0f) });

		m_scene->AddActor(std::move(actor));
	}
	/*
	EnemyDesc enemyDesc;
	enemyDesc.name = "Enemy";
	//enemyDesc.model = assets::enemyModel;
	enemyDesc.texture = Resources().Get<Texture>("Textures/EnemyShip.png", Engine::Get().GetRenderer());
	enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 90.0f, 1.0f };
	enemyDesc.velocity = Vector2{ 0.0f, 0.0f };
	enemyDesc.speed = RandomFloat(10000.0f, 15000.0f);
	enemyDesc.damping = 3.0f;


	m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
	*/
}
