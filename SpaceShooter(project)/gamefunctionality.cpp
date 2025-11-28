#include "gamefunctionality.h"





void playGameLevel(int levelTarget, Texture2D spaceship, int& currentscreen, Music bgm, Texture2D background, Texture2D enemyship, Sound hitSound)
{
	int space_x = gridWidth / 2;
	int space_y = gridHeight - 70;
	int bullet_x[20];
	int bullet_y[20];
	bool fire[20];
	int numberofbullets = 0;
	for (int i = 0; i < 20; i++) {
		fire[i] = false;
	}
	
	
	if (levelTarget == level_1_target) {
		
		enemy_move_limit = 2;
		enemy_move_step = 1;
	}
	else if (levelTarget == level_2_target) {   //increases speed for level 
		enemy_move_limit = 1;
		enemy_move_step = 2;
		level++;
	}

	setupEnemies(enemy_x, enemy_y, enemy_alive, max_total_enemies);




	while (!WindowShouldClose() && lives > 0 && enemies_destroyed_count < levelTarget) {
		
		UpdateMusicStream(bgm);


		updatePosition(space_x, space_y, fire, bullet_x, bullet_y, numberofbullets, currentscreen);

		if (currentscreen != 2) break;


		if (enemy_move_counter >= enemy_move_limit) {
			moveEnemies(enemy_x, enemy_y, enemy_alive, max_total_enemies);
			enemy_move_counter = 0;
		}
		enemy_move_counter++;
		checkCollisions(enemy_x, enemy_y, enemy_alive, max_total_enemies, fire, bullet_x, bullet_y, levelTarget, hitSound);
		checkShipCollision(enemy_x, enemy_y, enemy_alive, max_total_enemies, space_x, space_y, lives, levelTarget, hitSound);
		for (int i = 0; i < 20; i++) {
			if (fire[i]) {
				bullet_y[i] -= 10;
				if (bullet_y[i] < 1) {
					fire[i] = false;
				}
			}
		}
		for (int i = 0; i < max_total_enemies; i++) {
			if (enemy_alive[i] && enemy_y[i] >= gridHeight - 50) {
				lives--;
				enemy_alive[i] = false;
				active_enemies_count--;
				if (enemies_destroyed_count < levelTarget) {
					newEnemy(enemy_x, enemy_y, enemy_alive, i, levelTarget);
				}
				else {
					enemy_y[i] = -100;
				}
			}
		}
		BeginDrawing();
		Rectangle sourceRec = { 0.0f, 0.0f, (float)background.width, (float)background.height };
		Rectangle destRec = { 0.0f, 0.0f, 800.0f, 800.0f };
		Vector2 origin = { 0.0f, 0.0f };
		float rotation = 0.0f;
		DrawTexturePro(background, sourceRec, destRec, origin, rotation, WHITE);
		DrawGame(space_x, space_y, bullet_x, bullet_y, fire, enemy_x, enemy_y, enemy_alive, score, lives, spaceship, enemyship);

		EndDrawing();

	}
}

void newEnemy(int ex[], int ey[], bool ea[], int enemyIndex, int currentLevelTarget) {
	if (active_enemies_count < Active_Enemies && enemies_destroyed_count < currentLevelTarget) {
		int newX;
		int newY;

		int attempts = 0;


		do {
			newX = (rand() % (gridWidth - 50));
			int ver_pos = rand() % 5;
			newY = 2 + ver_pos;

			attempts++;
			if (attempts > 10) {
				return;
			}
		} while (CheckOverlap(newX, newY, enemyIndex));                      //enemies shouldnt overlap each other


		ex[enemyIndex] = newX;
		ey[enemyIndex] = newY;
		ea[enemyIndex] = true;
		active_enemies_count++;
	}
	else {
		ey[enemyIndex] = -1;
		ea[enemyIndex] = false;
	}
}



void DrawGame(int shipX, int shipY, int bullet_x[], int bullet_y[], bool fire[],
	int enemy_x[], int enemy_y[], bool enemy_alive[],
	int score, int lives, Texture2D ship, Texture2D enemy)
{

	DrawTexture(ship, shipX, shipY, WHITE);


	for (int i = 0; i < max_total_enemies; i++) {
		if (enemy_alive[i]) {



			DrawTexture(enemy, enemy_x[i], enemy_y[i], WHITE);

		}
	}


	for (int i = 0; i < 20; i++) {
		if (fire[i]) {

			DrawRectangle(bullet_x[i], bullet_y[i], 5, 15, BLUE);
		}
	}


	DrawText(TextFormat("SCORE: %d", score), 20, 20, 20, WHITE);
	DrawText(TextFormat("LIVES: %d", lives), 20, 50, 20, GREEN);
	DrawText(TextFormat("LEVEL: %d", level), 20, 80, 20, BLUE);
}

void updatePosition(int& space_x, int& space_y, bool fire[], int bullet_x[], int bullet_y[], int& numberofbullets, int& currentscreen) {
	if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && space_x > 0)
		space_x -= 10;
	if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && space_x < 740)
		space_x += 10;
	if (IsKeyDown(KEY_ESCAPE))
		currentscreen--;
	if (IsKeyPressed(KEY_SPACE)) {
		bullet_x[numberofbullets] = space_x + 26;
		bullet_y[numberofbullets] = space_y - 1;
		fire[numberofbullets] = true;
		numberofbullets++;
		if (numberofbullets >= 20) {
			numberofbullets = 0;
		}

	}

}

void setupEnemies(int ex[], int ey[], bool ea[], int count) {
	active_enemies_count = 0;
	for (int i = 0; i < count; i++) {
		if (i < Active_Enemies) {
			int newX;
			int newY;

			int attempts = 0;


			do {
				newX = (rand() % (gridWidth - 50));
				int ver_pos = rand() % 200;
				newY = ver_pos - 300;

				attempts++;
				if (attempts > 10) {
					newX = -100; newY = -100;
					break;
				}
			} while (CheckOverlap(newX, newY, i) == true);

			ex[i] = newX;
			ey[i] = newY;
			ea[i] = true;
			active_enemies_count++;

		}
		else {
			ex[i] = -1;
			ey[i] = -1;
			ea[i] = false;
		}
	}
}

void moveEnemies(int ex[], int ey[], bool ea[], int count) {

	for (int i = 0; i < count; i++) {
		if (ea[i]) {
			ey[i]=ey[i] + enemy_move_step;
		}
	}
}

void checkCollisions(int ex[], int ey[], bool ea[], int count, bool fire[], int bullet_x[], int bullet_y[], int currentLevelTarget, Sound hitSound) {

	for (int e = 0; e < count; e++) {
		if (ea[e]) {


			for (int b = 0; b < 20; b++) {
				if (fire[b]) {

					bool collisionX = (bullet_x[b] + 5 >= ex[e]) &&
						(bullet_x[b] <= ex[e] + 50);


					bool collisionY = (bullet_y[b] + 15 >= ey[e]) &&
						(bullet_y[b] <= ey[e] + 50);


					if (collisionX && collisionY) {
						PlaySound(hitSound);
						ea[e] = false;
						fire[b] = false;
						bullet_y[b] = -1;
						score += 10;
						enemies_destroyed_count++;
						active_enemies_count--;

						if (enemies_destroyed_count < currentLevelTarget) {
							newEnemy(enemy_x, enemy_y, enemy_alive, e, currentLevelTarget);
						}
						else {
							ey[e] = -1;
							ea[e] = false;
						}

						return;
					}
				}
			}
		}
	}
}
//files for stroing highscore
void loadScore() {
	ifstream scoreStored("highscore.txt");
	if (scoreStored.is_open()) {
		scoreStored >> highscore;
		scoreStored.close();
	}

}
void updateScore() {
	ofstream scoreStored("highscore.txt");
	if (scoreStored.is_open()) {
		scoreStored << highscore;
		scoreStored.close();
	}
}

void enemyShoot(int ex[], int ey[], bool ea[], int count) {
	int shooter = rand() % count;
	if (ea[shooter]) {
		if (ey[shooter] >= 0) {
			enemy_bullet_x[enemyBulletCount] = ex[shooter] + 25;
			enemy_bullet_y[enemyBulletCount] = ey[shooter] + 51;
			enemy_fire[enemyBulletCount] = true;
			enemyBulletCount++;
			if (enemyBulletCount >= maxBullets_enemy) {
				enemyBulletCount = 0;
			}
		}
	}
}
void updateEnemyBullets(int& space_x, int& space_y, Sound hitSound) {
	for (int i = 0; i < maxBullets_enemy; i++) {
		if (enemy_fire[i]) {
			enemy_bullet_y[i] = enemy_bullet_y[i] + (enemy_move_step + 1);

			bool collisionX = (enemy_bullet_x[i] + 5 >= space_x) && (enemy_bullet_x[i] <= space_x + shipWidth);

			bool collisionY = (enemy_bullet_y[i] + 15 >= space_y) && (enemy_bullet_y[i] <= space_y + shipHeight);

			if (collisionX && collisionY) {
				lives--;
				PlaySound(hitSound);
				enemy_fire[i] = false;
			}

			if (enemy_bullet_y[i] >= gridHeight - 1) {
				enemy_fire[i] = false;
			}
		}
	}
}

void drawEnemyBullets(char gridArray[gridWidth][gridHeight]) {
	for (int i = 0; i < maxBullets_enemy; i++) {
		if (enemy_fire[i]) {
			if (enemy_bullet_y[i] > 0 && enemy_bullet_y[i] < gridHeight - 1 &&
				enemy_bullet_x[i] > 0 && enemy_bullet_x[i] < gridWidth - 1) {
				gridArray[enemy_bullet_y[i]][enemy_bullet_x[i]] = 'v';
			}
		}
	}
}

void playGameLevel3(int levelTarget, Texture2D spaceship, int& currentscreen, Music bgm, Texture2D background, Texture2D enemyship, Sound hitSound)
{
	int space_x = gridWidth / 2;
	int space_y = gridHeight - 70;

	int bullet_x[20];
	int bullet_y[20];
	bool fire[20];
	int numberofbullets = 0;
	for (int i = 0; i < 20; i++) fire[i] = false;

	for (int i = 0; i < maxBullets_enemy; i++) enemy_fire[i] = false;

	setupEnemies(enemy_x, enemy_y, enemy_alive, max_total_enemies);
	level++;
	enemy_move_limit = 1;
	enemy_move_step = 1.5;
	while (!WindowShouldClose() && lives > 0 && enemies_destroyed_count < levelTarget) {

	
		UpdateMusicStream(bgm);




		updatePosition(space_x, space_y, fire, bullet_x, bullet_y, numberofbullets, currentscreen);
		if (currentscreen != 2) break;
		if (enemy_move_counter >= enemy_move_limit) {
			moveEnemies(enemy_x, enemy_y, enemy_alive, max_total_enemies);
			enemy_move_counter = 0;
		}
		enemy_move_counter++;
		checkShipCollision(enemy_x, enemy_y, enemy_alive, max_total_enemies, space_x, space_y, lives, levelTarget, hitSound);
		if (rand() % 20 == 0) {
			enemyShoot(enemy_x, enemy_y, enemy_alive, max_total_enemies);
		}
		updateEnemyBullets(space_x, space_y,hitSound);

		for (int i = 0; i < 20; i++) {
			if (fire[i]) {
				bullet_y[i] -= 10;
				if (bullet_y[i] < 1) fire[i] = false;
			}
		}
		checkBulletCollision(fire, bullet_x, bullet_y, enemy_fire, enemy_bullet_x, enemy_bullet_y,hitSound);
		checkCollisions(enemy_x, enemy_y, enemy_alive, max_total_enemies,fire, bullet_x, bullet_y, levelTarget,hitSound);


		for (int i = 0; i < max_total_enemies; i++) {
			if (enemy_alive[i] && enemy_y[i] >= gridHeight - 50) {
				lives--;
				enemy_alive[i] = false;
				active_enemies_count--;
				if (enemies_destroyed_count < levelTarget) {
					newEnemy(enemy_x, enemy_y, enemy_alive, i, levelTarget);
				}
				else {
					enemy_y[i] = -100;
				}
			}
		}

		BeginDrawing();
		Rectangle sourceRec = { 0.0f, 0.0f, (float)background.width, (float)background.height };
		Rectangle destRec = { 0.0f, 0.0f, 800.0f, 800.0f };
		Vector2 origin = { 0.0f, 0.0f };
		float rotation = 0.0f;
		DrawTexturePro(background, sourceRec, destRec, origin, rotation, WHITE);
		DrawGame(space_x, space_y, bullet_x, bullet_y, fire, enemy_x, enemy_y, enemy_alive, score, lives, spaceship, enemyship);
		for (int i = 0; i < maxBullets_enemy; i++) {
			if (enemy_fire[i]) {
				DrawRectangle(enemy_bullet_x[i], enemy_bullet_y[i], 5, 15, RED);
			}
		}
		EndDrawing();
	}
}
//bonus score for finishing game early
int scoreCalculator(int score, int start, int end) {
	int diff = end - start;
	int bonus = (200 - diff) * 5;
	if (bonus < 0) {
		bonus = 0;
	}
	score = score + bonus;
	return score;
}

void checkShipCollision(int ex[], int ey[], bool ea[], int count, int& space_x, int& space_y, int& lives, int levelTarget, Sound hitSound) {
	for (int i = 0; i < count; i++) {
		if (ea[i]) {
			bool collisionX = (ex[i] + 50 >= space_x) &&
				(ex[i] <= space_x + shipWidth);

			bool collisionY = (ey[i] + 50 >= space_y) &&
				(ey[i] <= space_y + shipHeight);

			if (collisionX && collisionY) {

				lives--;
				PlaySound(hitSound);

				ea[i] = false;
				active_enemies_count--;
				enemies_destroyed_count++;


				if (enemies_destroyed_count < levelTarget) {
					newEnemy(enemy_x, enemy_y, enemy_alive, i, levelTarget);
				}
				else {
					ey[i] = -100;
				}


				break;
			}
		}
	}
}

void checkBulletCollision(bool fire[], int bullet_x[], int bullet_y[],bool enemy_fire[], int enemy_bullet_x[], int enemy_bullet_y[], Sound hitSound) {

	for (int p = 0; p < 20; p++) {
		if (fire[p]) {

			for (int e = 0; e < maxBullets_enemy; e++) {
				if (enemy_fire[e]) {



					bool collisionX = (bullet_x[p] + 5 >= enemy_bullet_x[e]) &&
						(bullet_x[p] <= enemy_bullet_x[e] + 5);


					bool collisionY = (bullet_y[p] + 10 >= enemy_bullet_y[e]) &&
						(bullet_y[p] <= enemy_bullet_y[e] + 10);

					if (collisionX && collisionY) {

						PlaySound(hitSound);
						score += 5;
						fire[p] = false;
						bullet_y[p] = -1;


						enemy_fire[e] = false;
						enemy_bullet_y[e] = -1;


						break;
					}
				}
			}
		}
	}
}

bool CheckOverlap(int newX, int newY, int enemyIndex) {
	for (int i = 0; i < max_total_enemies; i++) {

		if (!enemy_alive[i] || i == enemyIndex) continue;


		bool collisionX = (newX + 50 >= enemy_x[i]) && (newX <= enemy_x[i] + 50);
		bool collisionY = (newY + 50 >= enemy_y[i]) && (newY <= enemy_y[i] + 50);

		if (collisionX && collisionY) {
			return true;
		}
	}
	return false;
}