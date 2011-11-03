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
  else if(line.substr(0,3) == "vt ") return line_type::texture;
  else if(line.substr(0,2) == "f ") return line_type::face;
  else if(line.substr(0,7) == "mtllib ") return line_type::material;
  else if(line[0] == '#') return line_type::comment;
  else return line_type::unclassified;
}

std::string obj_format::read_material_file(const std::vector<std::string>& lines) const
{
  for(auto line : lines)
    if(classify_line(line) == line_type::material)
    {
      char material_file[30];
      sscanf(line.c_str(), "mtllib %s", material_file);
      return std::string(material_file);
    }
  return "";
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

std::vector<vec2> obj_format::read_textures(const std::vector<std::string>& lines) const
{
  std::vector<vec2> ts;
  
  for(auto line : lines)
    if(classify_line(line) == line_type::texture)
    {
      float u, v;
      sscanf(line.c_str(), "vt %f %f", &u, &v);
      ts.push_back({ u, v });
    }
  return ts;
}

// vertices and their normals are indexed differently in OBJ;
// this function packs them to one structure
std::vector<vertex> obj_format::pack_into_vertex_structure(
  const std::vector<std::string>& lines,
  const std::vector<vec3>& vs,
  const std::vector<vec3>& ns,
  const std::vector<vec2>& ts
							   ) const
{
  std::vector<vertex> nvs;
  nvs.resize(vs.size());

  for(auto line : lines)
    if(classify_line(line) == line_type::face)
    {
      int v[3];
      int n[3];
      int t[3];

      sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
	&v[0], &t[0], &n[0],
	&v[1], &t[1], &n[1],
	&v[2], &t[2], &n[2]
	     );
      for(int i = 0; i < 3; ++i)
      {
	vertex vx = {
	  vs.at(v[i] - 1).x, vs.at(v[i] - 1).y, vs.at(v[i] - 1).z,
	  ns.at(n[i] - 1).x, ns.at(n[i] - 1).y, ns.at(n[i] - 1).z,
	  ts.at(t[i] - 1).x, ts.at(t[i] - 1).y
	};

	printf("ts[%d] = %f %f\n", t[i], vx.u, vx.v);

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
      int v[3];
      int unused;

      sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
	&v[0], &unused, &unused,
	&v[1], &unused, &unused,
	&v[2], &unused, &unused
	     );
      for(int i = 0; i < 3; ++i)
      {
	const int index_in_vbo = v[i] - 1; // could be index of normal or vertex, both viable, I've choosen vertex index
       
	fs.push_back(index_in_vbo);
      }
    }
  return fs;
}

std::string obj_format::read_texture_filename(const std::vector<std::string>& lines) const
{
  for(auto line : lines)
    if(line.substr(0,4) == "map_")
    {
      char head[20];
      char filename[40];
      sscanf(line.c_str(), "%s %s", head, filename);
      return std::string(filename);
    }
  return "";
}

void obj_format::read_from_file(const char* filename)
{
  auto model = file_to_memory(filename);

  auto vs = read_vertices(model);
  auto ns = read_normals(model);
  auto ts = read_textures(model);

  vertices = pack_into_vertex_structure(model, vs, ns, ts);
  indices = read_indices(model, vertices);

  printf("Read:\n%d vertices\n%d normals\n%d texture coordinates\n%d indices\n",
    static_cast<int>(vs.size()),
    static_cast<int>(ns.size()),
    static_cast<int>(ts.size()),
    static_cast<int>(indices.size()));

  for(auto t : ts)
  {
    printf("uv: %f %f\n", t.x, t.y);
  }

  for(auto vx : vertices)
  {
    printf("x: %f y: %f z: %f u: %f v: %f\n", vx.x, vx.y, vx.z, vx.u, vx.v);
  }
  

  glGenBuffers(1, &vertices_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &indices_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

  std::string mtl_file = read_material_file(model);
  auto materials = file_to_memory(mtl_file.c_str());
  std::string texture_file = read_texture_filename(materials);
  texture_id = load_texture(texture_file.c_str(), texture_width, texture_height);
  glEnable(GL_TEXTURE_2D);
  glClientActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glShadeModel(GL_SMOOTH);

}

void obj_format::draw() const
{
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(0));

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(3 * sizeof(float)));

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, sizeof(vertex), BUFFER_OFFSET(6 * sizeof(float)));
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
