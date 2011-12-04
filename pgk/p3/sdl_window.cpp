#include "sdl_window.hpp"

bool window::setup(const int width_param, const int height_param)
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

  return create_viewport(width_param, height_param);
}


bool window::create_viewport(const int width_param, const int height_param)
{
  width = width_param;
  height = height_param;
  
  if(SDL_SetVideoMode(width, height, get_bits_per_pixel(), SDL_OPENGL | SDL_RESIZABLE) == 0) {
    std::cout << "Couldn't set video mode: "
	 << SDL_GetError() << std::endl;
    return false;
  }

  setup_opengl(width, height);
  return true;
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
	  switch(event.button.button)
	  {
	    case SDL_BUTTON_LEFT:
	      {
		const float x_screen = static_cast<float>(event.button.x);
		const float y_screen = static_cast<float>(event.button.y);

		// scaling from <0,width> to <-1,1>
		const float x_scaled =
		  2.0 * (x_screen - static_cast<float>(width) / 2.0)
		  / static_cast<float>(width);
		const float y_scaled = 
		  2.0 * (y_screen - static_cast<float>(height) / 2.0)
		  / static_cast<float>(height);
		
		mousedown(x_scaled, y_scaled);
	      }
	      break;
	    case SDL_BUTTON_WHEELUP:
	      mousewheelup();
	      break;
	    case SDL_BUTTON_WHEELDOWN:
	      mousewheeldown();
	      break;
	  }
	  break;
	case SDL_MOUSEBUTTONUP:
	  if(event.button.button == SDL_BUTTON_LEFT)
	    mouseup();
	  break;
	case SDL_MOUSEMOTION:
	  {
	    const float x_screen = static_cast<float>(event.motion.x);
	    const float y_screen = static_cast<float>(event.motion.y);

	    // scaling from <0,width> to <-1,1>
	    const float x_scaled =
	      2.0 * (x_screen - static_cast<float>(width) / 2.0)
	      / static_cast<float>(width);
	    const float y_scaled = 
	      2.0 * (y_screen - static_cast<float>(height) / 2.0)
	      / static_cast<float>(height);

	    mousemotion(x_scaled, y_scaled);
	  }
	  break;
	case SDL_VIDEORESIZE:
	  create_viewport(event.resize.w, event.resize.h);
	  break;
        case SDL_QUIT:
          exit(0);
          break;
      }
    }

    frame();
  }
}
