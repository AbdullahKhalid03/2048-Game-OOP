#include "Board.h"
#include "Tile.h"
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>


Board::Board() {
	score = 0;
	highScore = 0;
	reset = false;
	gridSize = 2;
	srand(static_cast<unsigned int>(time(0)));

	// Initialize grid with nullptrs
	grid.resize(gridSize);
	for (int i = 0; i < gridSize; i++) {
		grid[i].resize(gridSize, nullptr);
	}
}

Board::Board(int currlevel) {
	score = 0;
	highScore = 0;
	reset = false;
	gridSize = currlevel;
	srand(static_cast<unsigned int>(time(0)));

	// Initialize grid with nullptrs
	grid.resize(gridSize);
	for (int i = 0; i < gridSize; i++) {
		grid[i].resize(gridSize, nullptr);
	}
}

Board::~Board() {
	for (int r = 0; r < grid.size(); r++) {
		for (int c = 0; c < grid[r].size(); c++) {
			if (grid[r][c] != nullptr) {
				delete grid[r][c];
				grid[r][c] = nullptr;
			}
		}
	}
}

std::vector<std::vector<Tile*>>& Board::getGrid() {
	return grid;
}

Tile* Board::getTile(int row, int col) const {
	if (row >= 0 && row < gridSize && col >= 0 && col < gridSize)
		return grid[row][col];
	else
		return nullptr;
}

void Board::finalizeMerges() {
	for (int r = 0; r < getGridSize(); ++r) {
		for (int c = 0; c < getGridSize(); ++c) {
			Tile* tile = grid[r][c];
			if (tile && tile->get_should_merge()) {
				tile->set_tile_number(tile->get_tile_number() * 2);
				tile->set_should_merge(false);
				tile->set_merged(true);
				ScoreOnBoard(tile->get_tile_number());
				ALLEGRO_BITMAP* newImage = getTileBitmap(tile->get_tile_number());
				tile->set_tile_image(newImage);
			}
		}
	}
}
int Board::getGridSize()const { return gridSize; }
void Board::setGridSize(int s) { gridSize = s; }

//Getter Functions
int Board::get_highScore()const { return highScore; }
int Board::get_score()const { return score; }
bool Board::get_reset()const { return reset; }

ALLEGRO_BITMAP* Board::getTileBitmap(int value) {
	auto it = tileImages.find(value);
	if (it != tileImages.end()) {
		return it->second;
	}
	if (!tileImages.empty()) {
		return tileImages.begin()->second;
	}

	return nullptr;
}

//Setter Functions
void Board::ScoreOnBoard(int s) { score += s; if (score > highScore) { highScore = score; } }
void Board::set_reset(bool v) { reset = v; }
void Board::addTile(int num, int row, int col) {
	if (row >= 0 && row < getGridSize() && col >= 0 && col < getGridSize()) {
		if (grid[row][col] == nullptr) {
			grid[row][col] = new Tile(num, row, col, tileImages[num]);
		}
	}
}
void Board::resetScore() {
	score = 0;
}
void Board::initialize(ALLEGRO_BITMAP* tileImgs[]) {
	int values[] = { 2, 4, 8, 16, 32, 64, 128, 256, 514, 1024, 2048 };
	for (int i = 0; i < 11; i++) {
		tileImages[values[i]] = tileImgs[i];
	}
}
void Board::drawBoard(const Animation* animation) {
	for (int r = 0; r < getGridSize(); r++) {
		for (int c = 0; c < getGridSize(); c++) {
			if (grid[r][c] != nullptr) {
				// Skip tiles that are being animated
				bool skip = false;
				if (animation && animation->isActive()) {
					for (const auto& anim : animation->getAnimatingTiles()) {
						if (anim.tile == grid[r][c]) {
							skip = true;
							break;
						}
					}
				}

				if (!skip) {
					int x = c * 70;
					int y = 100 + r * 70;
					al_draw_bitmap(grid[r][c]->get_tile_image(), x, y, 0);
				}
			}
		}
	}
}
void Board::moveTile(int fromRow, int fromCol, int toRow, int toCol) {
	if (fromRow < 0 || fromRow >= getGridSize() || fromCol < 0 || fromCol >= getGridSize() ||
		toRow < 0 || toRow >= getGridSize() || toCol < 0 || toCol >= getGridSize()) {
		return;
	}

	if (grid[fromRow][fromCol] != nullptr && grid[toRow][toCol] == nullptr) {
		grid[toRow][toCol] = grid[fromRow][fromCol];
		grid[toRow][toCol]->set_position(toRow, toCol);
		grid[fromRow][fromCol] = nullptr;
	}
}
void Board::clearTile(int row, int col) {
	if (grid[row][col] != nullptr) {
		delete grid[row][col];
		grid[row][col] = nullptr;
	}
}


void Board::generateRandomTile() {
	std::vector<std::pair<int, int>>emptyCells;
	for (int i = 0; i < getGridSize(); i++) {
		for (int j = 0; j < getGridSize(); j++) {
			if (grid[i][j] == nullptr) {
				emptyCells.push_back({ i,j });
			}
		}
	}
	if (emptyCells.empty()) { return; }

	int ran = rand() % emptyCells.size();

	std::pair<int, int> position = emptyCells[ran];
	int row = position.first;
	int col = position.second;

	int probability;
	if (rand() % 10 == 0) { probability = 4; }
	else { probability = 2; }

	addTile(probability, row, col);
}

bool Board::isEmpty() const {
	for (int i = 0; i < getGridSize(); i++) {
		for (int j = 0; j < getGridSize(); j++) {
			if (grid[i][j] == nullptr) {
				return true;
			}
		}
	}
	return false;
}


bool Board::isGameOver() const {
	// If there are empty spaces, game isn't over
	if (isEmpty()) return false;

	for (int r = 0; r < getGridSize(); ++r) {
		for (int c = 0; c < getGridSize(); ++c) {
			Tile* current = grid[r][c];
			if (!current) continue;

			// Check right neighbor
			if (c + 1 < getGridSize() && grid[r][c + 1] &&
				grid[r][c + 1]->get_tile_number() == current->get_tile_number()) {
				return false;
			}

			// Check down neighbor
			if (r + 1 < getGridSize() && grid[r + 1][c] &&
				grid[r + 1][c]->get_tile_number() == current->get_tile_number()) {
				return false;
			}

			// Check left neighbor
			if (c - 1 >= 0 && grid[r][c - 1] &&
				grid[r][c - 1]->get_tile_number() == current->get_tile_number()) {
				return false;
			}

			// Check up neighbor
			if (r - 1 >= 0 && grid[r - 1][c] &&
				grid[r - 1][c]->get_tile_number() == current->get_tile_number()) {
				return false;
			}
		}
	}

	// If no possible moves found, game is over
	return true;
}
