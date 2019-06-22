#include "Game.h"

int Game::width = 800;
int Game::height = 600;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_C && action == GLFW_RELEASE) {
		
	}
}

Game::Game()
{
	if (!glfwInit()) {
		std::cout << "GLFW failed to initialize" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwSetErrorCallback(error_callback);
	
	window = glfwCreateWindow(Game::width, Game::height, "OpenGL Engine", NULL, NULL);
	if (!window) {
		std::cout << "Couldn't create window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, keyCallback);
	glewExperimental = GL_TRUE;
	glewInit();

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	
	glEnable(GL_MULTISAMPLE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLint maxPatchVerts = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxPatchVerts);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);

	printf("Renderer: %s\nVersion: %s\n", renderer, version);
	std::cout << "Max Patch Vertices: " << maxPatchVerts << std::endl;
	
	scene = new Scene();
	scene->init();
/*
	Texture texture;
	texture.id = scene->getTextureFromFile("grass.jpg", "assets/textures");
	texture.path = "assets/textures/grass.jpg";
	texture.type = "texture_diffuse";
	Texture dirt;
	dirt.id = scene->getTextureFromFile("dirt.png", "assets/textures");
	dirt.path = "assets/textures/dirt.png";
	dirt.type = "texture_diffuse";

	std::mt19937 randyrand(time(NULL));
	auto realRand = std::bind(std::uniform_int_distribution<int>(0, INT_MAX), randyrand);
	int seed = realRand();
	terrain = new Terrain(0, 0, texture, seed, dirt);
	scene->processTerrain(*terrain);
	water = new WaterTile(0, 0);
	scene->processWaterTile(*water);
	*/
	this->renderer.scene = scene;
	this->renderer.init();
	
	player = new Player(&scene->view);
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);
}


/*
TODO
Optimizations
Components
Inhibiting trees from spawning below water level
Multitexturing/Terrain coloring
Water?
Skybox?
*/

Game::~Game()
{
}

void Game::loop()
{
	long ns = 1000000000 / UPS;
	uint64_t lastTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	double lag = 0.0;
	int frames = 0;
	int updates = 0;
	uint64_t timer = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	while (!glfwWindowShouldClose(window)) {
		uint64_t now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		uint64_t elapsed = now - lastTime;
		lastTime = now;
		lag += elapsed;
		glfwPollEvents();
		process();
		while (lag >= ns) {
			update(ns/lag);
			updates++;
			lag -= ns;
		}
		render();
		frames++;
		if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() - timer >= 1000000000) {
			timer += 1000000000;
			std::cout << "FPS: " << frames << ", UPS: " << updates << std::endl;
			updates = 0;
			frames = 0;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)glfwSetWindowShouldClose(window, 1);
	}
}

void Game::render()
{
	glEnable(GL_CLIP_DISTANCE0);
	renderer.render(*scene, window);
	glfwSwapBuffers(window);
}

bool reloadedLastFrame = false;

void Game::update(double delta)
{

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS &&!reloadedLastFrame) {
		scene->shaders[1].reload();
		reloadedLastFrame = true;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
		reloadedLastFrame = false;
	}
	player->update(delta,window, &renderer.world->levels[renderer.world->activeLevel]);
	scene->view.setPosition(player->position);
	scene->updateCamera(delta, window);
	scene->updateEntities(&renderer.world->levels[renderer.world->activeLevel], delta);
	renderer.world->levels[renderer.world->activeLevel].updateEntities(delta);
}

void Game::process()
{
	/*scene->processTerrain(*terrain);
	scene->processWaterTile(*water);*/
}

void Game::cleanup()
{
	glfwTerminate();
}
