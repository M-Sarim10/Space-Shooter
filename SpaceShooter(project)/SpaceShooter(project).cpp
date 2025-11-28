
#include "gamefunctionality.h"
using namespace std;



int score = 0;
int lives = 3;
int highscore = 0;
int enemy_x[max_total_enemies];
int enemy_y[max_total_enemies];
bool enemy_alive[max_total_enemies];
int enemies_destroyed_count = 0;
int active_enemies_count = 0;
bool enemy_fire[maxBullets_enemy];
int enemy_bullet_x[maxBullets_enemy];
int enemy_bullet_y[maxBullets_enemy];
int enemyBulletCount = 0;
int currentscreen = 0;
int enemy_move_counter = 0;
int enemy_move_limit = 1;
int enemy_move_step = 1;
int level = 1;


int main()
{
	srand(time(0));
	loadScore();
	
	int x = 400;
	InitWindow(800, 800, "space shoooter");
	SetTargetFPS(60);
	//sound k kaam
	InitAudioDevice();
	Music bgm = LoadMusicStream("assets/music.mp3");
	PlayMusicStream(bgm);
	SetMusicVolume(bgm, 0.6f);

	Sound hitSound = LoadSound("assets/shiphit.mp3");
	SetSoundVolume(hitSound, 0.6f);



	//image k kaam
	Image image = LoadImage("assets/background.png");
	Texture2D background = LoadTextureFromImage(image);
	UnloadImage(image);
	Image image2 = LoadImage("assets/background2.png");
	Texture2D background2 = LoadTextureFromImage(image2);
	UnloadImage(image2);

	Image image3 = LoadImage("assets/level.png");
	Texture2D background3 = LoadTextureFromImage(image3);
	UnloadImage(image3);


	// shipppp and enemy ship
	Image shipImg = LoadImage("assets/spaceship.png");
	Texture2D spaceship = LoadTextureFromImage(shipImg);
	UnloadImage(shipImg);
	Image enemy = LoadImage("assets/ufo.png");
	Texture2D enemyship = LoadTextureFromImage(enemy);
	UnloadImage(enemy);

	while (!WindowShouldClose())
	{
		UpdateMusicStream(bgm);
		if (currentscreen != 2)
		{
			BeginDrawing();
			ClearBackground(BLACK);
			
		//for spacshooter background hehe
		if (currentscreen == 0)
		{
			
			Rectangle sourceRec = { 0.0f, 0.0f, (float)background.width, (float)background.height };
			Rectangle destRec = { 0.0f, 0.0f, 800.0f, 800.0f };
			Vector2 origin = { 0.0f, 0.0f };
			float rotation = 0.0f;

			DrawTexturePro(background, sourceRec, destRec, origin, rotation, WHITE);
			DrawText("SPACE SHOOTER", 190, 35, 50, WHITE);
			DrawText("Press space key to continue....", 200, 700, 25, WHITE);
			if (IsKeyPressed(KEY_SPACE)) currentscreen = 1;
			
		}

		//for menu page yaad rkhna lrki
		else if (currentscreen == 1)
		{
			Rectangle sourceRec = { 0.0f, 0.0f, (float)background2.width, (float)background2.height };
			Rectangle destRec = { 0.0f, 0.0f, 800.0f, 800.0f };
			Vector2 origin = { 0.0f, 0.0f };
			float rotation = 0.0f;

			DrawTexturePro(background2, sourceRec, destRec, origin, rotation, WHITE);
			DrawText("space shooter", 200, 50, 60, BLUE);
			DrawText("(By SUPERNOVA)", 270, 130, 28, SKYBLUE);
			if (fmod(GetTime(), 1.0) < 0.42)
			{
				DrawText("PLAY", 350, 220, 45, PINK);
			}
			DrawText("The instructions to play tha game are as below:\n", 150, 380, 24, WHITE);
			DrawText("1_ Use the keys 'A' or 'D' or left or right arrow keys\n to move around.\n2_ Press 'Space' to fire bullets.\n3_ Hit the enemy ships and enemy bullets to score \n4_Press esc key to exit.", 150, 440, 24, WHITE);
			DrawText("Press enter key to play", 240, 700, 25, ORANGE);
			if (fmod(GetTime(), 1.0) <= 0.8)
				DrawText("........", 540, 700, 25, ORANGE);

			if (IsKeyPressed(KEY_ENTER)) {
				score = 0;
				lives = 3;
				enemies_destroyed_count = 0;
				currentscreen = 2;
			}
		}

		
		else if (currentscreen == 3)
		{
			DrawText("GAME OVER", 280, 400, 40, YELLOW);
			DrawText(TextFormat("Final Score: %i", score), 300, 460, 20, WHITE);
		}
		else if (currentscreen == 4) 
		{
			DrawText("YOU WIN!", 300, 400, 40, GREEN);
			DrawText(TextFormat("Final Score: %i", score), 300, 460, 20, WHITE);
			DrawText(TextFormat("High Score: %i", highscore), 300, 520, 20, WHITE);
		}
		EndDrawing();
		}
		else if (currentscreen == 2) {

			int start = time(0);
			enemies_destroyed_count = 0;
			playGameLevel(level_1_target, spaceship, currentscreen, bgm,background3,enemyship,hitSound);


			if (lives > 0 && currentscreen == 2) {

				enemies_destroyed_count = 0;
				playGameLevel(level_2_target, spaceship, currentscreen, bgm,background3,enemyship,hitSound);
			}
			if (lives > 0 && currentscreen == 2) {
				enemies_destroyed_count = 0;
				playGameLevel3(level_2_target, spaceship, currentscreen, bgm,background3,enemyship,hitSound); 
			}
			if (lives <= 0) currentscreen = 3; 
			else if (currentscreen == 2) {
				

				int end = time(0); 

				
				score = scoreCalculator(score, start, end);

				//updating high score
				if (score > highscore) {
					highscore = score;
					updateScore();
				}

				
				currentscreen = 4;
			}
		
		}
	}

	UnloadTexture(background);
	UnloadTexture(spaceship);
	CloseAudioDevice();
	CloseWindow();

	return 0;




}


