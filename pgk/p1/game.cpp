#include "game.hpp"

void game::place_ball_on_the_left()
{
  
}

void game::place_ball_on_the_right()
{
}

void game::reset_paddles()
{
}

void game::init()
{
  {
    const float margin = 10.0;
    const float width = 640;
    const float height = 480;
    
    board1 = std::make_shared<board>();
    board1->pos.x = margin;
    board1->pos.y = margin;
    board1->size.x = width - 2*margin;
    board1->size.y = height - 2*margin;;
  }

  {
    const float boundary_size = 100;

    {
      top_boundary = std::make_shared<rect>();
      top_boundary->pos.x = board1.pos.x;
      top_boundary->pos.y = board1.pos.y - boundary_size;
      top_boundary->size.x = board1.size.x;
      top_boundary->size.y = boundary_size;
    }

    {
      bottom_boundary = std::make_shared<rect>();
      bottom_boundary->pos.x = board1.pos.x;
      bottom_boundary->pos.y = board1.pos.y;
      bottom_boundary->size.x = board1.size.x;
      bottom_boundary->size.y = boundary_size;
    }

    {
      left_score = std::make_shared<rect>();
      left_score->pos.x = board1.pos.x - boundary_size;
      left_score->pos.y = board1.pos.y;
      left_score->size.x = boundary_size;
      left_score->size.y = board1.size.y;
    }
    
    {
      right_score = std::make_shared<rect>();
      right_score->pos.x = board1.pos.x + board1.size.x;
      right_score->pos.y = board1.pos.y;
      right_score->size.x = boundary_size;
      right_score->size.y = board1.size.y;
    }
  }

  {
    player_left = std::make_shared<player>();
    player_right = std::make_shared<player>();
    
    reset_paddles();
  }

  {
    ball1 = std::make_shared<ball>();
    ball1.size.x = ball1.size.y = 20;
  
    place_ball_on_the_left();
  }
}

void game::animate(const float delta_time)
{
  player_left->animate(delta_time);
  player_right->animate(delta_time);
  ball1->animate(delta_time);
}

void game::draw() const
{
  std::array<std::shared_ptr<rect>, 4> obj_to_draw = {
    { board1,
      player_left,
      player_right,
      ball1 }
  };
  std::for_each(obj_to_draw.begin(), obj_to_draw(), [](const shared_ptr<rect>& r) {
      r->draw();
    })
}

void game::keyup(char k)
{
  switch(k)
  {
    case 'a':
      p1.move_up_end();
      break;
    case 'z':
      p1.move_down_end();
      break;
    case 'k':
      p2.move_up_end();
      break;
    case 'm':
      p2.move_down_end();
      break;
    default:
      break;
  }
}

void game::keydown(char k)
{
  switch(k)
  {
    case 'a':
      p1.move_up();
      break;

    case 'z':
      p1.move_down();
      break;

    case 'k':
      p2.move_up();
      break;

    case 'm':
      p2.move_down();
      break;

    default:
      break;
  }
}
