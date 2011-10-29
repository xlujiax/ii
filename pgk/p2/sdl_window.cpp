#include "sdl_window.hpp"

bool window::setup(const int width, const int height)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Couldn't initialize SDL: "
	      << SDL_GetError() << std::endl;
    return false;
  }
  atexit(SDL_Quit);

  video = SDL_GetVideoInfo();
  if(video == NULL) {
    std::cout << "Couldn't get video information: "
	      << SDL_GetError() << std::endl;
    return false;
  }

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

  if(SDL_SetVideoMode(width, height, get_bits_per_pixel(), SDL_OPENGL | SDL_RESIZABLE) == 0) {
    std::cout << "Couldn't set video mode: "
	 << SDL_GetError() << std::endl;
    return false;
  }

  setup_opengl(width, height);

  return true;
}


void window::handle_resize(const int width, const int height)
{
  SDL_SetVideoMode(width, height, get_bits_per_pixel(), SDL_OPENGL | SDL_RESIZABLE);

  glViewport(0, 0, width, height);
}

void window::main_loop()
{
  SDL_Event event;

  while(true)
  {
    while(SDL_PollEvent(&event))
    {
      switch(event.type) {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
	  {
            case SDLK_ESCAPE:
              exit(0);
              break;

            default:
	      keydown(event.key.keysym.sym);
              break;
          }
          break;
	case SDL_KEYUP:
	  keyup(event.key.keysym.sym);
          break;
	case SDL_MOUSEBUTTONDOWN:
	  if(event.button.button == SDL_BUTTON_LEFT)
	    mousedown();
	  break;
	case SDL_MOUSEBUTTONUP:
	  if(event.button.button == SDL_BUTTON_LEFT)
	    mouseup();
	  break;
	case SDL_MOUSEMOTION:
	  mousemotion(
	    static_cast<float>(event.motion.x), static_cast<float>(event.motion.y),
	    static_cast<float>(event.motion.xrel), static_cast<float>(event.motion.yrel)
		      );
	  break;
	case SDL_VIDEORESIZE:
	  handle_resize(event.resize.w, event.resize.h);
	  break;
        case SDL_QUIT:
          exit(0);
          break;
      }
    }

    frame();
  }
}
