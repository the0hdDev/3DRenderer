#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath> // Für cos/sin

// GLFW Fehler-Callback
static void error_callback(int error, const char *description) {
	std::cerr << "Error: " << description << std::endl;
}

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

// Alle Cube-Vertices und Farben
float vertices[] = {
	// Position             // Farbe
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

	// OpenGL Context erstellen
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Rotating Cube", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Shader kompilieren und Programm erstellen
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

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

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Fragment Shader compilation failed:\n" << infoLog << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Shader Program linking failed:\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VAO und VBO einrichten
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position Attribut
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Farb-Attribut
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Uniform-Location abrufen
	GLint rotationLoc = glGetUniformLocation(shaderProgram, "rotation");

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Dynamischer Y-Winkel
		float angleY = glfwGetTime();
		float cosY = std::cos(angleY);
		float sinY = std::sin(angleY);

		// Statischer X-Winkel (45°)
		float angleX = 45.0f;
		float cosX = std::cos(angleX);
		float sinX = std::sin(angleX);

		// Rotation um X
		float rotX[] = {
			1,    0,     0,    0,
			0,  cosX, -sinX,   0,
			0,  sinX,  cosX,   0,
			0,    0,     0,    1
		};

		// Rotation um Y
		float rotY[] = {
			cosY, 0, sinY, 0,
			0,    1, 0,    0,
		   -sinY, 0, cosY, 0,
			0,    0, 0,    1
		};

		// Multiplikation: rotY * rotX
		float rotationMatrix[16];
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				rotationMatrix[col + row * 4] =
					rotY[0 + row * 4] * rotX[col + 0] +
					rotY[1 + row * 4] * rotX[col + 4] +
					rotY[2 + row * 4] * rotX[col + 8] +
					rotY[3 + row * 4] * rotX[col +12];
			}
		}

		// Shader aktivieren und Uniform setzen
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, rotationMatrix);

		// Cube zeichnen
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Ressourcen freigeben
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
