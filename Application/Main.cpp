#include "Engine.h" 
#include <iostream> 

float points[] = {
  -1.0f, -1.0f,  0.0f,
   0.0f,  1.0f,  0.0f,
   1.0f, -1.0f,  0.0f,

   -1.0f, -1.0f,  0.0f,
   1.0f,  1.0f,  0.0f,
   1.0f, -1.0f,  0.0f,
};

glm::Vector3 colors[] =
{
	{0, 0, 1 },
	{1, 0, 1 },
	{0, 1, 0 },
	{0, 0, 1 },
	{0, 1, 1 },
	{1, 1, 1 },
};

glm::vec2 texcoords[]{
	{ 0, 0 },
	{ 0, 1 },
	{ 1, 0 },
	{ 0, 1 },
	{ 1, 0 }
};

const char* vertex_shader =
"#version 430 core\n"
"in vec3 position;"
"void main() {"
"  gl_Position = vec4(position, 1.0);"
"}";

const char* fragment_shader =
"#version 430 core\n"
"out vec4 color;"
"void main() {"
"  color = vec4(1.0, 0.0, 0.0, 1.0);"
"}";

int main(int argc, char** argv)
{
	LOG("APPLICATION Started...");
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	

	neu::g_renderer.CreateWindow("Neumont", 800, 600, false);
	LOG("WINDOW INITIALIZED");

	// create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(neu::Vector3), colors, GL_STATIC_DRAW);

	GLuint tvbo = 0;
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), texcoords, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader
	std::shared_ptr<neu::Shader> vs = neu::g_resources.Get<neu::Shader>("shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<neu::Shader> fs = neu::g_resources.Get<neu::Shader>("shaders/basic.frag", GL_FRAGMENT_SHADER);
	 
	

	// create program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs->m_shader);
	glAttachShader(program, vs->m_shader);
	glLinkProgram(program);
	glUseProgram(program);


	// create texture
	std::shared_ptr<neu::Texture> texture1 = neu::g_resources.Get <neu::Texture>("textures/llama.jpg");
	std::shared_ptr<neu::Texture> texture2 = neu::g_resources.Get <neu::Texture>("textures/wood.png");
	texture2->Bind();



	GLint uniform1 = glGetUniformLocation(program, "scale");
	GLint uniform2 = glGetUniformLocation(program, "tint");
	GLint uniform3 = glGetUniformLocation(program, "transform");

	glUniform3f(uniform2, 1, 0, 0);



	glm::mat4 mx{ 1 };
	// mx = glm::scale(glm::vec3( 0.5, 0.5, 0.5 ));
	mx = glm::eulerAngleXYZ(0.0f, 0.0f, 2.0f);
	glUniformMatrix4fv(uniform3, 1, GL_FALSE, glm::value_ptr(mx));



	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::State::Pressed) quit = true;

			glUniform1f(uniform1, std::sin(neu::g_time.time));

		neu::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		neu::g_renderer.EndFrame();
		
	}
	neu::Engine::Instance().Shutdown();

	return 0;
}