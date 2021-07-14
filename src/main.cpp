#include <glm/glm.hpp>
#include <Mesh.h>
#include <models/floor.h>
#include <models/box.h>
#include <models/skybox.h>
#define WIDTH 1920
#define HEIGHT 1080


GLFWwindow* window;
GLFWmonitor* monitor;
bool running, fullscreen;
std::map<int, key> keyMap;




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

    // Display used OpenGL Version
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Setup Monitor to Primary
    monitor = glfwGetPrimaryMonitor();
    running = true; // States if program is running or not
    fullscreen = false; // States if program should be in fullscreen or not

    // Handle Textures
    Texture textures[] {
        Texture("../resources/planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("../resources/planks_spec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    // Handle Floor
    Shader shader("../shaders/fragment.glsl", "../shaders/vertex.glsl");
    std::vector <Vertex> verts(floor_v, floor_v + sizeof(floor_v) / sizeof(Vertex));
    std::vector <GLuint> ind(floor_i, floor_i + sizeof(floor_i) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    Mesh floor(verts, ind, tex);

    // Handle Light Source
    Shader lightshader("../shaders/light_fragment.glsl", "../shaders/light_vertex.glsl");
    std::vector <Vertex> lightVerts(box_vertices, box_vertices + sizeof(box_vertices) / sizeof(Vertex));
    std::vector <GLuint> lightInd(box_indices, box_indices + sizeof(box_indices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInd, tex);


    // Handle Lighting
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.f, 1.f, 0.f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel = glm::translate(objectModel, objectPos);

    lightshader.use();
    glUniformMatrix4fv(glGetUniformLocation(lightshader.programID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightshader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
    glUniform4f(glGetUniformLocation(shader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.programID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Handle Skybox
    // Create VAO, VBO, and EBO for the skybox
    Shader skyboxShader("../shaders/skybox_fragment.glsl", "../shaders/skybox_vertex.glsl");
    skyboxShader.use();
    glUniform1i(glGetUniformLocation(skyboxShader.programID, "skybox"), 0);

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Creates the cubemap texture object
    unsigned int cubemapTexture;
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // These are very important to prevent seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Cycles through all the textures and attaches them to the cubemap object
    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
                    (
                            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                            0,
                            GL_RGB,
                            width,
                            height,
                            0,
                            GL_RGB,
                            GL_UNSIGNED_BYTE,
                            data
                    );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
            stbi_image_free(data);
        }
    }

    // Uniforms
    GLuint uniID = glGetUniformLocation(shader.programID, "scale");

    // Camera
    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 1.0f, 2.0f)); //, 0.075, 75.f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    glEnable(GL_MULTISAMPLE);


    // Metrics
    double prev = 0.0;
    double curr = 0.0;
    double diff;
    unsigned int ct = 0;

    int vsync = 1;
    glfwSwapInterval(vsync); // Enable or Disable VSYNC

    // Run main loop until user terminates the window
    while (!glfwWindowShouldClose(window)) {

        curr = glfwGetTime();
        diff = curr - prev;
        ct++;
        if (diff >= 1.0 / 30.0)
        {
            std::string FPS = std::to_string((1.0 / diff) * ct);
            std::string ms = std::to_string((diff / ct) * 1000);
            std::string title = "ShadeGL : " + FPS + " FPS " + ms + "ms";
            glfwSetWindowTitle(window, title.c_str());

            prev = curr;
            ct = 0;
            if (!vsync) {
                // Check for user inputs
                input();
                camera.inputs(window);
            }
        }

        // Clear Window with clear color
        glClearColor(0.05f, 0.03f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (vsync) {
            // Check for user inputs
            input();
            camera.inputs(window);
        }

        glUniform1f(uniID, 0.5f);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // DRAW | Render SOMETHING
        glClearError();
        floor.Draw(shader, camera);
        light.Draw(lightshader, camera);
        glCheckError();

        // Since the cubemap will always have a depth of 1.0, we need that equal sign so it doesn't get discarded
        glDepthFunc(GL_LEQUAL);

        skyboxShader.use();
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        // We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
        // The last row and column affect the translation of the skybox (which we don't want to affect)
        view = glm::mat4(glm::mat3(glm::lookAt(camera.position, camera.position + camera.orientation, camera.up)));
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
        // where an object is present (a depth of 1.0f will always fail against any object's depth value)
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Switch back to the normal depth function
        glDepthFunc(GL_LESS);

        // Swap buffers
        glfwSwapBuffers(window);
    }
    // Call Delete()
    shader.Delete();
    skyboxShader.Delete();
    lightshader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


