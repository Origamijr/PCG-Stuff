#include <vector>
#include <array>
#include <queue>
#include <time.h>
#include <stack>

using namespace std;
//using namespace physx;

class MazeCube {
public:
	static pair<vector<array<float, 3>>, char***> generateMazeCube(int size) {
		if (size < 2) return make_pair(vector<array<float, 3>>(), nullptr);

		size = 2 * size - 1;

		// This commented section can be used to make the runtime O(n^2), but then it would take much more code
		/*int** latSurface = new int*[size];
		for (int i = 0; i < size; i++) {
			latSurface[i] = new int[4 * (size - 1)];
		}

		int** topSurface = new int*[size - 2];
		for (int i = 0; i < size; i++) {
			topSurface[i] = new int[size - 2];
		}

		int** botSurface = new int*[size - 2];
		for (int i = 0; i < size; i++) {
			topSurface[i] = new int[size - 2];
		}*/
		srand((unsigned)time(0));

		// Initiallize and setup cube for maze generation
		char*** cube = new char**[size];
		for (int i = 0; i < size; i++) {
			cube[i] = new char*[size];
			for (int j = 0; j < size; j++) {
				cube[i][j] = new char[size];
				for (int k = 0; k < size; k++) {
					if ((i == 0 || j == 0 || k == 0 || i == size - 1
						|| j == size - 1 || k == size - 1)
						&& (i % 2 == 0 && j % 2 == 0 && k % 2 == 0)) {
						cube[i][j][k] = 1;
					} else {
						cube[i][j][k] = rand() % (CHAR_MAX - 1) + 2;
					}
				}
			}
		}

		// Setup for iteration of prim's algorithm
		priority_queue<pair<char, array<int, 3>>> q = priority_queue<pair<char, array<int, 3>>>();

		cube[0][0][0] = 0;
		array<int, 3> arr1{ { 1, 0, 0 } };
		array<int, 3> arr2{ { 0, 1, 0 } };
		array<int, 3> arr3{ { 0, 0, 1 } };
		q.push(make_pair(cube[1][0][0], arr1));
		q.push(make_pair(cube[0][1][0], arr2));
		q.push(make_pair(cube[0][0][1], arr3));

		while (!q.empty()) {

			// Look at the top(greatest) element
			auto edge = q.top();
			q.pop();

			int x = edge.second[0];
			int y = edge.second[1];
			int z = edge.second[2];

			// Check if node is visited, and find direction of edge
			if (x > 0 && cube[x - 1][y][z] == 1) x--;
			else if (x < size - 1 && cube[x + 1][y][z] == 1) x++;
			else if (y > 0 && cube[x][y - 1][z] == 1) y--;
			else if (y < size - 1 && cube[x][y + 1][z] == 1) y++;
			else if (z > 0 && cube[x][y][z - 1] == 1) z--;
			else if (z < size - 1 && cube[x][y][z + 1] == 1) z++;
			else continue;

			//cout << x << " " << y << " " << z << ":" << (int)cube[x][y][z] << endl;

			// Set the edge to visited
			cube[edge.second[0]][edge.second[1]][edge.second[2]] = 0;
			cube[x][y][z] = 0;

			// Push neighbors
			if (x > 1 && cube[x - 2][y][z] == 1) {
				array<int, 3> arr{ {x - 1, y, z} };
				q.push(make_pair(cube[x - 1][y][z], arr));
			}
			if (x < size - 2 && cube[x + 2][y][z] == 1) {
				array<int, 3> arr{ { x + 1, y, z } };
				q.push(make_pair(cube[x + 1][y][z], arr));
			}
			if (y > 1 && cube[x][y - 2][z] == 1) {
				array<int, 3> arr{ { x, y - 1, z } };
				q.push(make_pair(cube[x][y - 1][z], arr));
			}
			if (y < size - 2 && cube[x][y + 2][z] == 1) {
				array<int, 3> arr{ { x, y + 1, z } };
				q.push(make_pair(cube[x][y + 1][z], arr));
			}
			if (z > 1 && cube[x][y][z - 2] == 1) {
				array<int, 3> arr{ { x, y, z - 1 } };
				q.push(make_pair(cube[x][y][z - 1], arr));
			}
			if (z < size - 2 && cube[x][y][z + 2] == 1) {
				array<int, 3> arr{ { x, y, z + 1 } };
				q.push(make_pair(cube[x][y][z + 1], arr));
			}
		}

		// Load walls
		vector<array<float, 3>> positions = vector<array<float, 3>>();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size; k++) {
					if ((i == 0 || j == 0 || k == 0 || i == size - 1
						|| j == size - 1 || k == size - 1) && cube[i][j][k] > 1) {
						array<float, 3> arr{ {(float)i, (float)j, (float)k} };
						positions.push_back(arr);
					}
				}
			}
		}

		return make_pair(positions, cube);
	}





	static pair<vector<array<float, 3>>, char***> generateAltMazeCube(int size) {
		if (size < 2) return make_pair(vector<array<float, 3>>(), nullptr);

		srand((unsigned)time(0));

		// Initiallize and setup cube for maze generation
		char*** cube = new char**[size];
		for (int i = 0; i < size; i++) {
			cube[i] = new char*[size];
			for (int j = 0; j < size; j++) {
				cube[i][j] = new char[size];
				for (int k = 0; k < size; k++) {
					if ((i == 0 || j == 0 || k == 0 || i == size - 1
						|| j == size - 1 || k == size - 1)) {
						cube[i][j][k] = rand() % (CHAR_MAX - 2) + 3;
					} else {
						cube[i][j][k] = 2;
					}
				}
			}
		}
		\
		// Setup for iteration of prim's algorithm
		priority_queue<pair<char, array<int, 3>>> q = priority_queue<pair<char, array<int, 3>>>();

		cube[0][0][0] = 0;
		array<int, 3> arr1{ { 1, 0, 0 } };
		array<int, 3> arr2{ { 0, 1, 0 } };
		array<int, 3> arr3{ { 0, 0, 1 } };
		q.push(make_pair(cube[1][0][0], arr1));
		q.push(make_pair(cube[0][1][0], arr2));
		q.push(make_pair(cube[0][0][1], arr3));

		while (!q.empty()) {

			// Look at the top(greatest) element
			auto edge = q.top();
			q.pop();

			int x = edge.second[0];
			int y = edge.second[1];
			int z = edge.second[2];

			// Check if pixel creates a loop
			int count = 0;
			if (x > 0 && cube[x - 1][y][z] == 0) count++;
			if (x < size - 1 && cube[x + 1][y][z] == 0) count++;
			if (y > 0 && cube[x][y - 1][z] == 0) count++;
			if (y < size - 1 && cube[x][y + 1][z] == 0) count++;
			if (z > 0 && cube[x][y][z - 1] == 0) count++;
			if (z < size - 1 && cube[x][y][z + 1] == 0) count++;

			if (count > 1) continue;

			// Set pixel to visited
			cube[x][y][z] = 0;

			// Push neighbors
			if (x > 0 && cube[x - 1][y][z] > 2) {
				array<int, 3> arr{ { x - 1, y, z } };
				q.push(make_pair(cube[x - 1][y][z], arr));
			}
			if (x < size - 1 && cube[x + 1][y][z] > 2) {
				array<int, 3> arr{ { x + 1, y, z } };
				q.push(make_pair(cube[x + 1][y][z], arr));
			}
			if (y > 0 && cube[x][y - 1][z] > 2) {
				array<int, 3> arr{ { x, y - 1, z } };
				q.push(make_pair(cube[x][y - 1][z], arr));
			}
			if (y < size - 1 && cube[x][y + 1][z] > 2) {
				array<int, 3> arr{ { x, y + 1, z } };
				q.push(make_pair(cube[x][y + 1][z], arr));
			}
			if (z > 0 && cube[x][y][z - 1] > 2) {
				array<int, 3> arr{ { x, y, z - 1 } };
				q.push(make_pair(cube[x][y][z - 1], arr));
			}
			if (z < size - 1 && cube[x][y][z + 1] > 2) {
				array<int, 3> arr{ { x, y, z + 1 } };
				q.push(make_pair(cube[x][y][z + 1], arr));
			}
		}

		// Load walls
		vector<array<float, 3>> positions = vector<array<float, 3>>();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size; k++) {
					if ((i == 0 || j == 0 || k == 0 || i == size - 1
						|| j == size - 1 || k == size - 1) && cube[i][j][k] > 1) {
						array<float, 3> arr{ { (float)i, (float)j, (float)k } };
						positions.push_back(arr);
					}
				}
			}
		}

		return make_pair(positions, cube);
	}





	static pair<vector<array<float, 3>>, char***> generateAltMazeCube2(int size) {
		if (size < 2) return make_pair(vector<array<float, 3>>(), nullptr);

		int cleanliness = 75;
		int straightener = 30;
		srand((unsigned)time(0));

		// Initiallize and setup cube for maze generation
		char*** cube = new char**[size];
		for (int i = 0; i < size; i++) {
			cube[i] = new char*[size];
			for (int j = 0; j < size; j++) {
				cube[i][j] = new char[size];
				for (int k = 0; k < size; k++) {
					if ((i == 0 || j == 0 || k == 0 || i == size - 1
						|| j == size - 1 || k == size - 1)) {
						cube[i][j][k] = rand() % (CHAR_MAX - 2) + 3;
					} else {
						cube[i][j][k] = 2;
					}
				}
			}
		}



		// Setup for iteration of prim's algorithm
		priority_queue<pair<char, array<int, 3>>> q = priority_queue<pair<char, array<int, 3>>>();

		cube[0][0][0] = 0;
		array<int, 3> arr1{ { 1, 0, 0 } };
		array<int, 3> arr2{ { 0, 1, 0 } };
		array<int, 3> arr3{ { 0, 0, 1 } };
		q.push(make_pair(cube[1][0][0], arr1));
		q.push(make_pair(cube[0][1][0], arr2));
		q.push(make_pair(cube[0][0][1], arr3));

		while (!q.empty()) {

			// Look at the top(greatest) element
			auto edge = q.top();
			q.pop();

			int x = edge.second[0];
			int y = edge.second[1];
			int z = edge.second[2];

			// Check if pixel creates a loop
			int direction = 1;
			if (x > 0 && cube[x - 1][y][z] == 0) direction *= 10;
			if (x < size - 1 && cube[x + 1][y][z] == 0) direction *= 60;
			if (y > 0 && cube[x][y - 1][z] == 0) direction *= 20;
			if (y < size - 1 && cube[x][y + 1][z] == 0) direction *= 50;
			if (z > 0 && cube[x][y][z - 1] == 0) direction *= 30;
			if (z < size - 1 && cube[x][y][z + 1] == 0) direction *= 40;

			if (direction > 60) continue;

			//cout << x << " " << y << " " << z << ":" << (int)cube[x][y][z] << endl;

			// Set pixel to visited
			cube[x][y][z] = 0;

			// Push neighbors, while adjusting weights so that straight is encouraged
			if (x > 0 && cube[x - 1][y][z] > 2) {
				array<int, 3> arr{ { x - 1, y, z } };
				if (direction == 60) cube[x - 1][y][z] = (cube[x - 1][y][z] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x - 1][y][z] + straightener;
				q.push(make_pair(cube[x - 1][y][z], arr));
			}
			if (x < size - 1 && cube[x + 1][y][z] > 2) {
				array<int, 3> arr{ { x + 1, y, z } };
				if (direction == 10) cube[x + 1][y][z] = (cube[x + 1][y][z] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x + 1][y][z] + straightener;
				q.push(make_pair(cube[x + 1][y][z], arr));
			}
			if (y > 0 && cube[x][y - 1][z] > 2) {
				array<int, 3> arr{ { x, y - 1, z } };
				if (direction == 50) cube[x][y - 1][z] = (cube[x][y - 1][z] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x][y - 1][z] + straightener;
				q.push(make_pair(cube[x][y - 1][z], arr));
			}
			if (y < size - 1 && cube[x][y + 1][z] > 2) {
				array<int, 3> arr{ { x, y + 1, z } };
				if (direction == 20) cube[x][y + 1][z] = (cube[x][y + 1][z] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x][y + 1][z] + straightener;
				q.push(make_pair(cube[x][y + 1][z], arr));
			}
			if (z > 0 && cube[x][y][z - 1] > 2) {
				array<int, 3> arr{ { x, y, z - 1 } };
				if (direction == 40) cube[x][y][z - 1] = (cube[x][y][z - 1] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x][y][z - 1] + straightener;
				q.push(make_pair(cube[x][y][z - 1], arr));
			}
			if (z < size - 1 && cube[x][y][z + 1] > 2) {
				array<int, 3> arr{ { x, y, z + 1 } };
				if (direction == 30) cube[x][y][z + 1] = (cube[x][y][z + 1] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x][y][z + 1] + straightener;
				q.push(make_pair(cube[x][y][z + 1], arr));
			}
		}

		// Clean up pointless dead ends
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				for (int z = 0; z < size; z++) {
					if ((x == 0 || y == 0 || z == 0 || x == size - 1
						|| y == size - 1 || z == size - 1) && cube[x][y][z] == 0) {

						int direction = 1;
						if (x > 0 && cube[x - 1][y][z] == 0) direction *= 10;
						if (x < size - 1 && cube[x + 1][y][z] == 0) direction *= 60;
						if (y > 0 && cube[x][y - 1][z] == 0) direction *= 20;
						if (y < size - 1 && cube[x][y + 1][z] == 0) direction *= 50;
						if (z > 0 && cube[x][y][z - 1] == 0) direction *= 30;
						if (z < size - 1 && cube[x][y][z + 1] == 0) direction *= 40;

						if (direction > 60) continue;

						if (rand() % 100 < cleanliness) {
							int count = 0;

							switch (direction) {
							case 10:
								if (y > 0 && cube[x - 1][y - 1][z] == 0) count++;
								if (y < size - 1 && cube[x - 1][y + 1][z] == 0) count++;
								if (z > 0 && cube[x - 1][y][z - 1] == 0) count++;
								if (z < size - 1 && cube[x - 1][y][z + 1] == 0) count++;

								break;
							case 60:
								if (y > 0 && cube[x + 1][y - 1][z] == 0) count++;
								if (y < size - 1 && cube[x + 1][y + 1][z] == 0) count++;
								if (z > 0 && cube[x + 1][y][z - 1] == 0) count++;
								if (z < size - 1 && cube[x + 1][y][z + 1] == 0) count++;

								break;
							case 20:
								if (x > 0 && cube[x - 1][y - 1][z] == 0) count++;
								if (x < size - 1 && cube[x + 1][y - 1][z] == 0) count++;
								if (z > 0 && cube[x][y - 1][z - 1] == 0) count++;
								if (z < size - 1 && cube[x][y - 1][z + 1] == 0) count++;

								break;
							case 50:
								if (x > 0 && cube[x - 1][y + 1][z] == 0) count++;
								if (x < size - 1 && cube[x + 1][y + 1][z] == 0) count++;
								if (z > 0 && cube[x][y + 1][z - 1] == 0) count++;
								if (z < size - 1 && cube[x][y + 1][z + 1] == 0) count++;

								break;
							case 30:
								if (x > 0 && cube[x - 1][y][z - 1] == 0) count++;
								if (x < size - 1 && cube[x + 1][y][z - 1] == 0) count++;
								if (y > 0 && cube[x][y - 1][z - 1] == 0) count++;
								if (y < size - 1 && cube[x][y + 1][z - 1] == 0) count++;

								break;
							case 40:
								if (x > 0 && cube[x - 1][y][z + 1] == 0) count++;
								if (x < size - 1 && cube[x + 1][y][z + 1] == 0) count++;
								if (y > 0 && cube[x][y - 1][z + 1] == 0) count++;
								if (y < size - 1 && cube[x][y + 1][z + 1] == 0) count++;

								break;
							default:
								break;
							}

							if (count > 1) cube[x][y][z] = 2;

						}

					}
				}
			}
		}

		// Load walls
		vector<array<float, 3>> positions = vector<array<float, 3>>();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size; k++) {
					if ((i == 0 || j == 0 || k == 0 || i == size - 1
						|| j == size - 1 || k == size - 1) && cube[i][j][k] > 1) {
						array<float, 3> arr{ { (float)i, (float)j, (float)k } };
						positions.push_back(arr);
					}
				}
			}
		}

		return make_pair(positions, cube);
	}





	static pair<vector<array<float, 3>>, char***> generateAltMazeCube3(int size) {
		if (size < 2) return make_pair(vector<array<float, 3>>(), nullptr);

		int loopiness = 15;
		int cleanliness = 75;
		int straightener = 30;
		srand((unsigned)time(0));

		// Initiallize and setup cube for maze generation
		char*** cube = new char**[size];
		for (int i = 0; i < size; i++) {
			cube[i] = new char*[size];
			for (int j = 0; j < size; j++) {
				cube[i][j] = new char[size];
				for (int k = 0; k < size; k++) {
					if ((i == 0 || j == 0 || k == 0 || i == size - 1
						|| j == size - 1 || k == size - 1)) {
						cube[i][j][k] = rand() % (CHAR_MAX - 2) + 3;
					} else {
						cube[i][j][k] = 2;
					}
				}
			}
		}

		// Setup for iteration of prim's algorithm
		priority_queue<pair<char, array<int, 3>>> q = priority_queue<pair<char, array<int, 3>>>();

		cube[0][0][0] = 0;
		array<int, 3> arr1{ { 1, 0, 0 } };
		array<int, 3> arr2{ { 0, 1, 0 } };
		array<int, 3> arr3{ { 0, 0, 1 } };
		q.push(make_pair(cube[1][0][0], arr1));
		q.push(make_pair(cube[0][1][0], arr2));
		q.push(make_pair(cube[0][0][1], arr3));

		while (!q.empty()) {

			// Look at the top(greatest) element
			auto edge = q.top();
			q.pop();

			int x = edge.second[0];
			int y = edge.second[1];
			int z = edge.second[2];

			// Check if pixel creates a loop
			int direction = 1;
			if (x > 0 && cube[x - 1][y][z] == 0) direction *= 10;
			if (x < size - 1 && cube[x + 1][y][z] == 0) direction *= 60;
			if (y > 0 && cube[x][y - 1][z] == 0) direction *= 20;
			if (y < size - 1 && cube[x][y + 1][z] == 0) direction *= 50;
			if (z > 0 && cube[x][y][z - 1] == 0) direction *= 30;
			if (z < size - 1 && cube[x][y][z + 1] == 0) direction *= 40;

			if (direction > 60 && rand() % 1000 > loopiness) continue;

			//cout << x << " " << y << " " << z << ":" << (int)cube[x][y][z] << endl;

			// Set pixel to visited
			cube[x][y][z] = 0;

			// Push neighbors, while adjusting weights so that straight is encouraged
			if (x > 0 && cube[x - 1][y][z] > 2) {
				array<int, 3> arr{ { x - 1, y, z } };
				if (direction == 60) cube[x - 1][y][z] = (cube[x - 1][y][z] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x - 1][y][z] + straightener;
				q.push(make_pair(cube[x - 1][y][z], arr));
			}
			if (x < size - 1 && cube[x + 1][y][z] > 2) {
				array<int, 3> arr{ { x + 1, y, z } };
				if (direction == 10) cube[x + 1][y][z] = (cube[x + 1][y][z] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x + 1][y][z] + straightener;
				q.push(make_pair(cube[x + 1][y][z], arr));
			}
			if (y > 0 && cube[x][y - 1][z] > 2) {
				array<int, 3> arr{ { x, y - 1, z } };
				if (direction == 50) cube[x][y - 1][z] = (cube[x][y - 1][z] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x][y - 1][z] + straightener;
				q.push(make_pair(cube[x][y - 1][z], arr));
			}
			if (y < size - 1 && cube[x][y + 1][z] > 2) {
				array<int, 3> arr{ { x, y + 1, z } };
				if (direction == 20) cube[x][y + 1][z] = (cube[x][y + 1][z] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x][y + 1][z] + straightener;
				q.push(make_pair(cube[x][y + 1][z], arr));
			}
			if (z > 0 && cube[x][y][z - 1] > 2) {
				array<int, 3> arr{ { x, y, z - 1 } };
				if (direction == 40) cube[x][y][z - 1] = (cube[x][y][z - 1] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x][y][z - 1] + straightener;
				q.push(make_pair(cube[x][y][z - 1], arr));
			}
			if (z < size - 1 && cube[x][y][z + 1] > 2) {
				array<int, 3> arr{ { x, y, z + 1 } };
				if (direction == 30) cube[x][y][z + 1] = (cube[x][y][z + 1] > CHAR_MAX - straightener) ? CHAR_MAX : cube[x][y][z + 1] + straightener;
				q.push(make_pair(cube[x][y][z + 1], arr));
			}
		}

		// Clean up pointless dead ends
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				for (int z = 0; z < size; z++) {
					if ((x == 0 || y == 0 || z == 0 || x == size - 1
						|| y == size - 1 || z == size - 1) && cube[x][y][z] == 0) {

						int direction = 1;
						if (x > 0 && cube[x - 1][y][z] == 0) direction *= 10;
						if (x < size - 1 && cube[x + 1][y][z] == 0) direction *= 60;
						if (y > 0 && cube[x][y - 1][z] == 0) direction *= 20;
						if (y < size - 1 && cube[x][y + 1][z] == 0) direction *= 50;
						if (z > 0 && cube[x][y][z - 1] == 0) direction *= 30;
						if (z < size - 1 && cube[x][y][z + 1] == 0) direction *= 40;

						if (direction > 60) continue;

						if (rand() % 100 < cleanliness) {
							int count = 0;

							switch (direction) {
							case 10:
								if (y > 0 && cube[x - 1][y - 1][z] == 0) count++;
								if (y < size - 1 && cube[x - 1][y + 1][z] == 0) count++;
								if (z > 0 && cube[x - 1][y][z - 1] == 0) count++;
								if (z < size - 1 && cube[x - 1][y][z + 1] == 0) count++;

								break;
							case 60:
								if (y > 0 && cube[x + 1][y - 1][z] == 0) count++;
								if (y < size - 1 && cube[x + 1][y + 1][z] == 0) count++;
								if (z > 0 && cube[x + 1][y][z - 1] == 0) count++;
								if (z < size - 1 && cube[x + 1][y][z + 1] == 0) count++;

								break;
							case 20:
								if (x > 0 && cube[x - 1][y - 1][z] == 0) count++;
								if (x < size - 1 && cube[x + 1][y - 1][z] == 0) count++;
								if (z > 0 && cube[x][y - 1][z - 1] == 0) count++;
								if (z < size - 1 && cube[x][y - 1][z + 1] == 0) count++;

								break;
							case 50:
								if (x > 0 && cube[x - 1][y + 1][z] == 0) count++;
								if (x < size - 1 && cube[x + 1][y + 1][z] == 0) count++;
								if (z > 0 && cube[x][y + 1][z - 1] == 0) count++;
								if (z < size - 1 && cube[x][y + 1][z + 1] == 0) count++;

								break;
							case 30:
								if (x > 0 && cube[x - 1][y][z - 1] == 0) count++;
								if (x < size - 1 && cube[x + 1][y][z - 1] == 0) count++;
								if (y > 0 && cube[x][y - 1][z - 1] == 0) count++;
								if (y < size - 1 && cube[x][y + 1][z - 1] == 0) count++;

								break;
							case 40:
								if (x > 0 && cube[x - 1][y][z + 1] == 0) count++;
								if (x < size - 1 && cube[x + 1][y][z + 1] == 0) count++;
								if (y > 0 && cube[x][y - 1][z + 1] == 0) count++;
								if (y < size - 1 && cube[x][y + 1][z + 1] == 0) count++;

								break;
							default:
								break;
							}

							if (count > 1) cube[x][y][z] = 2;

						}

					}
				}
			}
		}

		// Load walls
		vector<array<float, 3>> positions = vector<array<float, 3>>();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size; k++) {
					if ((i == 0 || j == 0 || k == 0 || i == size - 1
						|| j == size - 1 || k == size - 1) && cube[i][j][k] > 1) {
						array<float, 3> arr{ { (float)i, (float)j, (float)k } };
						positions.push_back(arr);
					}
				}
			}
		}

		return make_pair(positions, cube);
	}




	

	static pair<array<float, 3>, array<float, 3>> cubeFindLongestPath(char*** srcCube, int size) {
		
		char*** cube = new char**[size];
		array<int, 3> bfsStart;

		int cells = 0;
		for (int i = 0; i < size; i++) {
			cube[i] = new char*[size];
			for (int j = 0; j < size; j++) {
				cube[i][j] = new char[size];
				for (int k = 0; k < size; k++) {
					if (srcCube[i][j][k] == 0 || srcCube[i][j][k] == 1) {
						cube[i][j][k] = 0;
						cells++;
						bfsStart = { i, j, k };
					} else {
						cube[i][j][k] = CHAR_MAX;
					}
				}
			}
		}

		queue<array<int, 3>> q = queue<array<int, 3>>();
		vector<array<float, 3>> ret = vector<array<float, 3>>();

		q.push(bfsStart);
		array<int, 3> start;

		while (!q.empty()) {
			
			start = q.front();
			q.pop();

			int x = start[0];
			int y = start[1];
			int z = start[2];

			array<float, 3> arr{ {(float)x, (float)y, (float)z} };
			ret.push_back(arr);

			cube[x][y][z] = 1;

			//cout << "Phase 1: " << x << "," << y << "," << z << " : " << cells-- << " : " << (int)q.size() << endl;

			// Push neighbors
			if (x > 0 && cube[x - 1][y][z] == 0) {
				array<int, 3> arr{ { x - 1, y, z } };
				//cout << "push-x" << endl;
				q.push(arr);
			}
			if (x < size - 1 && cube[x + 1][y][z] == 0) {
				array<int, 3> arr{ { x + 1, y, z } };
				//cout << "push+x" << endl;
				q.push(arr);
			}
			if (y > 0 && cube[x][y - 1][z] == 0) {
				array<int, 3> arr{ { x, y - 1, z } };
				//cout << "push-y" << endl;
				q.push(arr);
			}
			if (y < size - 1 && cube[x][y + 1][z] == 0) {
				array<int, 3> arr{ { x, y + 1, z } };
				//cout << "push+y" << endl;
				q.push(arr);
			}
			if (z > 0 && cube[x][y][z - 1] == 0) {
				array<int, 3> arr{ { x, y, z - 1 } };
				//cout << "push-z" << endl;
				q.push(arr);
			}
			if (z < size - 1 && cube[x][y][z + 1] == 0) {
				array<int, 3> arr{ { x, y, z + 1 } };
				//cout << "push+z" << endl;
				q.push(arr);
			}
		}

		// Reset and BFS again
		cells = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = 0; k < size; k++) {
					if (srcCube[i][j][k] == 0 || srcCube[i][j][k] == 1) {
						cube[i][j][k] = 0;
						cells++;
					} else {
						cube[i][j][k] = CHAR_MAX;
					}
				}
			}
		}

		q.push(start);
		array<int, 3> end;

		while (!q.empty()) {
			
			end = q.front();
			q.pop();

			int x = end[0];
			int y = end[1];
			int z = end[2];

			cube[x][y][z] = 1;
			
			//cout << "Phase 2: " << x << "," << y << "," << z << " : " << cells-- << " : " << (int)q.size() << endl;

			// Push neighbors
			if (x > 0 && cube[x - 1][y][z] == 0) {
				array<int, 3> arr{ { x - 1, y, z } };
				//cout << "push-x" << endl;
				q.push(arr);
			}
			if (x < size - 1 && cube[x + 1][y][z] == 0) {
				array<int, 3> arr{ { x + 1, y, z } };
				//cout << "push+x" << endl;
				q.push(arr);
			}
			if (y > 0 && cube[x][y - 1][z] == 0) {
				array<int, 3> arr{ { x, y - 1, z } };
				//cout << "push-y" << endl;
				q.push(arr);
			}
			if (y < size - 1 && cube[x][y + 1][z] == 0) {
				array<int, 3> arr{ { x, y + 1, z } };
				//cout << "push+y" << endl;
				q.push(arr);
			}
			if (z > 0 && cube[x][y][z - 1] == 0) {
				array<int, 3> arr{ { x, y, z - 1 } };
				//cout << "push-z" << endl;
				q.push(arr);
			}
			if (z < size - 1 && cube[x][y][z + 1] == 0) {
				array<int, 3> arr{ { x, y, z + 1 } };
				//cout << "push+z" << endl;
				q.push(arr);
			}
		}

		array<float, 3> fstart{ {(float)start[0], (float)start[1], (float)start[2]} };
		array<float, 3> fend{ { (float)end[0], (float)end[1], (float)end[2] } };
		
		//return ret;
		return make_pair(fstart, fend);
	}





	static vector<array<float, 3>> findPathInCube(char*** srcCube, int size, array<float, 3> start, array<float, 3> end) {

		char*** cube = new char**[size];
		
		for (int i = 0; i < size; i++) {
			cube[i] = new char*[size];
			for (int j = 0; j < size; j++) {
				cube[i][j] = new char[size];
				for (int k = 0; k < size; k++) {
					if (srcCube[i][j][k] == 0) {
						cube[i][j][k] = 0;
					} else {
						cube[i][j][k] = CHAR_MAX;
					}
				}
			}
		}

		stack<array<float, 3>> q = stack<array<float, 3>>();

		q.push(start);
		
		while (!q.empty()) {
			start = q.top();

			int x = (int)start[0];
			int y = (int)start[1];
			int z = (int)start[2];

			cube[x][y][z] = 1;

			//cout << "Pathing: " << x << "," << y << "," << z << endl;

			// Push and count neighbors
			int count = 0;
			array<float, 3> arr;
			if (x > 0 && cube[x - 1][y][z] == 0) {
				arr = { (float)x - 1, (float)y, (float)z };
				count++;
			}
			if (x < size - 1 && cube[x + 1][y][z] == 0) {
				arr = { (float)x + 1, (float)y, (float)z };
				count++;
			}
			if (y > 0 && cube[x][y - 1][z] == 0) {
				arr = { (float)x, (float)y - 1, (float)z };
				count++;
			}
			if (y < size - 1 && cube[x][y + 1][z] == 0) {
				arr = { (float)x, (float)y + 1, (float)z };
				count++;
			}
			if (z > 0 && cube[x][y][z - 1] == 0) {
				arr = { (float)x, (float)y, (float)z - 1 };
				count++;
			}
			if (z < size - 1 && cube[x][y][z + 1] == 0) {
				arr = { (float)x, (float)y, (float)z + 1 };
				count++;
			}

			if (count == 0) {
				q.pop();
			} else {
				q.push(arr);
				if (arr == end) {
					break;
				}
			}
			
		}

		vector<array<float, 3>> ret = vector<array<float, 3>>();

		while (!q.empty()) {
			array<float, 3> arr{ { (float)q.top()[0], (float)q.top()[1], (float)q.top()[2]} };
			ret.push_back(arr);
			q.pop();
		}

		return ret;
	}
};