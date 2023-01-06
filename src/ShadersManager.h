#pragma once

#include <vector>

class ShadersManager final
{
public:
	ShadersManager() = default;
	~ShadersManager();

	std::vector<unsigned int> getVertexShaders() const { return vertex_shaders_; }
	std::vector<unsigned int> getFragmentShaders() const { return fragment_shaders_; }
	std::vector<unsigned int> getPrograms() const { return programs_; }

	unsigned int createVertexShader(const char* source);
	unsigned int createFragmentShader(const char* source);

	unsigned int createProgram(
		unsigned int vertex_shader,
		unsigned int fragment_shader,
		bool delete_shaders);

	void deleteShader(unsigned int id);
	void deleteProgram(unsigned int id);

	void deleteAllVertexShaders();
	void deleteAllFragmentShaders();
	void deleteAllShaders();
	void deleteAllPrograms();
private:
	unsigned int create_shader(const char *source, int type);

	bool has_shader(unsigned int shader_id) const;
	bool has_program(unsigned int program_id) const;

private:
	std::vector<unsigned int> vertex_shaders_;
	std::vector<unsigned int> fragment_shaders_;
	std::vector<unsigned int> programs_;
	bool check_shader_compilation(unsigned int shader);
	bool check_shader_linking(unsigned int program_id);
};
