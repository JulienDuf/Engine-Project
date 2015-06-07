#pragma once

class Window {

private:
	GLFWwindow* window;
public:

	Window(int w, int h, const char* nom) {

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(w, h, nom, NULL, NULL);
		glfwMakeContextCurrent(window);

	}

	// true open
	// false close
	bool windowState() {
		return glfwWindowShouldClose(window);
	}

	void renderWindow() {
		glfwSwapBuffers(window);
	}
};