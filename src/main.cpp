#include <SDL2/SDL.h>

const int FRAMEBUFFER_WIDTH = 100;
const int FRAMEBUFFER_HEIGHT = 100;

bool cells[FRAMEBUFFER_WIDTH][FRAMEBUFFER_HEIGHT] = {false};

void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco

    // Dibujar las células vivas en el lienzo
    for (int x = 0; x < FRAMEBUFFER_WIDTH; ++x) {
        for (int y = 0; y < FRAMEBUFFER_HEIGHT; ++y) {
            if (cells[x][y]) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    // Actualizar el estado de las células
    bool newCells[FRAMEBUFFER_WIDTH][FRAMEBUFFER_HEIGHT] = {false};
    for (int x = 0; x < FRAMEBUFFER_WIDTH; ++x) {
        for (int y = 0; y < FRAMEBUFFER_HEIGHT; ++y) {
            int aliveNeighbors = 0;

            // Contar el número de vecinos vivos
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }

                    int neighborX = x + dx;
                    int neighborY = y + dy;

                    // Asegurarse de que los vecinos estén dentro de los límites del lienzo
                    if (neighborX >= 0 && neighborX < FRAMEBUFFER_WIDTH && neighborY >= 0 && neighborY < FRAMEBUFFER_HEIGHT) {
                        if (cells[neighborX][neighborY]) {
                            aliveNeighbors++;
                        }
                    }
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

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Juego de la Vida", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;

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
