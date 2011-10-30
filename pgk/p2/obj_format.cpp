#include "obj_format.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct vertex
{
  float x, y, z;
  float nx, ny, nz; // normal
  float u, v;       // texture
};

GLuint vertices_vbo;
GLuint indices_vbo;

GLuint num_vertices;
GLuint num_indices;
vertex* vertices;
GLuint* indices;
std::vector<vertex> nvs; // full vertices
std::vector<GLuint> fs; // faces (consecutive fours)

std::vector<std::string> obj_format::file_to_memory(
  const char* filename,
  const unsigned int max_line_len) const
{
  FILE* file = fopen(filename, "r");
  char line[max_line_len];
  std::vector<std::string> lines;
  while(fgets(line, max_line_len, file) != NULL)
    lines.push_back(line);
  return lines;
}

obj_format::line_type obj_format::classify_line(const std::string& line) const
{
  if(line.substr(0,2) == "v ") return line_type::vertex;
  else if(line.substr(0,3) == "vn ") return line_type::normal;
  else if(line.substr(0,2) == "f ") return line_type::face;
  else if(line[0] == '#') return line_type::comment;
  else return line_type::unclassified;
}

std::vector<vec3> obj_format::read_vertices(const std::vector<std::string>& lines) const
{
  std::vector<vec3> vs;
  
  for(auto line : lines)
    if(classify_line(line) == line_type::vertex)
    {
      float x,y,z;
      sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
      vs.push_back({ x, y, z });
    }
  return vs;
}

std::vector<vec3> obj_format::read_normals(const std::vector<std::string>& lines) const
{
  std::vector<vec3> ns;
  
  for(auto line : lines)
    if(classify_line(line) == line_type::normal)
    {
      float x,y,z;
      sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
      ns.push_back({ x, y, z });
    }
  return ns;
}

void obj_format::read_from_file(const char* filename)
{
  std::vector<vec3> vs; // vertices
  std::vector<vec3> ns; // normals

  std::map<int, vertex> map_nvs;

  auto model = file_to_memory(filename);
  for(auto line : model)
  {
    switch(classify_line(line))
    {
      case line_type::comment:
      case line_type::unclassified:
	break;
	
      case line_type::vertex:
	{
	  float x,y,z;
	  sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
	  vs.push_back({ x, y, z });
	}
	break;
      case line_type::normal:
	{
	  float x,y,z;
	  sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
	  ns.push_back({ x, y, z });
	}
	break;
      case line_type::face:
	{
	  int v[4];
	  int n[4];

	  sscanf(line.c_str(), "f %d//%d %d//%d %d//%d %d//%d",
	    &v[0], &n[0],
	    &v[1], &n[1],
	    &v[2], &n[2],
	    &v[3], &n[3]
		 );
	  for(int i = 0; i < 4; ++i)
	  {
	    vertex vx = {
	      vs[v[i] - 1].x, vs[v[i] - 1].y, vs[v[i] - 1].z,
	      ns[n[i] - 1].x, ns[n[i] - 1].y, ns[n[i] - 1].z,
	      0, 0
	    };

	    const int index_in_vbo = v[i] - 1; // could be index of normal or texture
	    if(map_nvs.end() == map_nvs.find(index_in_vbo))
	      map_nvs[index_in_vbo] = vx;
	    else
	    {
	      vertex before = (*map_nvs.find(index_in_vbo)).second;
	      assert(before.x == vx.x);
	      assert(before.y == vx.y);
	      assert(before.z == vx.z);
	      assert(before.nx == vx.nx);
	      assert(before.ny == vx.ny);
	      assert(before.nz == vx.nz);
	    }
       
	    fs.push_back(index_in_vbo);
	  }
	}
	break;
    }
  }

  nvs.reserve(map_nvs.size());
  for(auto i = map_nvs.begin(); i != map_nvs.end(); ++i)
    nvs.push_back(i->second);

  num_vertices = nvs.size();
  vertices = &nvs[0];
  
  num_indices = fs.size();
  indices = &fs[0];

  glGenBuffers(1, &vertices_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(vertex), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &indices_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

void obj_format::draw() const
{
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(0));

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(3 * sizeof(float)));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glDrawElements(GL_QUADS, num_indices, GL_UNSIGNED_INT, 0);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
