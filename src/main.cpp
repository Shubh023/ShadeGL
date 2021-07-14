#include <ShadeGL.h>
#include <Shader.h>
#include <Camera.h>
#include <VBO.h>
#include <VAO.h>
#include <EBO.h>
#include <Texture.h>

#define WIDTH 1280
#define HEIGHT 720

GLFWwindow* window;
GLFWmonitor* monitor;
bool running, fullscreen;
std::map<int, key> keyMap;


// Vertices coordinates
GLfloat vertices[] =
        { //     COORDINATES     /        COLORS      /   TexCoord  //
                -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
                -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
                0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
                0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
                0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 1, 2,
                0, 2, 3,
                0, 1, 4,
                1, 2, 4,
                2, 3, 4,
                3, 0, 4
        };



void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void input() {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        running = false;
        glfwSetWindowShouldClose(window, 1);
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && keyMap[GLFW_KEY_F].prev) {
        if (!fullscreen)
            glfwSetWindowMonitor(window, monitor, 0, 0, WIDTH, HEIGHT, 0);
        if (fullscreen)
            glfwSetWindowMonitor(window, NULL, 0, 0, WIDTH, HEIGHT, 0);
        fullscreen = !fullscreen;
    }
    keyMap[GLFW_KEY_F].prev = glfwGetKey(window, GLFW_KEY_F);
}


int main() {
    // Greet on the terminal
    std::cout << "Hello, Welcome to ShadeGL !" << std::endl;

    // Setup GLFW
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Init GLFW
    if (!glfwInit())
        std::cout << "Failed to initialize GLFW" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create Window
    window = glfwCreateWindow(WIDTH, HEIGHT, "ShadeGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to open window GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Init GLEW
    glewExperimental = true;
    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Display used OpenGL Version
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Setup Monitor to Primary
    monitor = glfwGetPrimaryMonitor();
    running = true; // States if program is running or not
    fullscreen = false; // States if program should be in fullscreen or not

    // Handle Shaders
    Shader shader("../shaders/fragment.glsl", "../shaders/vertex.glsl");

    // Handle VAO, VBO, EBO
    VAO vao1;
    vao1.Bind();
    VBO vbo1(vertices, sizeof(vertices));
    EBO ebo1(indices, sizeof(indices));
    vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao1.Unbind();
    vbo1.Unbind();
    ebo1.Unbind();

    // Texture
    Texture tex("../resources/512.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    tex.texUnit(shader, "tex0", 0);

    // Uniforms
    GLuint uniID = glGetUniformLocation(shader.programID, "scale");

    // Camera
    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 10.0f), 0.075, 75.f);

    // Run main loop until user terminates the window
    while (!glfwWindowShouldClose(window)) {
        /**
         * Update Stuff on window
         */
        // Handle Shaders
        shader.use();

        // Uniform
        glUniform1f(uniID, 0.65f);

        // Texture
        tex.Bind();

        // Camera
        camera.inputs(window);
        camera.matrix(shader, "camMatrix");
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        /**
         * Check for user inputs
         */
        input();


        /**
         * Render Stuff
         */
        // Clear Window with clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearError();
        // DRAW | Render SOMETHING
        vao1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glCheckError();

        // Swap buffers
        glfwSwapBuffers(window);
    }
    // Call Delete()
    vao1.Delete();
    vbo1.Delete();
    ebo1.Delete();
    tex.Delete();
    shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


