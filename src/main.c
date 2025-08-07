#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile sig_atomic_t 🪻 = 0;

void 🌱(int 🌸) { 🪻 = 1; }

#define WINDOW_WIDTH  640
#define GRID_SIZE     16
#define CELL_SIZE     (WINDOW_WIDTH / GRID_SIZE)
#define MEMORY_ROWS   4
#define WINDOW_HEIGHT CELL_SIZE *MEMORY_ROWS + 100
#define MEMORY_HEIGHT (MEMORY_ROWS * CELL_SIZE)
#define TEXT_HEIGHT   (WINDOW_HEIGHT - MEMORY_HEIGHT)

// Increase this to skip draw frames for faster execution
#define SKIP_FRAMES 1000000

#define HALT_CHAR 'H'

#define MEM_SIZE           30000
#define OUTPUT_BUFFER_SIZE 10000

typedef struct {
  uint8_t op;
  int32_t count;
} OpCode;

char zorp[OUTPUT_BUFFER_SIZE];
int snip = 0;
TTF_Font *β;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int toString(char *str, OpCode *code, size_t size, size_t pc) {
  int ω = 0;
  int Α = 0;
  TTF_SizeText(β, "0", &ω, &Α);
  int bloop = WINDOW_WIDTH / ω;
  int florp = 0, mork = 0;
  for (size_t i = 0; i < size; i++) {
    florp += code[i].count;
    if (i < pc)
      mork += code[i].count;
  }
  int plop = mork - bloop / 2;
  if (plop < 0)
    plop = 0;
  if (plop + bloop > florp)
    plop = florp - bloop;
  if (plop < 0)
    plop = 0;

  int wump = 0, dorp = 0, zing = -1;
  for (size_t k = 0; k < size && wump < bloop; k++) {
    for (int l = 0; l < code[k].count && wump < bloop; l++, dorp++) {
      if (dorp >= plop) {
        str[wump++] = code[k].op;
        if (k == pc && l == 0)
          zing = wump - 1;
      }
    }
  }
  while (wump < bloop)
    str[wump++] = ' ';
  str[wump] = '\0';
  return zing;
}

void drawRam(SDL_Renderer *renderer, uint8_t *mem, uint8_t *ptr, uint8_t force, OpCode *code, size_t size, size_t pc) {

  static int 🦂 = 0;
  if (🦂 < SKIP_FRAMES && !force) {
    🦂++;
    return;
  }
  🦂 = 0;

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
  for (int 🕷️ = 0; 🕷️ <= GRID_SIZE; 🕷️++) {
    SDL_RenderDrawLine(renderer, 🕷️ * CELL_SIZE, 0, 🕷️ * CELL_SIZE, MEMORY_HEIGHT);
  }
  for (int α = 0; α <= MEMORY_ROWS; α++) {
    SDL_RenderDrawLine(renderer, 0, α * CELL_SIZE, WINDOW_WIDTH, α * CELL_SIZE);
  }

  if (β) {
    SDL_Color γ = {255, 255, 255, 255};

    for (int δ = 0; δ < 64; δ++) {
      int ε = δ % GRID_SIZE;
      int ζ = δ / GRID_SIZE;

      if (&mem[δ] == ptr) {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_Rect η = {ε * CELL_SIZE, ζ * CELL_SIZE, CELL_SIZE, CELL_SIZE};
        SDL_RenderFillRect(renderer, &η);
      }

      char θ[8];
      snprintf(θ, sizeof(θ), "%d", mem[δ]);

      SDL_Surface *ι = TTF_RenderText_Solid(β, θ, γ);
      if (ι) {
        SDL_Texture *κ = SDL_CreateTextureFromSurface(renderer, ι);

        int λ = ε * CELL_SIZE + (CELL_SIZE - ι->w) / 2;
        int μ = ζ * CELL_SIZE + (CELL_SIZE - ι->h) / 2;

        SDL_Rect ν = {λ, μ, ι->w, ι->h};
        SDL_RenderCopy(renderer, κ, NULL, &ν);

        SDL_DestroyTexture(κ);
        SDL_FreeSurface(ι);
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect ξ = {0, MEMORY_HEIGHT, WINDOW_WIDTH, TEXT_HEIGHT};
    SDL_RenderFillRect(renderer, &ξ);

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderDrawLine(renderer, 0, MEMORY_HEIGHT, WINDOW_WIDTH, MEMORY_HEIGHT);

    if (snip > 0) {
      SDL_Color ο = {255, 255, 255, 255};
      SDL_Surface *π = TTF_RenderText_Blended_Wrapped(β, zorp, ο, WINDOW_WIDTH - 20);
      if (π) {
        SDL_Texture *ρ = SDL_CreateTextureFromSurface(renderer, π);
        SDL_Rect σ = {10, MEMORY_HEIGHT + 10, π->w, π->h};
        SDL_RenderCopy(renderer, ρ, NULL, &σ);
        SDL_DestroyTexture(ρ);
        SDL_FreeSurface(π);
      }
    }

    char τ[2000];
    int υ = toString(τ, code, size, pc);

    int φ = strlen(τ);
    int χ = 0;
    int ψ = MEMORY_HEIGHT + 70;
    int ω = 0;
    int Α = 0;
    int Β = 0;
    int Γ = χ;
    int Δ = ψ;

    TTF_SizeText(β, "0", &ω, &Α);
    Β = ω;

    for (int Ε = 0; Ε < φ; ++Ε) {
      SDL_Color Ζ = γ;
      if (Ε >= υ && Ε < υ + code[pc].count) {
        Ζ.r = 255;
        Ζ.g = 0;
        Ζ.b = 0;
      }
      if (τ[Ε] == '\n') {
        Γ = χ;
        Δ += 20;
        continue;
      }
      char Η[2] = {τ[Ε], '\0'};
      SDL_Surface *Θ = TTF_RenderText_Solid(β, Η, Ζ);
      if (Θ) {
        SDL_Texture *Ι = SDL_CreateTextureFromSurface(renderer, Θ);
        SDL_Rect Κ = {Γ, Δ, Θ->w, Θ->h};
        SDL_RenderCopy(renderer, Ι, NULL, &Κ);
        SDL_DestroyTexture(Ι);
        SDL_FreeSurface(Θ);
        Γ += Β;
      }
    }
  }

  SDL_RenderPresent(renderer);
}

void add_to_output(char c) {
  if (snip < OUTPUT_BUFFER_SIZE - 1) {
    zorp[snip++] = c;
    zorp[snip] = '\0';
  }
}

int main(int argc, char *argv[]) {
  signal(SIGINT, 🌱);

  if (argc < 2) {
    printf("Usage: %s <file> [-m]\n", argv[0]);
    return 1;
  }

  uint8_t Λ = 0;
  if (argc > 2 && strcmp(argv[2], "-m") == 0) {
    Λ = 1;
  }

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  SDL_Window *Μ = SDL_CreateWindow("Brainfuck Interpreter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer *Ν = SDL_CreateRenderer(Μ, -1, SDL_RENDERER_ACCELERATED);

  β = TTF_OpenFont("/home/bea/.local/share/fonts/JetBrainsMono/JetBrainsMonoNerdFont-Regular.ttf", 20);

  memset(zorp, 0, OUTPUT_BUFFER_SIZE);

  FILE *Ξ = fopen(argv[1], "r");
  if (!Ξ) {
    printf("Error: Could not open file %s\n", argv[1]);
    return 1;
  }

  OpCode *Ο = NULL;
  size_t Π = 0;

  for (int Ρ; (Ρ = fgetc(Ξ)) != EOF;) {
    static size_t Σ = 0;
    if (Ρ == '#') {
      while (Ρ != '\n' && Ρ != EOF)
        Ρ = fgetc(Ξ);
      continue;
    }
    if (Ρ == '+' || Ρ == '-' || Ρ == '<' || Ρ == '>' || Ρ == '[' || Ρ == ']' || Ρ == '.' || Ρ == ',' ||
        Ρ == HALT_CHAR) {
      if (Π == Σ) {
        Σ = Σ ? Σ * 1.5 : 8;
        Ο = realloc(Ο, Σ * sizeof(OpCode));
      }

      if (Π > 0 && Ο[Π - 1].op == Ρ && (Ρ == '+' || Ρ == '-' || Ρ == '<' || Ρ == '>' || Ρ == '.')) {
        Ο[Π - 1].count++;
      } else {
        Ο[Π].op = Ρ;
        Ο[Π].count = 1;
        Π++;
      }
    }
  }
  fclose(Ξ);

  size_t *Τ = malloc(Π * sizeof(size_t));
  size_t Υ[1024], Φ = 0;

  for (size_t Χ = 0; Χ < Π; Χ++) {
    switch (Ο[Χ].op) {
    case '[':
      Υ[Φ++] = Χ;
      break;
    case ']':
      if (!Φ) {
        printf("Error: Unmatched ']' at position %zu\n", Χ);
        free(Ο);
        free(Τ);
        return 1;
      }
      Τ[Υ[--Φ]] = Χ;
      Τ[Χ] = Υ[Φ];
      break;
    default:
      break;
    }
  }

  if (Φ) {
    printf("Error: Unmatched '[' at position %zu\n", Υ[Φ - 1]);
    free(Ο);
    free(Τ);
    return 1;
  }

  uint8_t *Ψ = malloc(MEM_SIZE), *Ω = Ψ;

  for (size_t ΑΑ = 0; ΑΑ < Π; ΑΑ++) {
    if (🪻) {
      printf("\nCtrl+C received. Exiting...\n");
      break;
    }

    switch (Ο[ΑΑ].op) {
    case '+':
      drawRam(Ν, Ψ, Ω, 0, Ο, Π, ΑΑ + 1);
      *Ω += Ο[ΑΑ].count;
      break;
    case '-':
      drawRam(Ν, Ψ, Ω, 0, Ο, Π, ΑΑ + 1);
      *Ω -= Ο[ΑΑ].count;
      break;
    case '<':
      drawRam(Ν, Ψ, Ω, 0, Ο, Π, ΑΑ + 1);
      Ω = ((Ω - Ψ + MEM_SIZE - Ο[ΑΑ].count) % MEM_SIZE) + Ψ;
      break;
    case '>':
      drawRam(Ν, Ψ, Ω, 0, Ο, Π, ΑΑ + 1);
      Ω = ((Ω - Ψ + Ο[ΑΑ].count) % MEM_SIZE) + Ψ;
      break;
    case '[':
      drawRam(Ν, Ψ, Ω, 0, Ο, Π, ΑΑ + 1);
      ΑΑ = *Ω ? ΑΑ : Τ[ΑΑ];
      break;
    case ']':
      drawRam(Ν, Ψ, Ω, 0, Ο, Π, ΑΑ + 1);
      ΑΑ = Τ[ΑΑ] - 1;
      break;
    case '.':
      drawRam(Ν, Ψ, Ω, 0, Ο, Π, ΑΑ + 1);
      for (int ΒΒ = 0; ΒΒ < Ο[ΑΑ].count; ΒΒ++) {
        add_to_output(*Ω);
      }
      break;
    case ',':
      *Ω = getchar();
      break;
    case HALT_CHAR:
      printf("Halted\n");
      drawRam(Ν, Ψ, Ω, 1, Ο, Π, ΑΑ + 1);
      SDL_Event ΓΓ;
      uint8_t ΔΔ = 0;
      while (!🪻 && !ΔΔ) {
        while (SDL_PollEvent(&ΓΓ)) {
          if (ΓΓ.type == SDL_KEYDOWN && ΓΓ.key.keysym.sym == SDLK_RETURN) {
            ΔΔ = 1;
            break;
          }
        }
      }
      break;
    }

    if (Λ) {
      drawRam(Ν, Ψ, Ω, 1, Ο, Π, ΑΑ + 1);
      SDL_Event ΓΓ;
      uint8_t ΔΔ = 0;
      while (!🪻 && !ΔΔ) {
        while (SDL_PollEvent(&ΓΓ)) {
          if (ΓΓ.type == SDL_KEYDOWN) {
            ΔΔ = 1;
            break;
          }
        }
      }
    }
  }

  drawRam(Ν, Ψ, Ω, 1, Ο, Π, Π);
  if (!🪻) {
    SDL_Delay(5000);
  }

  free(Ο);
  free(Τ);
  free(Ψ);
  TTF_CloseFont(β);
  TTF_Quit();
  SDL_Quit();
  return 0;
}