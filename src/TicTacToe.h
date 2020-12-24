#define CALC_LINE_POS(i) ((i + 1) * gameBoard.TILE_SIZE + 50 * i)

struct Board
{
	const int GAMEBOARD_SIZE = 1300;
	const float DIAGONAL = 1838.47;
	const int TILE_SIZE = 400;
	const int LINE_THICKNESS = 50;
	const sf::Color TILE_COLOUR = sf::Color(128, 128, 128);
};

struct Position
{
	float x_pos;
	float y_pos;
	Position(float x, float y) :
		x_pos(x),
		y_pos(y)
	{}
};

struct GameData
{
	int turn = 0;
	int moveCnt = 0;
	bool change = false;
	bool gameOver = false;
};

class TicTacToe
{
public:
	TicTacToe(sf::RenderWindow& window);
	void setupBoard();
	void makeMove(const int x, const int y);
	void refreshBoard();
	bool isGameOver();

private:
	GameData gameData;
	const Board gameBoard;
	sf::RenderWindow* gameWindow;
	std::vector<sf::RectangleShape&> tiles;
	std::vector<sf::RectangleShape&> board;

	void drawTiles();
	void drawBoard();
	void checkWinner();
	void drawWinner();
	void drawLine(const Position& pos, const float h, const float w);
};
