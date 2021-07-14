#include <ShadeGL.h>
#include <Shader.h>
#include <Camera.h>
#include <VBO.h>
#include <VAO.h>
#include <EBO.h>
#include <Texture.h>

#define WIDTH 1920
#define HEIGHT 1080

GLFWwindow* window;
GLFWmonitor* monitor;
bool running, fullscreen;
std::map<int, key> keyMap;


// Vertices coordinates
GLfloat vertices[] =
        { //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
                -1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
                -1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
                1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
                1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 1, 2,
                0, 2, 3
        };

GLfloat lightVertices[] =
        { //     COORDINATES     //
                -0.1f, -0.1f,  0.1f,
                -0.1f, -0.1f, -0.1f,
                0.1f, -0.1f, -0.1f,
                0.1f, -0.1f,  0.1f,
                -0.1f,  0.1f,  0.1f,
                -0.1f,  0.1f, -0.1f,
                0.1f,  0.1f, -0.1f,
                0.1f,  0.1f,  0.1f
        };

GLuint lightIndices[] =
        {
                0, 1, 2,
                0, 2, 3,
                0, 4, 7,
                0, 7, 3,
                3, 7, 6,
                3, 6, 2,
                2, 6, 5,
                2, 5, 1,
                1, 5, 4,
                1, 4, 0,
                4, 5, 6,
                4, 6, 7
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
    vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    vao1.LinkAttrib(vbo1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    vao1.Unbind();
    vbo1.Unbind();
    ebo1.Unbind();

    // Shader for light cube
    Shader lightShader("../shaders/light_fragment.glsl", "../shaders/light_vertex.glsl");
    // Generates Vertex Array Object and binds it
    VAO lightVAO;
    lightVAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    // Generates Element Buffer Object and links it to indices
    EBO lightEBO(lightIndices, sizeof(lightIndices));
    // Links VBO attributes such as coordinates and colors to VAO
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    // Unbind all to prevent accidentally modifying them
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();



    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.use();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.programID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.programID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


    // Texture
    Texture tex("../resources/planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    tex.texUnit(shader, "tex0", 0);
    Texture spectex("../resources/planks_spec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    tex.texUnit(shader, "tex1", 1);



    // Uniforms
    GLuint uniID = glGetUniformLocation(shader.programID, "scale");

    // Camera
    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 1.0f, 2.0f), 0.075, 75.f);

    // Run main loop until user terminates the window
    while (!glfwWindowShouldClose(window)) {
        // Clear Window with clear color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Check for user inputs
        input();
        camera.inputs(window);

        glUniform1f(uniID, 0.5f);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // DRAW | Render SOMETHING
        glClearError();
        shader.use();
        camera.matrix(shader, "camMatrix");
        spectex.Bind();

        tex.Bind();
        vao1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glCheckError();

        glClearError();
        lightShader.use();
        camera.matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glCheckError();

        // Swap buffers
        glfwSwapBuffers(window);
    }
    // Call Delete()
    vao1.Delete();
    vbo1.Delete();
    ebo1.Delete();
    tex.Delete();
    spectex.Delete();
    shader.Delete();

    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    lightShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


