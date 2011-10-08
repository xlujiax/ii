#include "sdl_window.h"

bool setup_sdl_window(const int width, const int height)
{
  const SDL_VideoInfo* video;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Couldn't initialize SDL: "
	      << SDL_GetError() << std::endl;
    return false;
  }

  /* Quit SDL properly on exit */
  atexit(SDL_Quit);

  /* Get the current video information */
  video = SDL_GetVideoInfo();
  if(video == NULL) {
    std::cout << "Couldn't get video information: "
	      << SDL_GetError() << std::endl;
    return false;
  }

  /* Set the minimum requirements for the OpenGL window */
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  /* Note the SDL_DOUBLEBUF flag is not required to enable double
   * buffering when setting an OpenGL video mode.
   * Double buffering is enabled or disabled using the
   * SDL_GL_DOUBLEBUFFER attribute.
   */
  if(SDL_SetVideoMode(width, height, video->vfmt->BitsPerPixel, SDL_OPENGL) == 0) {
    std::cout << "Couldn't set video mode: "
	 << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}
