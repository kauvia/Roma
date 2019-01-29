#ifndef ROMA_ENGINE
#define ROMA_ENGINE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "./Graphics/Textures.h"
#include "./Data/Entity.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>

#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>
#include <array>

#include <iterator>
#include <random>

class Engine
{
public:
  static int SCREEN_WIDTH;
  static int SCREEN_HEIGHT;
  static int SCREEN_X;
  static int SCREEN_Y;

  Engine();
  ~Engine();

  bool Initialize(const char *windowTitle);
  bool loadMedia();

  void Update();
  void Render();

  bool runLoop();
  void closeEngine();

private:
  static SDL_Window *gWindow;
  static SDL_Renderer *gRenderer;
  static TTF_Font *gFont;
  static SDL_Event e;
};

class Xoroshiro128
{
private:
  std::array<uint64_t, 2> s;

  static inline uint64_t Rot1(const uint64_t x, int k)
  {
    return (x << k) | (x >> (64 - k));
  }

public:
  explicit Xoroshiro128(std::array<uint64_t, 2> &seed) : s(seed) {}

  template <typename T>
  static Xoroshiro128 SeedFromRng(T &rng)
  {
    std::array<uint64_t, 2> a;
    std::generate(a.begin(), a.end(), [rng]() mutable { return rng.Next(); });
    return Xoroshiro128(a);
  }

  u_int64_t Next(void)
  {
    const uint64_t s0 = s[0];
    uint64_t s1 = s[1];
    const u_int64_t result = s0 + s1;

    s1 ^= s0;
    s[0] = Rot1(s0, 55) ^ s1 ^ (s1 << 14);
    s[1] = Rot1(s1, 36);

    return result;
  }

  void Jump()
  {
    static const std::array<uint64_t, 2> JUMP = {0xbeac0467eba5facb, 0xd86b0486aa992};
    uint64_t s0 = 0;
    uint64_t s1 = 0;
    for (size_t i = 0; i < JUMP.size(); i++)
    {
      for (auto b = 0; b < 64; b++)
      {
        if (JUMP[i] & 1ULL << b)
        {
          s0 ^= s[0];
          s1 ^= s[1];
        }
        Next();
      }
    }
    s[0] = s0;
    s[1] = s1;
  }
  static const size_t STATE_SIZE = 2;
};
template <typename T>

class Random
{

private:
  T generator;

public:
  Random() : generator(std::chrono::high_resolution_clock::now().time_since_epoch().count())
  {
  }
  int generate_integer(int begin, int end)
  {
    return std::uniform_int_distribution<int>(begin, end - 1)(generator);
  }
};

#endif