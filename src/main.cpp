#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath> // Für cos/sin

static void error_callback(int error, const char *description) {
	std::cerr << "Error: " << description << std::endl;
}


float angle = 45;
float cosA = cos(angle);
float sinA = sin(angle);

float rotationMatrixX[] = {
	1.0f, 0.0f,  0.0f, 0.0f,
	0.0f, cosA, -sinA, 0.0f,
	0.0f, sinA,  cosA, 0.0f,
	0.0f, 0.0f,  0.0f, 1.0f
};

// Vertex Shader: empfängt Rotationsmatrix als Uniform
const char *vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vertexColor;
uniform mat4 rotation;

void main() {
	gl_Position = rotation * vec4(aPos, 1.0);
	vertexColor = aColor;
}
)";

const char *fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;
void main() {
	FragColor = vec4(vertexColor, 1.0);
}
)";

// Ursprüngliche Dreiecks-Vertices
float vertices[] = {
	// Position            // Farbe (RGB)
	// Front Face (rot)
	-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,

	// Back Face (grün)
	-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,

	// Left Face (blau)
	-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

	// Right Face (gelb)
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,

	// Top Face (cyan)
	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,

	// Bottom Face (magenta)
	-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
};

int main() {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Rotating Triangle", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Shader kompilieren
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Fehler-Check für Vertex Shader
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Vertex Shader compilation failed:\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// Fehler-Check für Fragment Shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Fragment Shader compilation failed:\n" << infoLog << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Fehler-Check für Shader Program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Shader Program linking failed:\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VAO, VBO erstellen
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Attribut-Zeiger setzen (3 floats pro Vertex)
	// Position: 3 floats, offset 0, stride 6 floats
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Farbe: 3 floats, offset nach 3 floats, stride 6 floats
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Hole Uniform-Location der Rotationsmatrix
	GLint rotationLoc = glGetUniformLocation(shaderProgram, "rotation");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		// Ganz am Anfang clear, und zwar **Farbe + Depth**
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rotation, Uniform setzen, Shader aktivieren ...
		float time = glfwGetTime();
		float angle = time;
		float cosA = std::cos(angle);
		float sinA = std::sin(angle);

		float rotationMatrix[] = {
			cosA, 0.0f, sinA, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
		   -sinA, 0.0f, cosA, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
	   };

		glUseProgram(shaderProgram);
		glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, rotationMatrix);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// Aufräumen
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
