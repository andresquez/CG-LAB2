#include <SDL2/SDL.h>

const int CELL_SIZE = 8;  // Tamaño de cada célula
const int FRAMEBUFFER_WIDTH = 100;
const int FRAMEBUFFER_HEIGHT = 100;
const int WINDOW_WIDTH = FRAMEBUFFER_WIDTH * CELL_SIZE;
const int WINDOW_HEIGHT = FRAMEBUFFER_HEIGHT * CELL_SIZE;

bool cells[FRAMEBUFFER_WIDTH][FRAMEBUFFER_HEIGHT] = {false};

// Obtener las coordenadas válidas considerando el "loop" toroidal
void getValidCoordinates(int& x, int& y) {
    if (x < 0) {
        x = FRAMEBUFFER_WIDTH - 1;
    } else if (x >= FRAMEBUFFER_WIDTH) {
        x = 0;
    }

    if (y < 0) {
        y = FRAMEBUFFER_HEIGHT - 1;
    } else if (y >= FRAMEBUFFER_HEIGHT) {
        y = 0;
    }
}

void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 139, 115, 245, 255); // Color blanco

    // Dibujar las células vivas en el lienzo
    for (int x = 0; x < FRAMEBUFFER_WIDTH; ++x) {
        for (int y = 0; y < FRAMEBUFFER_HEIGHT; ++y) {
            if (cells[x][y]) {
                SDL_Rect cellRect;
                cellRect.x = x * CELL_SIZE;
                cellRect.y = y * CELL_SIZE;
                cellRect.w = CELL_SIZE;
                cellRect.h = CELL_SIZE;
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }

    // Actualizar el estado de las células
    bool newCells[FRAMEBUFFER_WIDTH][FRAMEBUFFER_HEIGHT] = {false};
    for (int x = 0; x < FRAMEBUFFER_WIDTH; ++x) {
        for (int y = 0; y < FRAMEBUFFER_HEIGHT; ++y) {
            int aliveNeighbors = 0;

            // Calcular las coordenadas de los vecinos
            int neighborsX[8] = {x - 1, x - 1, x - 1, x, x, x + 1, x + 1, x + 1};
            int neighborsY[8] = {y - 1, y, y + 1, y - 1, y + 1, y - 1, y, y + 1};

            for (int i = 0; i < 8; ++i) {
                // Asegurarse de que las coordenadas de los vecinos sean válidas
                getValidCoordinates(neighborsX[i], neighborsY[i]);

                if (cells[neighborsX[i]][neighborsY[i]]) {
                    aliveNeighbors++;
                }
            }

            // Aplicar las reglas del Juego de la Vida
            if (cells[x][y]) {
                // Célula viva
                if (aliveNeighbors == 2 || aliveNeighbors == 3) {
                    newCells[x][y] = true; // Sobrevive
                }
            } else {
                // Célula muerta
                if (aliveNeighbors == 3) {
                    newCells[x][y] = true; // Nace
                }
            }
        }
    }

    // Actualizar el estado de las células
    for (int x = 0; x < FRAMEBUFFER_WIDTH; ++x) {
        for (int y = 0; y < FRAMEBUFFER_HEIGHT; ++y) {
            cells[x][y] = newCells[x][y];
        }
    }
}

// Patrón: Spaceship
void addSpaceshipPattern(int startX, int startY) {
    cells[startX][startY + 1] = true;
    cells[startX + 1][startY + 2] = true;
    cells[startX + 2][startY] = true;
    cells[startX + 2][startY + 1] = true;
    cells[startX + 2][startY + 2] = true;
}

// Patrón: Glider
void addGliderPattern(int startX, int startY) {
    cells[startX][startY + 1] = true;
    cells[startX + 1][startY + 2] = true;
    cells[startX + 2][startY] = true;
    cells[startX + 2][startY + 1] = true;
    cells[startX + 2][startY + 2] = true;
}

// Patrón: Gosper Glider Gun
void addGosperGliderGunPattern(int startX, int startY) {
    cells[startX + 24][startY] = true;
    cells[startX + 22][startY + 1] = true;
    cells[startX + 24][startY + 1] = true;
    cells[startX + 12][startY + 2] = true;
    cells[startX + 13][startY + 2] = true;
    cells[startX + 20][startY + 2] = true;
    cells[startX + 21][startY + 2] = true;
    cells[startX + 34][startY + 2] = true;
    cells[startX + 35][startY + 2] = true;
    cells[startX + 11][startY + 3] = true;
    cells[startX + 15][startY + 3] = true;
    cells[startX + 20][startY + 3] = true;
    cells[startX + 21][startY + 3] = true;
    cells[startX + 34][startY + 3] = true;
    cells[startX + 35][startY + 3] = true;
    cells[startX + 0][startY + 4] = true;
    cells[startX + 1][startY + 4] = true;
    cells[startX + 10][startY + 4] = true;
    cells[startX + 16][startY + 4] = true;
    cells[startX + 20][startY + 4] = true;
    cells[startX + 21][startY + 4] = true;
    cells[startX + 0][startY + 5] = true;
    cells[startX + 1][startY + 5] = true;
    cells[startX + 10][startY + 5] = true;
    cells[startX + 14][startY + 5] = true;
    cells[startX + 16][startY + 5] = true;
    cells[startX + 17][startY + 5] = true;
    cells[startX + 22][startY + 5] = true;
    cells[startX + 24][startY + 5] = true;
    cells[startX + 10][startY + 6] = true;
    cells[startX + 16][startY + 6] = true;
    cells[startX + 24][startY + 6] = true;
    cells[startX + 11][startY + 7] = true;
    cells[startX + 15][startY + 7] = true;
    cells[startX + 12][startY + 8] = true;
    cells[startX + 13][startY + 8] = true;
}

// Patrón: Lightweight Spaceship
void addLightweightSpaceshipPattern(int startX, int startY) {
    cells[startX + 1][startY] = true;
    cells[startX + 4][startY] = true;
    cells[startX][startY + 1] = true;
    cells[startX][startY + 2] = true;
    cells[startX + 4][startY + 2] = true;
    cells[startX][startY + 3] = true;
    cells[startX + 3][startY + 3] = true;
    cells[startX + 4][startY + 3] = true;
    cells[startX + 2][startY + 4] = true;
}

// Patrón: Pulsar (Período 3)
void addPulsarPattern(int startX, int startY) {
    int x = startX;
    int y = startY;

    // Primer segmento
    cells[x + 2][y] = true;
    cells[x + 3][y] = true;
    cells[x + 4][y] = true;
    cells[x][y + 2] = true;
    cells[x + 5][y + 2] = true;
    cells[x][y + 3] = true;
    cells[x + 5][y + 3] = true;
    cells[x][y + 4] = true;
    cells[x + 5][y + 4] = true;
    cells[x + 2][y + 5] = true;
    cells[x + 3][y + 5] = true;
    cells[x + 4][y + 5] = true;

    // Segundo segmento
    cells[x + 7][y] = true;
    cells[x + 8][y] = true;
    cells[x + 9][y] = true;
    cells[x + 7][y + 5] = true;
    cells[x + 8][y + 5] = true;
    cells[x + 9][y + 5] = true;

    // Tercer segmento
    cells[x + 2][y + 7] = true;
    cells[x + 3][y + 7] = true;
    cells[x + 4][y + 7] = true;
    cells[x][y + 9] = true;
    cells[x + 5][y + 9] = true;
    cells[x][y + 10] = true;
    cells[x + 5][y + 10] = true;
    cells[x][y + 11] = true;
    cells[x + 5][y + 11] = true;
    cells[x + 2][y + 12] = true;
    cells[x + 3][y + 12] = true;
    cells[x + 4][y + 12] = true;

    // Cuarto segmento
    cells[x + 7][y + 7] = true;
    cells[x + 8][y + 7] = true;
    cells[x + 9][y + 7] = true;
    cells[x + 7][y + 12] = true;
    cells[x + 8][y + 12] = true;
    cells[x + 9][y + 12] = true;
}

// Patrón: Block
void addBlockPattern(int startX, int startY) {
    int x = startX;
    int y = startY;

    cells[x][y] = true;
    cells[x + 1][y] = true;
    cells[x][y + 1] = true;
    cells[x + 1][y + 1] = true;
}

// Patrón: Toad
void addToadPattern(int startX, int startY) {
    int x = startX;
    int y = startY;

    cells[x + 1][y] = true;
    cells[x + 2][y] = true;
    cells[x + 3][y] = true;
    cells[x][y + 1] = true;
    cells[x + 1][y + 1] = true;
    cells[x + 2][y + 1] = true;
}

// Patrón: Boat
void addBoatPattern(int startX, int startY) {
    int x = startX;
    int y = startY;

    cells[x][y] = true;
    cells[x + 1][y] = true;
    cells[x][y + 1] = true;
    cells[x + 2][y + 1] = true;
    cells[x + 1][y + 2] = true;
}

// Patrón: Heavyweight Spaceship
void addHeavyweightSpaceshipPattern(int startX, int startY) {
    int x = startX;
    int y = startY;

    cells[x + 1][y] = true;
    cells[x + 2][y] = true;
    cells[x + 3][y] = true;
    cells[x][y + 1] = true;
    cells[x + 3][y + 1] = true;
    cells[x + 3][y + 2] = true;
    cells[x + 3][y + 3] = true;
    cells[x][y + 4] = true;
    cells[x + 2][y + 4] = true;
}

// Patrón: Puffer Train
void addPufferTrainPattern(int startX, int startY) {
    int x = startX;
    int y = startY;

    cells[x + 3][y] = true;
    cells[x + 4][y] = true;
    cells[x + 5][y] = true;
    cells[x + 2][y + 1] = true;
    cells[x + 5][y + 1] = true;
    cells[x + 5][y + 2] = true;
    cells[x + 1][y + 3] = true;
    cells[x + 5][y + 3] = true;
    cells[x + 6][y + 3] = true;
    cells[x + 7][y + 3] = true;
    cells[x + 8][y + 3] = true;
    cells[x][y + 4] = true;
    cells[x + 2][y + 4] = true;
    cells[x + 4][y + 4] = true;
    cells[x + 7][y + 4] = true;
    cells[x + 8][y + 4] = true;
    cells[x][y + 5] = true;
    cells[x + 1][y + 5] = true;
    cells[x + 2][y + 5] = true;
    cells[x + 6][y + 5] = true;
    cells[x + 7][y + 5] = true;
    cells[x][y + 6] = true;
    cells[x + 1][y + 6] = true;
    cells[x + 6][y + 6] = true;
    cells[x + 7][y + 6] = true;
    cells[x + 8][y + 6] = true;
}

// Patrón: Penta-decathlon
void addPentaDecathlonPattern(int startX, int startY) {
    int x = startX;
    int y = startY;

    cells[x + 1][y] = true;
    cells[x + 2][y] = true;
    cells[x + 3][y] = true;
    cells[x][y + 1] = true;
    cells[x + 4][y + 1] = true;
    cells[x + 1][y + 2] = true;
    cells[x + 2][y + 2] = true;
    cells[x + 3][y + 2] = true;
    cells[x][y + 3] = true;
    cells[x + 4][y + 3] = true;
    cells[x + 1][y + 4] = true;
    cells[x + 2][y + 4] = true;
    cells[x + 3][y + 4] = true;
}

// Patrón: Infinite Growth 1
void addInfiniteGrowth1Pattern(int startX, int startY) {
    int x = startX;
    int y = startY;

    cells[x][y] = true;
    cells[x + 1][y] = true;
    cells[x + 2][y] = true;
    cells[x + 3][y] = true;
    cells[x + 4][y] = true;
    cells[x + 5][y] = true;
    cells[x + 6][y] = true;
    cells[x + 7][y] = true;
    cells[x + 8][y] = true;
    cells[x + 9][y] = true;
    cells[x + 10][y] = true;
    cells[x + 11][y] = true;
    cells[x + 12][y] = true;
    cells[x + 13][y] = true;
    cells[x + 14][y] = true;
    cells[x + 15][y] = true;
    cells[x + 16][y] = true;
    cells[x + 17][y] = true;
    cells[x + 18][y] = true;
    cells[x + 19][y] = true;
    cells[x + 20][y] = true;
    cells[x + 21][y] = true;
    cells[x + 22][y] = true;
    cells[x + 23][y] = true;
    cells[x + 24][y] = true;
    cells[x + 25][y] = true;
    cells[x + 26][y] = true;
    cells[x + 27][y] = true;
    cells[x + 28][y] = true;
    cells[x + 29][y] = true;
    cells[x + 30][y] = true;
    cells[x + 31][y] = true;
    cells[x + 32][y] = true;
    cells[x + 33][y] = true;
    cells[x + 34][y] = true;
    cells[x + 35][y] = true;
    cells[x + 36][y] = true;
    cells[x + 37][y] = true;
    cells[x + 38][y] = true;
    cells[x + 39][y] = true;
    cells[x + 40][y] = true;
    cells[x + 41][y] = true;
    cells[x + 42][y] = true;
    cells[x + 43][y] = true;
    cells[x + 44][y] = true;
    cells[x + 45][y] = true;
    cells[x + 46][y] = true;
    cells[x + 47][y] = true;
    cells[x + 48][y] = true;
    cells[x + 49][y] = true;
    cells[x + 50][y] = true;
}


int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Juego de la Vida", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;

    // Agregar patrones iniciales
    addInfiniteGrowth1Pattern(25, 30);
    addInfiniteGrowth1Pattern(25, 60);
    // addSpaceshipPattern(10, 10);
    // addGliderPattern(60, 10);
    // addGosperGliderGunPattern(25, 45);
    // addPulsarPattern(10, 50);
    // addLightweightSpaceshipPattern(70, 50);
    // addBlockPattern(80, 10);
    // addToadPattern(80, 20);
    // addBoatPattern(80, 30);
    // addPentaDecathlonPattern(10, 70);
    // addPufferTrainPattern(40, 70);


    bool isRunning = true;
    while (isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color negro
        SDL_RenderClear(renderer);

        render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(100); // Retardo de 0.1 segundos entre frames
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}