#include "Game.h"

int Game::width = 800;
int Game::height = 600;
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
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
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glClearColor(0.2f, 0.8f, 1.0f, 1.0f);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);

	printf("Renderer: %s\nVersion: %s\n", renderer, version);

	
	
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

int state = GLFW_RELEASE;

void Game::update(double delta)
{
	player->update(delta, window, &renderer.world->levels[renderer.world->activeLevel]);
	scene->updateCamera(delta, window);
	scene->updateEntities(delta);
	renderer.world->levels[renderer.world->activeLevel].updateEntities(delta);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && state!=GLFW_PRESS) {
		renderer.world->activeLevel = (renderer.world->activeLevel == 0) ? 1 : 0;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		renderer.world->levels[renderer.world->activeLevel].pLights[0].position.x += 0.1f;
	}
	state = glfwGetKey(window, GLFW_KEY_E);
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
