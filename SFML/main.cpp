#include <SFML/Graphics.hpp>
#include <iostream>
#include<SFML/Audio.hpp>
#include<fstream>
#include<sstream>
#include <thread>
#include <chrono>
using namespace sf;
using namespace std;

RenderWindow window(VideoMode(600, 600), "flappy bird");

int decide, second_decide;
bool ischoosen = false, icon_choosen = false, lost = false, lvl = false, NoContinue = false;
float jump, gravity, pipes;
bool yesNO = false;
int Q_ans = 2;
double BIRD_X_POSITION, BIRD_Y_POSITION;
Vector2i mousepos;

RectangleShape play_icon(Vector2f(220.0f, 100.0f));
void RandomizePosition(int& x, int& a)
{
	while (x - (-a + 550) != 145)
	{
		a = 50 + (rand() % 450);
		x = 50 + (rand() % 450);
	}
}

// play
void main_menu(Texture play, Sprite background, Texture logo_tex)
{
	RectangleShape logo;
	RectangleShape original(Vector2f(100.0f, 100.0f));
	Texture tex;
	tex.loadFromFile("flappy bird down.png");
	original.setTexture(&tex);

	logo.setSize(Vector2f(450.0f, 150.0f));
	//play_icon.setSize(Vector2f(220.0f, 100.0f));


	logo.setFillColor(Color::White);
	logo.setTexture(&logo_tex);
	logo.setPosition(75, 50);


	play_icon.setTexture(&play);
	play_icon.setPosition(180, 400);

	original.setPosition(250.0f, 250.0f);

	window.draw(background);
	window.draw(logo);
	window.draw(play_icon);
	window.draw(original);

	window.display();

	// if condition for the mouse
	if (Mouse::isButtonPressed(Mouse::Left)) {
		mousepos = Mouse::getPosition(window);
	}
	if (mousepos.x >= 180 && mousepos.x <= 400 && mousepos.y >= 400 && mousepos.y <= 500) {
		second_decide = 1;
		icon_choosen = true;

		this_thread::sleep_for(chrono::milliseconds(500));
	}


}
// levels

void levels() {
	RectangleShape easy, normal, hard;
	easy.setSize(sf::Vector2f(300, 90));
	normal.setSize(sf::Vector2f(290, 95));
	hard.setSize(sf::Vector2f(300, 95));
	easy.setPosition(150, 100);
	normal.setPosition(150, 270);
	hard.setPosition(150, 440);

	Texture level_easy, level_normal, level_hard, back;
	Sprite background;
	back.loadFromFile("sky.png");
	background.setTexture(back);
	background.setTextureRect(IntRect(0, 400, 1024, 1024));

	level_easy.loadFromFile("easy.png");
	level_normal.loadFromFile("normal.png");
	level_hard.loadFromFile("hard.png");
	easy.setTexture(&level_easy);
	normal.setTexture(&level_normal);
	hard.setTexture(&level_hard);
	//window.clear();
	window.draw(background);
	window.draw(easy);
	window.draw(normal);
	window.draw(hard);
	window.display();

	if (Mouse::isButtonPressed(Mouse::Left)) {
		mousepos = Mouse::getPosition(window);
		if (mousepos.x >= 150 && mousepos.x <= 450 && mousepos.y >= 100 && mousepos.y <= 190) {
			pipes = -0.03;
			gravity = 0.05;
			jump = -0.3;
			lvl = true;
		}
		else if (mousepos.x >= 150 && mousepos.x <= 440 && mousepos.y >= 270 && mousepos.y <= 365) {
			pipes = -0.05;
			gravity = 0.066;
			jump = -0.35;
			lvl = true;
		}
		else if (mousepos.x >= 150 && mousepos.x <= 450 && mousepos.y >= 440 && mousepos.y <= 535) {
			pipes = -0.09;
			gravity = 0.09;
			jump = -0.4;
			lvl = true;
		}
	}

}

//choose bird
void choosebird(Texture tex, Texture tex2, Texture tex3, Texture tex4, Sprite background)
{
	//Textures For Arrows 
	RectangleShape arrows1(Vector2f(130.0f, 130.0f));
	arrows1.setPosition(225, 320);

	RectangleShape arrows2, arrows3, arrows4;

	arrows2.setSize(Vector2f(130.0f, 130.0f));
	arrows2.setPosition(225, 180);

	arrows3.setSize(Vector2f(130.0f, 130.0f));
	arrows3.setPosition(300, 250);

	arrows4.setSize(Vector2f(130.0f, 130.0f));
	arrows4.setPosition(153, 250);

	//Textures for arrows

	Texture arrowTex1, arrowTex2, arrowTex3, arrowTex4;

	arrowTex1.loadFromFile("arrow down.png");
	arrows1.setTexture(&arrowTex1);

	arrowTex2.loadFromFile("arrow up.png");
	arrows2.setTexture(&arrowTex2);

	arrowTex3.loadFromFile("arrow right.png");
	arrows3.setTexture(&arrowTex3);

	arrowTex4.loadFromFile("arrow left.png");
	arrows4.setTexture(&arrowTex4);

	RectangleShape bird1(Vector2f(90.0f, 90.0f));
	RectangleShape bird2(Vector2f(100.0f, 100.0f));
	RectangleShape bird3(Vector2f(100.0f, 100.0f));
	RectangleShape bird4(Vector2f(100.0f, 100.0f));

	bird1.setTexture(&tex);
	bird1.setPosition(250.0f, 95.0f);

	bird2.setTexture(&tex2);
	bird2.setPosition(440.0f, 255.0f);

	bird3.setTexture(&tex3);
	bird3.setPosition(240.0f, 440.0f);

	bird4.setTexture(&tex4);
	bird4.setPosition(40.0f, 255.0f);

	//Text to choose the bird

	Font font;
	font.loadFromFile("SNAP__.ttf");
	Text  choose;

	choose.setFont(font);
	choose.setFillColor(Color::Black);
	choose.setCharacterSize(50);
	choose.setString("Pick Your Bird");
	choose.setPosition(100, 20);

	window.draw(background);

	window.draw(choose);

	window.draw(arrows1);
	window.draw(arrows2);
	window.draw(arrows3);
	window.draw(arrows4);

	window.draw(bird1);
	window.draw(bird2);
	window.draw(bird3);
	window.draw(bird4);
	window.display();

	//cout << "please choose bird" ;
	if (Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		decide = 1; // el bird el asly

		ischoosen = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		decide = 2;  // el pink
		ischoosen = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		decide = 3;  //el 2zr2
		ischoosen = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		decide = 4;  //el 25dr
		ischoosen = true;
	}
}
int gameOver(int currentScore)
{
	ifstream input("best_score.txt");
	int bestScore = 0;
	input >> bestScore;
	ofstream output("best_score.txt");
	if (currentScore > bestScore)
	{
		output << currentScore;
		return currentScore;
	}
	else
	{
		output << bestScore;
		return bestScore;
	}

}
int YourCoins()
{
	ifstream read("YourCoins.txt");
	int currentCoins = 0;
	read >> currentCoins;
	return currentCoins;
}
void IncCoins()
{
	ifstream read("YourCoins.txt");
	int currentCoins = 0;
	read >> currentCoins;
	currentCoins++;

	ofstream writeIn("YourCoins.txt");
	writeIn << currentCoins;

}

void AskQuestion()
{
	Font scoreFont;
	scoreFont.loadFromFile("beeb.ttf");

	Text question;
	question.setFont(scoreFont); //BEEB FONT LIKE THE SCORE
	question.setCharacterSize(30);
	question.setStyle(Text::Bold);
	question.setFillColor(Color::Blue);
	//question.setPosition(0, -100);
	question.setString("Want to continue ?");

	Texture yes_texture, no_texture;
	yes_texture.loadFromFile("yes.png");
	no_texture.loadFromFile("no.png");
	RectangleShape yes(Vector2f(150.0f, 100.0f));
	RectangleShape no(Vector2f(150.0f, 100.0f));
	//yes.setPosition(0, -200);
	//no.setPosition(0, -200);
	yes.setTexture(&yes_texture);
	no.setTexture(&no_texture);

	Text decCoins;
	decCoins.setFont(scoreFont);
	decCoins.setCharacterSize(15);
	decCoins.setFillColor(Color::White);
	decCoins.setPosition(0, -50);
	decCoins.setString("( -10 coins )");

	Texture coinsBoard_texture;
	coinsBoard_texture.loadFromFile("board.png");
	Sprite coinsBoard_sprite;
	coinsBoard_sprite.setTexture(coinsBoard_texture);
	//coinsBoard_sprite.setPosition(0, -500);
	coinsBoard_sprite.setPosition(5, 100);
	question.setPosition(50, 180);
	yes.setPosition(30, 250);
	no.setPosition(400, 255);
	decCoins.setPosition(160, 300);

	window.draw(coinsBoard_sprite);
	window.draw(question);
	window.draw(yes);
	window.draw(no);
	window.draw(decCoins);

	window.display();

	if (Mouse::isButtonPressed(Mouse::Left)) {
		mousepos = Mouse::getPosition(window);
		if (mousepos.x >= 30 && mousepos.x <= 180 && mousepos.y >= 250 && mousepos.y <= 350)
		{
			yesNO = true;
			Q_ans = 1;
		}
		if (mousepos.x >= 400 && mousepos.x <= 550 && mousepos.y >= 255 && mousepos.y <= 355)
		{
			yesNO = true;
			Q_ans = 0;
		}
	}

}

int main()
{

	window.setFramerateLimit(1200);
	int numberOfCoins = 0;

	int score = 0, i = 0, cnt = 0, bestFromFile = 0;
	float velo = 0;
	bool collision1 = false;
	bool collision2 = false;
	bool collision3 = false;
	bool collision4 = false;
	bool intersect = false, movement = false;
	bool is_text_appeared = false;
	bool gameover_is_played = false;
	//bool gravity = false;

	RectangleShape bird(Vector2f(40, 40));
	bird.setPosition(280, 300);

	//upper rectangles
	RectangleShape shape(Vector2f(70.0f, 550.0f));
	RectangleShape shape2(Vector2f(70.0f, 550.0f));
	RectangleShape shape3(Vector2f(70.0f, 550.0f));
	RectangleShape shape4(Vector2f(70.0f, 550.0f));

	//lower rectangles 
	RectangleShape rec1(Vector2f(70.0f, 550.0f));
	RectangleShape rec2(Vector2f(70.0f, 550.0f));
	RectangleShape rec3(Vector2f(70.0f, 550.0f));
	RectangleShape rec4(Vector2f(70.0f, 550.0f));

	shape.setPosition(230, -700.0);
	shape2.setPosition(500, -700.0);
	shape3.setPosition(770, -700.0);
	shape4.setPosition(1040, -700.0);

	rec1.setPosition(230, 700.0);
	rec2.setPosition(500, 700.0);
	rec3.setPosition(770, 700.0);
	rec4.setPosition(1040, 700.0);

	//Textures
	Texture tex1, tex2, tex3, tex4;
	tex1.loadFromFile("sky.png");
	tex2.loadFromFile("down.png");
	tex3.loadFromFile("up.png");
	tex4.loadFromFile("game over.png");
	//set texture to rectangles
	rec1.setTexture(&tex2);
	rec2.setTexture(&tex2);
	rec3.setTexture(&tex2);
	rec4.setTexture(&tex2);

	shape.setTexture(&tex3);
	shape2.setTexture(&tex3);
	shape3.setTexture(&tex3);
	shape4.setTexture(&tex3);


	// transparent rectangles
	RectangleShape transparent1(Vector2f(1, 130));
	RectangleShape transparent2(Vector2f(1, 130));
	RectangleShape transparent3(Vector2f(1, 130));
	RectangleShape transparent4(Vector2f(1, 130));

	transparent1.setFillColor(Color::Transparent);
	transparent2.setFillColor(Color::Transparent);
	transparent3.setFillColor(Color::Transparent);
	transparent4.setFillColor(Color::Transparent);

	transparent1.setPosition(180.0, 700.0);
	transparent2.setPosition(430.0, 700.0);
	transparent3.setPosition(680.0, 700.0);
	transparent4.setPosition(930.0, 700.0);

	// background
	Sprite background_sprite;
	background_sprite.setTexture(tex1);
	background_sprite.setTextureRect(IntRect(0, 400, 1024, 1024));

	//  animation
	Texture originalanimation[10], yellowanimation[10], blueanimation[5], nesranimation[5];

	originalanimation[0].loadFromFile("flappy bird straight.png");
	originalanimation[1].loadFromFile("flappy bird up.png");
	originalanimation[2].loadFromFile("flappy bird straight.png");
	originalanimation[3].loadFromFile("flappy bird down.png");

	yellowanimation[0].loadFromFile("frame1.png");
	yellowanimation[1].loadFromFile("frame2.png");
	yellowanimation[2].loadFromFile("frame3.png");
	yellowanimation[3].loadFromFile("frame4.png");

	blueanimation[0].loadFromFile("blue straight.png");
	blueanimation[1].loadFromFile("blue up.png");
	blueanimation[2].loadFromFile("blue straight.png");
	blueanimation[3].loadFromFile("blue down.png");

	nesranimation[0].loadFromFile("fly1.png");
	nesranimation[1].loadFromFile("fly2.png");

	//start window
	Texture play, logo_tex;
	play.loadFromFile("play.png");
	logo_tex.loadFromFile("flappy bird logo.png");


	//retry and exit 
	RectangleShape restart_icon(Vector2f(220.0f, 100.0f));
	RectangleShape exit_icon(Vector2f(220.0f, 100.0f));

	Texture resttex;
	resttex.loadFromFile("restart.png");
	restart_icon.setTexture(&resttex);

	Texture exittex;
	exittex.loadFromFile("exit.png");
	exit_icon.setTexture(&exittex);



	//sounds
	SoundBuffer gameover_buffer;
	Sound gameover_sfx;
	gameover_sfx.setBuffer(gameover_buffer);
	gameover_buffer.loadFromFile("gameover_sfx.wav");

	SoundBuffer coin_buffer;
	Sound coin_sfx;
	coin_sfx.setBuffer(coin_buffer);
	coin_buffer.loadFromFile("smrpg_coin.wav");


	//how to play
	Font selectedfont;
	selectedfont.loadFromFile("font.ttf");
	Text how_to_play;
	how_to_play.setFont(selectedfont);
	how_to_play.setString("Press SPACE To Jump");
	how_to_play.setFillColor(Color::White);
	how_to_play.setCharacterSize(30);
	how_to_play.setPosition(800, 800);

	// setting original score 
	Font scoreFont;
	scoreFont.loadFromFile("beeb.ttf");
	ostringstream ssScore;
	ssScore << score;
	Text txtscore;
	txtscore.setCharacterSize(40);
	txtscore.setPosition(280, 100);
	txtscore.setFont(scoreFont);
	txtscore.setStyle(Text::Bold);
	txtscore.setString(ssScore.str());

	//game over current score and best score

	//current score
	Font currentScoreFont;
	currentScoreFont.loadFromFile("font.ttf");
	ostringstream ccScore;
	ccScore << score;
	Text txtCurrentScore;
	txtCurrentScore.setFont(currentScoreFont);
	txtCurrentScore.setCharacterSize(40);
	txtCurrentScore.setPosition(450, 240);
	txtCurrentScore.setStyle(Text::Bold);
	txtCurrentScore.setString(ccScore.str());

	//best score
	Font BestScoreFont;
	BestScoreFont.loadFromFile("font.ttf");
	ostringstream bstScore;
	Text txtbestScore;
	txtbestScore.setFont(currentScoreFont);
	txtbestScore.setCharacterSize(40);
	txtbestScore.setPosition(450, 340);
	txtbestScore.setStyle(Text::Bold);

	//score texture and sprite 
	Texture game_over_texture;
	game_over_texture.loadFromFile("score&best.png");
	Sprite game_over_sprite;
	game_over_sprite.setTexture(game_over_texture);
	game_over_sprite.setPosition(20, 150);

	//medals textures and sprite 
	Texture bronze, silver, gold;
	bronze.loadFromFile("Bronze-Medal.png");
	silver.loadFromFile("Silver-Medal.png");
	gold.loadFromFile("gold-Medal.png");
	Sprite bronze_sprite, silver_sprite, gold_sprite;
	bronze_sprite.setTexture(bronze);
	silver_sprite.setTexture(silver);
	gold_sprite.setTexture(gold);
	bronze_sprite.setPosition(80, 250);
	silver_sprite.setPosition(80, 250);
	gold_sprite.setPosition(80, 250);

	// game over
	RectangleShape gameover_shape(Vector2f(400, 100));
	gameover_shape.setTexture(&tex4);
	gameover_shape.setPosition(800.0f, 800.0f);

	// coin between pipe
	Texture coin_texture;
	coin_texture.loadFromFile("coin.png");
	Sprite coin_sprite;
	coin_sprite.setTexture(coin_texture);
	coin_sprite.setPosition(180, -100);
	int x_coin = 0, y_coin = 0;
	int slow_animation = 0; //slow animation for the coin

	//upper coin that counts 
	Texture upperCoin_texture;
	upperCoin_texture.loadFromFile("upper_coin.png");
	Sprite upperCoin_sprite;
	upperCoin_sprite.setTexture(upperCoin_texture);
	upperCoin_sprite.setPosition(0, 0);


	Font coins_font;
	coins_font.loadFromFile("micross.ttf");
	ostringstream coins;
	numberOfCoins = YourCoins();
	coins << numberOfCoins;
	Text coinsText;
	coinsText.setFont(coins_font);
	coinsText.setCharacterSize(30);
	coinsText.setPosition(50, 10);
	coinsText.setStyle(Text::Bold);
	coinsText.setString(coins.str());
	double COIN_X_POSITION = 0;

	Texture coinsBoard_texture;
	coinsBoard_texture.loadFromFile("board.png");
	Sprite coinsBoard_sprite;
	coinsBoard_sprite.setTexture(coinsBoard_texture);
	coinsBoard_sprite.setPosition(0, -500);

	Text question;
	question.setFont(scoreFont); //BEEB FONT LIKE THE SCORE
	question.setCharacterSize(30);
	question.setStyle(Text::Bold);
	question.setFillColor(Color::Blue);
	question.setPosition(0, -100);
	question.setString("Want to continue ?");

	Texture yes_texture, no_texture;
	yes_texture.loadFromFile("yes.png");
	no_texture.loadFromFile("no.png");
	RectangleShape yes(Vector2f(150.0f, 100.0f));
	RectangleShape no(Vector2f(150.0f, 100.0f));
	yes.setPosition(0, -200);
	no.setPosition(0, -200);
	yes.setTexture(&yes_texture);
	no.setTexture(&no_texture);

	Text decCoins;
	decCoins.setFont(scoreFont);
	decCoins.setCharacterSize(15);
	decCoins.setFillColor(Color::White);
	decCoins.setPosition(0, -50);
	decCoins.setString("( -10 coins )");
	//pause
	Texture pause_texture;
	pause_texture.loadFromFile("pause.png");
	RectangleShape pause_icon(Vector2f(50.0,50.0));
	pause_icon.setTexture(&pause_texture);
	pause_icon.setPosition(0, -580);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		// call function el start

		while (!icon_choosen)
		{
			main_menu(play, background_sprite, logo_tex);
			window.clear();
		}


		// call levels
		while (!lvl)
		{

			levels();
			window.clear();
		}
		// call function choose bird
		while (!ischoosen)
		{
			choosebird(originalanimation[0], yellowanimation[0], blueanimation[0], nesranimation[0], background_sprite);
			if (ischoosen)
			{
				if (decide == 1) { bird.setTexture(&originalanimation[0]); }
				else if (decide == 2) { bird.setTexture(&yellowanimation[0]); }
				else if (decide == 3) { bird.setTexture(&blueanimation[0]); }
				else if (decide == 4) { bird.setTexture(&nesranimation[0]); }
			}
			window.clear();
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) || is_text_appeared) {
			how_to_play.move(0.0, 0.07);
			is_text_appeared = true;
		}
		else { how_to_play.setPosition(150, 200); }
		//pause
		if (is_text_appeared==true)
		pause_icon.setPosition(545,0);
		else 
			pause_icon.setPosition(545, -1000);

		if (Keyboard::isKeyPressed(Keyboard::Key::P))
		{
			is_text_appeared = false;
		}

		//coin animation 
		slow_animation++;
		x_coin++;
		x_coin = x_coin % 5;
		if (slow_animation > 600)
		{
			coin_sprite.setTextureRect(IntRect(x_coin * 84, y_coin, 85, 85));
			slow_animation = 0;
		}

		// losing

		if (bird.getGlobalBounds().intersects(shape.getGlobalBounds()) == true ||
			bird.getGlobalBounds().intersects(shape2.getGlobalBounds()) == true ||
			bird.getGlobalBounds().intersects(shape3.getGlobalBounds()) == true ||
			bird.getGlobalBounds().intersects(shape4.getGlobalBounds()) == true ||
			bird.getGlobalBounds().intersects(rec1.getGlobalBounds()) == true ||
			bird.getGlobalBounds().intersects(rec2.getGlobalBounds()) == true ||
			bird.getGlobalBounds().intersects(rec3.getGlobalBounds()) == true ||
			bird.getGlobalBounds().intersects(rec4.getGlobalBounds()) == true &&
			lost == false || bird.getPosition().y > 550)
		{

			shape.move(0.00f, 0.0f);
			shape2.move(0.00f, 0.0f);
			shape3.move(0.00f, 0.0f);
			shape4.move(0.00f, 0.0f);

			rec1.move(0.00f, 0.0f);
			rec2.move(0.00f, 0.0f);
			rec3.move(0.00f, 0.0f);
			rec4.move(0.00f, 0.0f);

			coin_sprite.move(0.0f, 0.0f);
			if (gameover_is_played == false)
			{
				gameover_sfx.play();
				gameover_is_played = true;
			}

			bestFromFile = gameOver(score);
			bstScore.str("");

			bstScore << bestFromFile;
			txtbestScore.setString(bstScore.str());

			if (numberOfCoins >= 10)
			{
				while (!yesNO)
				{
					AskQuestion();
					if (yesNO)
					{
						if (Q_ans == 1)
						{
							float newposx1, newposx2, newposx3, newposx4;
							float newposy1, newposy2, newposy3, newposy4;
							float newposy11, newposy22, newposy33, newposy44;
							float  new_transparent1x, new_transparent2x, new_transparent3x, new_transparent4x;
							float  new_transparent1y, new_transparent2y, new_transparent3y, new_transparent4y;
							//float new_bird_y_position;

							newposx1 = shape.getPosition().x + 160;
							newposx2 = shape2.getPosition().x + 160;
							newposx3 = shape3.getPosition().x + 160;
							newposx4 = shape4.getPosition().x + 160;
							newposy1 = shape.getPosition().y;
							newposy2 = shape2.getPosition().y;
							newposy3 = shape3.getPosition().y;
							newposy4 = shape4.getPosition().y;
							newposy11 = rec1.getPosition().y;
							newposy22 = rec2.getPosition().y;
							newposy33 = rec3.getPosition().y;
							newposy44 = rec4.getPosition().y;
							new_transparent1x = transparent1.getPosition().x + 160;
							new_transparent2x = transparent2.getPosition().x + 160;
							new_transparent3x = transparent3.getPosition().x + 160;
							new_transparent4x = transparent4.getPosition().x + 160;
							new_transparent1y = transparent1.getPosition().y;
							new_transparent2y = transparent2.getPosition().y;
							new_transparent3y = transparent3.getPosition().y;
							new_transparent4y = transparent4.getPosition().y;
							//new_bird_y_position = bird.getPosition()

							shape.setPosition(newposx1, newposy1);
							rec1.setPosition(newposx1, newposy11);
							shape2.setPosition(newposx2, newposy2);
							rec2.setPosition(newposx2, newposy22);
							shape3.setPosition(newposx3, newposy3);
							rec3.setPosition(newposx3, newposy33);
							shape4.setPosition(newposx4, newposy4);
							rec4.setPosition(newposx4, newposy44);
							transparent1.setPosition(new_transparent1x, new_transparent1y);
							transparent2.setPosition(new_transparent2x, new_transparent2y);
							transparent3.setPosition(new_transparent3x, new_transparent3y);
							transparent4.setPosition(new_transparent4x, new_transparent4y);

							bird.setPosition(280, 300);
							ifstream in("YourCoins.txt");
							ofstream out("YourCoins.txt");
							numberOfCoins -= 10;
							in >> numberOfCoins;
							out << numberOfCoins;
							coins.str("");
							coins << numberOfCoins;
							coinsText.setString(coins.str());
							COIN_X_POSITION = coin_sprite.getPosition().x;
							coin_sprite.setPosition(COIN_X_POSITION, -100.0f);
							IncCoins();

							is_text_appeared = gameover_is_played = false;
						}
						else if (Q_ans == 0)
						{
							NoContinue = lost = true;
							window.clear();
							break;
							coinsBoard_sprite.setPosition(700.0f, 700.0f);
							no.setPosition(700.0f, 700.0f);
							yes.setPosition(700.0f, 700.0f);
							question.setPosition(700.0f, 700.0f);
							decCoins.setPosition(700.0f, 700.0f);
							yesNO = true;
						}
					}
				}
			}
			else
			{
				lost = NoContinue = true;
			}

			window.clear();
		}

		//if (Q_ans == 1)
			//yesNO = false;

		if (shape.getPosition().x + shape.getSize().x < 0)
		{
			int a = 0;
			int x = 0;
			RandomizePosition(x, a);
			shape.setPosition(1040, -a);
			rec1.setPosition(1040, x);
			coin_sprite.setPosition(1030, x - 110);

			transparent1.setPosition(1075, -a + 550);
			collision1 = false;
		}
		if (shape2.getPosition().x + shape.getSize().x < 0)
		{
			int a = 0;
			int x = 0;
			RandomizePosition(x, a);
			shape2.setPosition(1040, -a);
			rec2.setPosition(1040, x);

			transparent2.setPosition(1075, -a + 550);
			collision2 = false;
		}
		if (shape3.getPosition().x + shape.getSize().x < 0)
		{
			int a = 0;
			int x = 0;
			RandomizePosition(x, a);
			shape3.setPosition(1040, -a);
			rec3.setPosition(1040, x);

			transparent3.setPosition(1075, -a + 550);
			collision3 = false;
		}
		if (shape4.getPosition().x + shape.getSize().x < 0)
		{
			int a = 0;
			int x = 0;
			RandomizePosition(x, a);
			shape4.setPosition(1040, -a);
			rec4.setPosition(1040, x);

			transparent4.setPosition(1075, -a + 550);
			collision4 = false;
		}
		// pipes movement
		if (lost == false && is_text_appeared == true)
		{
			shape.move(pipes, 0.0f);
			shape2.move(pipes, 0.0f);
			shape3.move(pipes, 0.0f);
			shape4.move(pipes, 0.0f);

			rec1.move(pipes, 0.0f);
			rec2.move(pipes, 0.0f);
			rec3.move(pipes, 0.0f);
			rec4.move(pipes, 0.0f);

			transparent1.move(pipes, 0);
			transparent2.move(pipes, 0);
			transparent3.move(pipes, 0);
			transparent4.move(pipes, 0);


			coin_sprite.move(pipes, 0.0f);

		}
		//counting number of coins
		if (bird.getGlobalBounds().intersects(coin_sprite.getGlobalBounds()) == true)
		{

			coin_sfx.play();
			numberOfCoins++;
			coins.str("");
			coins << numberOfCoins;
			coinsText.setString(coins.str());
			COIN_X_POSITION = coin_sprite.getPosition().x;
			coin_sprite.setPosition(COIN_X_POSITION, -100.0f);
			IncCoins();
		}

		// counting score
		if (bird.getGlobalBounds().intersects(transparent1.getGlobalBounds()) == true && collision1 == false)
		{
			collision1 = true;
			score++;
			ssScore.str("");
			ssScore << score;
			txtscore.setString(ssScore.str());

			ccScore.str("");
			ccScore << score;
			txtCurrentScore.setString(ccScore.str());

		}
		if (bird.getGlobalBounds().intersects(transparent2.getGlobalBounds()) && !collision2)
		{
			collision2 = true;
			score++;
			ssScore.str("");
			ssScore << score;
			txtscore.setString(ssScore.str());

			ccScore.str("");
			ccScore << score;
			txtCurrentScore.setString(ccScore.str());

		}
		if (bird.getGlobalBounds().intersects(transparent3.getGlobalBounds()) && !collision3)
		{
			collision3 = true;
			score++;
			ssScore.str("");
			ssScore << score;
			txtscore.setString(ssScore.str());
			ccScore.str("");
			ccScore << score;
			txtCurrentScore.setString(ccScore.str());

		}
		if (bird.getGlobalBounds().intersects(transparent4.getGlobalBounds()) && !collision4)
		{
			collision4 = true;
			score++;
			ssScore.str("");
			ssScore << score;
			txtscore.setString(ssScore.str());
			ccScore.str("");
			ccScore << score;
			txtCurrentScore.setString(ccScore.str());

		}

		/*
		if (collision1 == true && lost == false)
		{
		shape.move(0.0, 0.003f);
		rec1.move(0.0, -0.003f);
		}
		if (collision2 == true && lost == false)
		{
		shape2.move(0.0, 0.003f);
		rec2.move(0.0, -0.003f);
		}if (collision3 == true && lost == false)
		{
		shape3.move(0.0, 0.003f);
		rec3.move(0.0, -0.003f);
		}if (collision4 == true && lost == false)
		{
		shape4.move(0.0, 0.003f);
		rec4.move(0.0, -0.003f);
		}
		*/
		// bird's movement
		if (Keyboard::isKeyPressed(Keyboard::Key::Space) && !movement && !lost)
		{
			bird.move(0.0f, jump);
			movement = true;

			velo = 0;
		}
		else { movement = false; }
		//  anitmation for the bird
		if (!lost)
		{
			if (decide == 1)
			{
				if (cnt % 50 == 0)
				{
					i++;
					if (i > 3) { i = 0; }
				}
				if (cnt > 50) { cnt = 1; }
				bird.setTexture(&originalanimation[i]);
				cnt++;
			}
			else if (decide == 2)
			{
				if (cnt % 70 == 0)
				{
					i++;
					if (i > 3) { i = 0; }
				}
				if (cnt > 70) { cnt = 1; }
				bird.setTexture(&yellowanimation[i]);
				cnt++;
			}
			else if (decide == 3)
			{
				if (cnt % 70 == 0)
				{
					i++;
					if (i > 2) { i = 0; }
				}
				if (cnt > 70) { cnt = 1; }
				bird.setTexture(&blueanimation[i]);
				cnt++;
			}
			else if (decide == 4)
			{
				if (cnt % 80 == 0)
				{
					i++;
					if (i > 1) { i = 0; }
				}
				if (cnt > 80) { cnt = 1; }
				bird.setTexture(&nesranimation[i]);
				cnt++;
			}
		}
		// gravity
		if (movement == false && lost == false && is_text_appeared)
		{

			bird.move(0.0f, gravity);

			velo = velo + 0.01;
			if (velo <= 60)
				bird.setRotation(velo);
		}

		window.clear();
		window.draw(background_sprite);
		window.draw(transparent1);
		window.draw(transparent2);
		window.draw(transparent3);
		window.draw(transparent4);
		window.draw(bird);
		window.draw(rec1);
		window.draw(rec2);
		window.draw(rec3);
		window.draw(rec4);
		window.draw(shape);
		window.draw(shape2);
		window.draw(shape3);
		window.draw(shape4);
		window.draw(coin_sprite);
		window.draw(how_to_play);
		window.draw(upperCoin_sprite);
		window.draw(coinsText);
		window.draw(txtscore);
		window.draw(pause_icon);




		if (lost && NoContinue) {
			//medals
			window.draw(game_over_sprite);
			window.draw(txtCurrentScore);
			window.draw(txtbestScore);
			if (score >= 0 && score < 20)
				window.draw(bronze_sprite);
			if (score >= 20 && score < 30)
				window.draw(silver_sprite);
			if (score >= 30)
				window.draw(gold_sprite);


			restart_icon.setPosition(70.0f, 450.0f);
			exit_icon.setPosition(320, 450);
			window.draw(restart_icon);
			window.draw(exit_icon);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				mousepos = Mouse::getPosition(window);
				if (mousepos.x >= 70 && mousepos.x <= 290 && mousepos.y >= 450 && mousepos.y <= 550)
				{
					window.clear();
					lost = yesNO = false;

					return main();
				}
				if (mousepos.x >= 320 && mousepos.x <= 540 && mousepos.y >= 450 && mousepos.y <= 550)
				{
					window.close();
				}


			}

		}

		window.display();


	}

	return 0;

}