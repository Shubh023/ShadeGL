#include <ShadeGL.h>
#include <Shader.h>
#include <Camera.h>
#include <VBO.h>
#include <VAO.h>
#include <EBO.h>


#define WIDTH 1280
#define HEIGHT 720

GLFWwindow* window;
GLFWmonitor* monitor;
bool running, fullscreen;
std::map<int, key> keyMap;

// Vertices coordinates
GLfloat vertices[] =
{
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Lower right triangle
        5, 4, 1 // Upper triangle
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

    VAO vao1;
    vao1.Bind();
    VBO vbo1(vertices, sizeof(vertices));
    EBO ebo1(indices, sizeof(indices));
    vao1.LinkVBO(vbo1, 0);
    vao1.Unbind();
    vbo1.Unbind();
    ebo1.Unbind();

    // Handle Shaders
    Shader shader("../shaders/fragment.glsl", "../shaders/vertex.glsl");

    // Camera
    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    // Run main loop until user terminates the window
    while (!glfwWindowShouldClose(window)) {
        /**
         * Update Stuff on window
         */
        // Handle Shaders
        shader.use();

        camera.matrix(45.0f, 0.1f, 100.f, shader, "camMatrix");
        camera.inputs(window);

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
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glCheckError();

        // Swap buffers
        glfwSwapBuffers(window);
    }
    // Call Delete()
    vao1.Delete();
    vbo1.Delete();
    ebo1.Delete();
    shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


