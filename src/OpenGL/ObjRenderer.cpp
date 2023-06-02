#include "ObjRenderer.hpp"

/* --- ObjRenderer --- */

MultiResObjRenderer::MultiResObjRenderer(
    const char* low_obj_path, const char* medium_obj_path, const char* high_obj_path,
    const char* image_path, const p6::Shader* shader
)
{
    img::Image image   = p6::load_image_buffer(image_path);
    GLuint     texture = initTex(image);

    this->low_renderer       = ObjRenderer(low_obj_path, texture, shader);
    this->medium_renderer    = ObjRenderer(medium_obj_path, texture, shader);
    this->high_renderer      = ObjRenderer(high_obj_path, texture, shader);
    this->_floor_low_medium  = Parameters::get().FLOOR_LOW_MEDIUM;
    this->_floor_medium_high = Parameters::get().FLOOR_MEDIUM_HIGH;
}

void MultiResObjRenderer::draw(float cam_distance)
{
    if (cam_distance < this->_floor_medium_high)
    {
        this->high_renderer.draw();
    }
    else if (cam_distance > this->_floor_low_medium)
    {
        this->low_renderer.draw();
    }
    else
    {
        this->medium_renderer.draw();
    }
}

ObjRenderer::ObjRenderer()
{
    this->shader = shader;
    this->_initGL("assets/models/baleine_low.obj"); // via ObjLoader

    img::Image image = p6::load_image_buffer("assets/textures/uvgrid.jpg"); // load texture
    this->texture    = initTex(image);
}

ObjRenderer::ObjRenderer(const char* obj_path, const char* image_path, const p6::Shader* shader)
{
    std::vector<ShapeVertex> vertices = LoadOBJ(obj_path);
    this->shader                      = shader;
    this->_initGL(obj_path); // via ObjLoader

    img::Image image = p6::load_image_buffer(image_path); // load texture
    this->texture    = initTex(image);
}

ObjRenderer::ObjRenderer(const char* obj_path, GLuint texture, const p6::Shader* shader)
{
    std::vector<ShapeVertex> vertices = LoadOBJ(obj_path);
    this->shader                      = shader;
    this->_initGL(obj_path); // via ObjLoader

    this->texture = texture;
}

void ObjRenderer::_initGL(const char* obj_path)
{
    std::vector<ShapeVertex> shapevertexes = LoadOBJ(obj_path);
    std::cout << "shapevertexes"
              << " " << shapevertexes.size() << std::endl;

    std::vector<Vertex3DUV> vv;
    for (int i = 0; i < (int)shapevertexes.size(); i++)
    {
        vv.push_back(Vertex3DUV(shapevertexes[i].position, shapevertexes[i].texCoords, shapevertexes[i].normal));
    };

    // storing vv.len() in vertex_size
    this->vertex_size = vv.size();

    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::cout << vv.size() << std::endl;
    glBufferData(GL_ARRAY_BUFFER, vv.size() * sizeof(Vertex3DUV), &vv[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* --- VAO --- */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_TEXTURE  = 2;
    const GLuint VERTEX_ATTR_NORMAL   = 3;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

    /* --- Binding --- */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*)(offsetof(Vertex3DUV, _position)));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*)(offsetof(Vertex3DUV, _coordTex)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*)(offsetof(Vertex3DUV, _normal)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->vao = vao;
}

void ObjRenderer::draw()
{
    // draw obj
    glBindVertexArray(this->vao);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glDrawArrays(GL_TRIANGLES, 0, this->vertex_size);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}