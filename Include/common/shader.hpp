#ifndef SHADER_HPP
#define SHADER_HPP

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path, const char * geometry_file_path = NULL,const char * tess_control_flie_path = NULL,
	const char * tess_eval_file_path = NULL);

#endif
