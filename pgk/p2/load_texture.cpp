#include "load_texture.hpp"

SDL_Surface *loadImage(const char *filename)
{
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;

  loadedImage = IMG_Load(filename);

  optimizedImage = SDL_DisplayFormat(loadedImage);
  SDL_FreeSurface(loadedImage);

  return optimizedImage;
}

GLuint load_texture(const char *filename)
{
  GLuint thisIsMyTexture;
  glGenTextures(1, &thisIsMyTexture);
  SDL_Surface* temporarySurface = loadImage(filename);
  glBindTexture(GL_TEXTURE_2D,thisIsMyTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, temporarySurface->w, temporarySurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, temporarySurface->pixels);
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  return thisIsMyTexture;
}
