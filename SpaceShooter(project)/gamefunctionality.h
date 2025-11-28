#include <iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include "raylib.h"
#include <cmath>

using namespace std;


const int gridWidth = 800;
const int gridHeight = 800;
const int max_total_enemies = 14;
const int level_1_target = 12;
const int level_2_target = 16;
const int Active_Enemies = 4;
const int shipWidth = 70;
const int shipHeight = 70;
const int maxBullets_enemy = 20;


extern int enemy_move_limit;
extern int score;
extern int lives;
extern int highscore;
extern int enemy_x[max_total_enemies];
extern int enemy_y[max_total_enemies];
extern bool enemy_alive[max_total_enemies];
extern int enemies_destroyed_count;
extern int active_enemies_count;
extern bool enemy_fire[maxBullets_enemy];
extern int enemy_bullet_x[maxBullets_enemy];
extern int enemy_bullet_y[maxBullets_enemy];
extern int enemyBulletCount;
extern int currentscreen;
extern int enemy_move_counter;
extern int enemy_move_step;
extern int level;

void DrawGame(int shipX, int shipY, int bullet_x[], int bullet_y[], bool fire[],
	int enemy_x[], int enemy_y[], bool enemy_alive[],
	int score, int lives, Texture2D ship, Texture2D enemy);
void updatePosition(int&, int&, bool[], int[], int[], int&, int&);
void setupEnemies(int ex[], int ey[], bool ea[], int count);
void moveEnemies(int ex[], int ey[], bool ea[], int count);
void checkCollisions(int ex[], int ey[], bool ea[], int count, bool fire[], int bullet_x[], int bullet_y[], int currentLevelTarget, Sound hitSound);
void newEnemy(int ex[], int ey[], bool ea[], int enemyIndex, int currentLevelTarget);
void loadScore();
void updateScore();
int scoreCalculator(int, int, int);
void playGameLevel(int levelTarget, Texture2D spaceship, int& currentscreen, Music bgm, Texture2D background, Texture2D enemyship, Sound hitSound);
void enemyShoot(int ex[], int ey[], bool ea[], int count);
void updateEnemyBullets(int& space_x, int& space_y, Sound hitSound);
void playGameLevel3(int levelTarget, Texture2D spaceship, int& currentscreen, Music bgm, Texture2D background, Texture2D enemyship, Sound hitSound);
void checkShipCollision(int ex[], int ey[], bool ea[], int count, int& space_x, int& space_y, int& lives, int levelTarget, Sound hitSound);
void checkBulletCollision(bool fire[], int bullet_x[], int bullet_y[], bool enemy_fire[], int enemy_bullet_x[], int enemy_bullet_y[], Sound hitSound);
bool CheckOverlap(int newX, int newY, int enemyIndex);
