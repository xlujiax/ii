#include "obj_format.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

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

// vertices and their normals are indexed differently in OBJ;
// this function packs them to one structure
std::vector<vertex> obj_format::pack_into_vertex_structure(
  const std::vector<std::string>& lines,
  const std::vector<vec3>& vs,
  const std::vector<vec3>& ns
					       ) const
{
  std::vector<vertex> nvs;
  nvs.resize(vs.size());

  for(auto line : lines)
    if(classify_line(line) == line_type::face)
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
	  vs.at(v[i] - 1).x, vs.at(v[i] - 1).y, vs.at(v[i] - 1).z,
	  ns.at(n[i] - 1).x, ns.at(n[i] - 1).y, ns.at(n[i] - 1).z,
	  0, 0
	};

	const int index_in_vbo = v[i] - 1; // could be index of normal or vertex, both viable, I've choosen vertex index
	nvs[index_in_vbo] = vx;
      }
    }
  return nvs;
}

std::vector<GLuint> obj_format::read_indices(const std::vector<std::string>& lines,
  const std::vector<vertex>& nvs) const
{
  std::vector<GLuint> fs;

  for(auto line : lines)
    if(classify_line(line) == line_type::face)
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
	const int index_in_vbo = v[i] - 1; // could be index of normal or vertex, both viable, I've choosen vertex index
       
	fs.push_back(index_in_vbo);
      }
    }
  return fs;
}

void obj_format::read_from_file(const char* filename)
{
  auto model = file_to_memory(filename);

  std::vector<vec3> vs = read_vertices(model);
  std::vector<vec3> ns = read_normals(model);

  assert(ns.size() == vs.size()); // normal per vertex

  vertices = pack_into_vertex_structure(model, vs, ns);
  indices = read_indices(model, vertices);

  glGenBuffers(1, &vertices_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &indices_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

void obj_format::draw() const
{
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(0));

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(3 * sizeof(float)));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_INT, 0);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
