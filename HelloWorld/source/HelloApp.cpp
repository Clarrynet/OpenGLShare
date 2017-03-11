//
//  HelloApp.cpp
//  Cornell University Game Library (CUGL)
//
//  This is the implementation file for the custom application. This is the
//  definition of your root (and in this case only) class.
//
//  CUGL zlib License:
//      This software is provided 'as-is', without any express or implied
//      warranty.  In no event will the authors be held liable for any damages
//      arising from the use of this software.
//
//      Permission is granted to anyone to use this software for any purpose,
//      including commercial applications, and to alter it and redistribute it
//      freely, subject to the following restrictions:
//
//      1. The origin of this software must not be misrepresented; you must not
//      claim that you wrote the original software. If you use this software
//      in a product, an acknowledgment in the product documentation would be
//      appreciated but is not required.
//
//      2. Altered source versions must be plainly marked as such, and must not
//      be misrepresented as being the original software.
//
//      3. This notice may not be removed or altered from any source distribution.
//
//  Author: Walker White
//  Version: 1/8/17
//
// Include the class header, which includes all of the CUGL classes
#include "HelloApp.h"
#include <cugl/base/CUBase.h>

// Add support for simple random number generation
#include <cstdlib>
#include <ctime>

// This keeps us from having to write cugl:: all the time
using namespace cugl;

// The number of frames before moving the logo to a new position
#define TIME_STEP 60
// This is adjusted by screen aspect ratio to get the height
#define GAME_WIDTH 1024
//Try putting in gl commands (drl224)
static const GLfloat g_vertex_buffer_data[] = {
	-0.5f, -0.50f, -0.50f, // triangle 1 : begin
	-0.50f, -0.50f, 0.50f,
	-0.50f, 0.50f, 0.50f, // triangle 1 : end
	0.50f, 0.50f, -0.50f, // triangle 2 : begin
	-0.50f, -0.50f, -0.50f,
	-0.50f, 0.50f, -0.50f, // triangle 2 : end
	0.50f, -0.50f, 0.50f,
	-0.50f, -0.50f, -0.50f,
	0.50f, -0.50f, -0.50f,
	0.50f, 0.50f, -0.50f,
	0.50f, -0.50f, -0.50f,
	-0.50f, -0.50f, -0.50f,
	-0.50f, -0.50f, -0.50f,
	-0.50f, 0.50f, 0.50f,
	-0.50f, 0.50f, -0.50f,
	0.50f, -0.50f, 0.50f,
	-0.50f, -0.50f, 0.50f,
	-0.50f, -0.50f, -0.50f,
	-0.50f, 0.50f, 0.50f,
	-0.50f, -0.50f, 0.50f,
	0.50f, -0.50f, 0.50f,
	0.50f, 0.50f, 0.50f,
	0.50f, -0.50f, -0.50f,
	0.50f, 0.50f, -0.50f,
	0.50f, -0.50f, -0.50f,
	0.50f, 0.50f, 0.50f,
	0.50f, -0.50f, 0.50f,
	0.50f, 0.50f, 0.50f,
	0.50f, 0.50f, -0.50f,
	-0.50f, 0.50f, -0.50f,
	0.50f, 0.50f, 0.50f,
	-0.50f, 0.50f, -0.50f,
	-0.50f, 0.50f, 0.50f,
	0.50f, 0.50f, 0.50f,
	-0.50f, 0.50f, 0.50f,
	0.50f, -0.50f, 0.50f
};

static const GLfloat g_uv_buffer_data[] = {
	//0.000059f, 1.0f - 0.000004f,
	//0.000103f, 1.0f - 0.336048f,
	//0.335973f, 1.0f - 0.335903f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	//1.000023f, 1.0f - 0.000013f,
	//0.667979f, 1.0f - 0.335851f,
	//0.999958f, 1.0f - 0.336064f,
	1.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	//0.667979f, 1.0f - 0.335851f,
	//0.336024f, 1.0f - 0.671877f,
	//0.667969f, 1.0f - 0.671889f,
	1.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	//1.000023f, 1.0f - 0.000013f,
	//0.668104f, 1.0f - 0.000013f,
	//0.667979f, 1.0f - 0.335851f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	//0.000059f, 1.0f - 0.000004f,
	//0.335973f, 1.0f - 0.335903f,
	//0.336098f, 1.0f - 0.000071f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	//0.667979f, 1.0f - 0.335851f,
	//0.335973f, 1.0f - 0.335903f,
	//0.336024f, 1.0f - 0.671877f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	//1.000004f, 1.0f - 0.671847f,
	//0.999958f, 1.0f - 0.336064f,
	//0.667979f, 1.0f - 0.335851f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	//0.668104f, 1.0f - 0.000013f,
	//0.335973f, 1.0f - 0.335903f,
	//0.667979f, 1.0f - 0.335851f,
	1.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	//0.335973f, 1.0f - 0.335903f,
	//0.668104f, 1.0f - 0.000013f,
	//0.336098f, 1.0f - 0.000071f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	//0.000103f, 1.0f - 0.336048f,
	//0.000004f, 1.0f - 0.671870f,
	//0.336024f, 1.0f - 0.671877f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	//0.000103f, 1.0f - 0.336048f,
	//0.336024f, 1.0f - 0.671877f,
	//0.335973f, 1.0f - 0.335903f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	//0.667969f, 1.0f - 0.671889f,
	//1.000004f, 1.0f - 0.671847f,
	//0.667979f, 1.0f - 0.335851f
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f
};
// This will identify our vertex buffer
GLuint vertexbuffer;
// This will identify our color buffer
GLuint colorbuffer;
// This will identify our uv buffer
GLuint uvbuffer;
/**
* The method called after OpenGL is initialized, but before running the application.
*
* This is the method in which all user-defined program intialization should
* take place.  You should not create a new init() method.
*
* When overriding this method, you should call the parent method as the
* very last line.  This ensures that the state will transition to FOREGROUND,
* causing the application to run.
*/
void HelloApp::onStartup() {
	Size size = getDisplaySize();
	size *= GAME_WIDTH / size.width;

	// Create a scene graph the same size as the window
	_scene = Scene::alloc(size.width, size.height);
	// get the camera from the scene
	//_camera = PerspectiveCamera::alloc(1, 90);
	// fill the dummy texture
	//_texture = SpriteBatch::getBlankTexture();
	//_texture->initWithFile("texture.JPG");
	//_texture->bind();

	// Create a sprite batch (and background color) to render the scene
	_batch = SpriteBatch::alloc();
	setClearColor(Color4(20, 5, 35, 40));
	_shader = SpriteShader::alloc();
	//_shader->init();
	// Create an asset manager to load all assets
	_assets = AssetManager::alloc();

	// You have to attach the individual loaders for each asset type
	_assets->attach<Texture>(TextureLoader::alloc()->getHook());
	_assets->attach<Font>(FontLoader::alloc()->getHook());

	// This reads the given JSON file and uses it to load all other assets
	_assets->loadDirectory("json/assets.json");

	// Activate mouse or touch screen input as appropriate
	// We have to do this BEFORE the scene, because the scene has a button
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Generate 1 buffer, put the resulting identifier in uvbuffer
	glGenBuffers(1, &colorbuffer);
	// The following commands will talk about our 'uvbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	// Generate 1 buffer, put the resulting identifier in uvbuffer
	glGenBuffers(1, &uvbuffer);
	// The following commands will talk about our 'uvbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);


#if defined (CU_TOUCH_SCREEN)
	Input::activate<Touchscreen>();
#else
	Input::activate<Mouse>();
#endif

	// Build the scene from these assets
	buildScene();

	Application::onStartup();
}

/**
* The method called when the application is ready to quit.
*
* This is the method to dispose of all resources allocated by this
* application.  As a rule of thumb, everything created in onStartup()
* should be deleted here.
*
* When overriding this method, you should call the parent method as the
* very last line.  This ensures that the state will transition to NONE,
* causing the application to be deleted.
*/
void HelloApp::onShutdown() {
	// Delete all smart pointers
	_logo = nullptr;
	_scene = nullptr;
	_batch = nullptr;
	_assets = nullptr;

	// Deativate input
#if defined CU_TOUCH_SCREEN
	Input::deactivate<Touchscreen>();
#else
	Input::deactivate<Mouse>();
#endif
	Application::onShutdown();
}

/**
* The method called to update the application data.
*
* This is your core loop and should be replaced with your custom implementation.
* This method should contain any code that is not an OpenGL call.
*
* When overriding this method, you do not need to call the parent method
* at all. The default implmentation does nothing.
*
* @param timestep  The amount of time (in seconds) since the last frame
*/
void HelloApp::update(float timestep) {
	if (_countdown == 0) {
		// Move the logo about the screen
		Size size = getDisplaySize();
		size *= GAME_WIDTH / size.width;
		float x = (float)(std::rand() % (int)(size.width / 2)) + size.width / 4;
		float y = (float)(std::rand() % (int)(size.height / 2)) + size.height / 8;
		_logo->setPosition(Vec2(x, y));
		_countdown = TIME_STEP * 6;
	}
	else {
		_countdown--;
	}
}

/**
* The method called to draw the application to the screen.
*
* This is your core loop and should be replaced with your custom implementation.
* This method should OpenGL and related drawing calls.
*
* When overriding this method, you do not need to call the parent method
* at all. The default implmentation does nothing.
*/
void HelloApp::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// This takes care of begin/end
	// An array of 3 vectors which represents 3 vertices
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);

	glVertexAttribPointer(
		1,                  // attribute 2. No particular reason for 2, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);



	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);

	glVertexAttribPointer(
		2,                  // attribute 2. No particular reason for 2, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glUseProgram(_shader->getProgram());

	//Set the camera transform
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	int width = getDisplayWidth();
	int height = getDisplayHeight();
	Mat4 ortho = Mat4::createOrthographic(4, 3, 0.1f, 100.0f);
	Mat4 Projection = Mat4::createPerspective(90, (float)width / (float)height, 0.1f, 100.0f);
	Projection = ortho;
	// Camera matrix
	float camerabump = (TIME_STEP * 6.0f - _countdown) / (float)TIME_STEP / 6.0f;
	float theta = 2.0f * M_PI * camerabump;
	float otherbump = ((float)_countdown / (float)TIME_STEP * 6) - 1;
	Mat4 View = Mat4::createLookAt(
		Vec3(2 * cosf(theta), 1.0f, 2 * sinf(theta)), // Camera is at (4,3,3), in World Space
													  //Vec3(-cosf(theta), 0, -(sinf(theta))), // and looks at the origin
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0, 1.0f, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//View = Mat4::IDENTITY;
	//Mat4 Dummy = Mat4()
	// Model matrix : an identity matrix (model will be at the origin)
	Mat4 Model = Mat4::IDENTITY;
	// Our ModelViewProjection : multiplication of our 3 matrices
	Mat4 mvp = Projection * View *Model;
	mvp = Model * View * Projection;
	std::shared_ptr<Texture> texture = _assets->get<Texture>("claw");
	texture->bind();
	GLuint MatrixID = glGetUniformLocation(_shader->getProgram(), "uPerspective");
	// Send our transformation to the currently bound shader, in the "uPerspective" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp.m[0]);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	texture->unbind();

}

/**
* Internal helper to build the scene graph.
*
* Scene graphs are not required.  You could manage all scenes just like
* you do in 3152.  However, they greatly simplify scene management, and
* have become standard in most game engines.
*/
void HelloApp::buildScene() {
	Size size = getDisplaySize();
	size *= GAME_WIDTH / size.width;

	// The logo is actually an image+label.  We need a parent node
	_logo = Node::alloc();

	// Get the image and add it to the node.
	std::shared_ptr<Texture> texture = _assets->get<Texture>("claw");
	std::shared_ptr<PolygonNode> claw = PolygonNode::allocWithTexture(texture);
	claw->setScale(0.1f); // Magic number to rescale asset
	claw->setAnchor(Vec2::ANCHOR_MIDDLE_BOTTOM);
	claw->setPosition(0, 0);
	_logo->addChild(claw);

	// Get the font and make a label for the logo
	std::shared_ptr<Font> font = _assets->get<Font>("charlemagne");
	std::shared_ptr<Label> label = Label::alloc("CUGL", font);
	label->setAnchor(Vec2::ANCHOR_MIDDLE_TOP);
	label->setPosition(15, -15); // Magic numbers for some manual kerning
	_logo->addChild(label);

	// Put the logo in the middle of the screen
	_logo->setAnchor(Vec2::ANCHOR_MIDDLE);
	_logo->setPosition(size.width / 2, size.height / 2);


	// Create a button.  A button has an up image and a down image
	std::shared_ptr<Texture> up = _assets->get<Texture>("close-normal");
	std::shared_ptr<Texture> down = _assets->get<Texture>("close-selected");

	Size bsize = up->getSize();
	std::shared_ptr<Button> button = Button::alloc(PolygonNode::allocWithTexture(up),
		PolygonNode::allocWithTexture(down));

	// Create a callback function for the button
	button->setName("close");
	button->setListener([=](const std::string& name, bool down) {
		// Only quit when the button is released
		if (!down) {
			CULog("Goodbye!");
			this->quit();
		}
	});

	// Position the button in the bottom right corner
	button->setAnchor(Vec2::ANCHOR_MIDDLE);
	button->setPosition(size.width - bsize.width / 2, bsize.height / 2);

	// Add the logo and button to the scene graph
	_scene->addChild(_logo);
	_scene->addChild(button);

	// We can only activate a button AFTER it is added to a scene
	button->activate(1);

	// Start the logo countdown and C-style random number generator
	_countdown = TIME_STEP;
	std::srand((int)std::time(0));
}
