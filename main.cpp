

#include "pch.h"
#include "Snake.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window, char &b)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		b = 'w';
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			b = 'a';
		}
		else {
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				b = 's';
			}
			else {
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
					b = 'd';
				}
				else {
					b = 'u';
				}
			}
		}

	}
		
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int cam[COLONNE][RIGHE];
// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

void stampaMappa() {
	
	for (int i = 0; i < COLONNE; i++) {
		for (int j = 0; j < RIGHE; j++) {
			//stampa prima riga ultima riga
			if (i == 0 || i == COLONNE - 1) {
				cam[i][j] = '1';
			}
			else {
				//stampa colonna ultima colonna
				if (j == 0 || j == COLONNE - 1) {
					cam[i][j] = '1';
				}
				else {
					//stampa spazi
					cam[i][j] = ' ';
				}
			}
		}
		//va capo
		std::cout << std::endl;
	}
}








int main()
{
	Shader aSha;
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------


	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	glewInit();
	GLuint o = aSha.LoadShaders("vertex.glsl", "shafragm.glsl");

	glEnable(GL_DEPTH_TEST);



	float mat[50][50];
	GLuint VBO, VAO, EBO;

	float vertices[12] = {			// positions          // colors           // texture coords
		 -0.967f,  1.0f, 0.0f,
		-0.967f, 0.967f, 0.0f,
		-1.0f, 0.967f, 0.0f,
		-1.0f,  1.0f, 0.0f, };
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	stampaMappa();
	Snake ActSna(10, 10, cam);
	pos fru;
	srand(time(NULL));
	fru.x = rand() % (RIGHE - 10) + 1;
	fru.y = rand() % (COLONNE - 10) + 1;

	char k = 'w';
	bool fine = false;
	cam[fru.y][fru.x] = 'p';


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window) && 1 && !ActSna.colpito() && !fine)
	{
	


		if (ActSna.getX() == fru.x && ActSna.getY() == fru.y) {
			ActSna.mangia();
			fru.x = rand() % (RIGHE - 10) + 1;
			fru.y = rand() % (COLONNE - 10) + 1;
			cam[fru.y][fru.x] = 'p';
			

		}
		char b;
		processInput(window,b);
		if (b!='u') {
			
			if (b == 'a' && k!='d') {
				ActSna.sinistra();
				k = b;
			}
			if (b == 'w' && k!='s') {
				ActSna.avanti();
				k = b;
			}
			if (b == 's' && k!='w') {
				ActSna.indietro();
				k = b;
			}
			if (b == 'd' && k!='a') {
				ActSna.destra();
				k = b;
			}


		}
		else {
			if (k == 'a') {
				ActSna.sinistra();
			}
			if (k == 'w') {
				ActSna.avanti();
			}
			if (k == 's') {
				ActSna.indietro();
			}
			if (k == 'd') {
				ActSna.destra();
			}
		}
		if (ActSna.getX() >= COLONNE || ActSna.getX() <= 0 || ActSna.getY() >= RIGHE || ActSna.getY() <= 0) {
			fine = true;
		}
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < COLONNE; i++) {
			for (int j = 0; j < RIGHE; j++) {
				if (cam[i][j] == '1') {
					glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
					transform = glm::translate(transform, glm::vec3(j*0.033f, -i*0.033f, 0.0f));
					int vertexColorLocation = glGetUniformLocation(o, "ourColor");
					glUniform4f(vertexColorLocation, 0.0f, 1.0, 0.0f, 1.0f);

					// draw our first triangle
					glUseProgram(o);
					unsigned int transformLoc = glGetUniformLocation(o, "transform");
					glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

					glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
					//glDrawArrays(GL_TRIANGLES, 0, 6);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				}
				if (cam[i][j] == 'v') {
					glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
					transform = glm::translate(transform, glm::vec3(j*0.033f, -i * 0.033f, 0.0f));
					int vertexColorLocation = glGetUniformLocation(o, "ourColor");
					glUniform4f(vertexColorLocation, 0.0f, 0.0, 1.0f, 1.0f);

					// draw our first triangle
					glUseProgram(o);
					unsigned int transformLoc = glGetUniformLocation(o, "transform");
					glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

					glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
					//glDrawArrays(GL_TRIANGLES, 0, 6);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				}
				if (cam[i][j] == ' ') {
					glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
					transform = glm::translate(transform, glm::vec3(j*0.033f, -i * 0.033f, 0.0f));
					int vertexColorLocation = glGetUniformLocation(o, "ourColor");
					glUniform4f(vertexColorLocation, 0.0f, 0.8, 1.0f, 1.0f);

					// draw our first triangle
					glUseProgram(o);
					unsigned int transformLoc = glGetUniformLocation(o, "transform");
					glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

					glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
					//glDrawArrays(GL_TRIANGLES, 0, 6);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				}
				if (cam[i][j] == 'p') {
					glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
					transform = glm::translate(transform, glm::vec3(j*0.033f, -i * 0.033f, 0.0f));
					int vertexColorLocation = glGetUniformLocation(o, "ourColor");
					glUniform4f(vertexColorLocation, 0.8f, 0.9, 1.0f, 1.0f);

					// draw our first triangle
					glUseProgram(o);
					unsigned int transformLoc = glGetUniformLocation(o, "transform");
					glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

					glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
					//glDrawArrays(GL_TRIANGLES, 0, 6);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				}
			}

		}
		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(100);
		
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);


	glfwTerminate();
	return 0;

}
