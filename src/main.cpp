#include <glm/glm.hpp>
#include <Mesh.h>
#include <Transform.h>
#include <models/floor.h>
#include <models/box.h>
#include <models/rectangle.h>
#include <models/skybox.h>

#define ENABLE_SKYBOX 0
#define ENABLE_FULLSCREEN 1
#define VSYNC 1

GLFWwindow* window;
GLFWmonitor* monitor;
bool running, light_sel = false;
unsigned int window_width = 1980;
unsigned int window_height = 1080;

unsigned int samples = 8;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

glm::vec3 gpos = glm::vec3();
glm::vec3 gorientation = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 gup = glm::vec3(0.0f, 1.0f, 0.0f);
float gspeed = 0.1f;
int gsel = 0;

glm::vec3 input() {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        running = false;
        glfwSetWindowShouldClose(window, 1);
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        light_sel = !light_sel;
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        gsel = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        gsel = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        gsel = 2;
    }

    if (light_sel) {

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            gpos = glm::vec3(0.0f, 0.75f, 0.0f);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            gpos += gspeed * gorientation;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            gpos += gspeed * -glm::normalize(glm::cross(gorientation, gup));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            gpos += gspeed * -gorientation;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            gpos += gspeed * glm::normalize(glm::cross(gorientation, gup));
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            gpos += gspeed * gup;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            gpos += gspeed * -gup;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            gspeed = 0.4f;
        } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
            gspeed = 0.1f;
        }
    }
}


int main() {
    // Greet on the terminal
    std::cout << "Hello, Welcome to ShadeGL !" << std::endl;

    // Init GLFW
    if (!glfwInit())
    std::cout << "Failed to initialize GLFW" << std::endl;

    // Setup GLFW
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Setup Monitor to Primary
    monitor = glfwGetPrimaryMonitor();
    running = true; // States if program is running or not

    // Handle case where we want to render at the maximum monitor resolution aka Fullscreen :-)
    if (ENABLE_FULLSCREEN) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        window_width = mode->width;
        window_height = mode->height;
    }
    std::cout <<  "Using Window Size : " <<  window_width << " x " << window_height << std::endl;

    // Create GLFW Window
    window = glfwCreateWindow(window_width, window_height, "ShadeGL", NULL, NULL);
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

    /**
     * Handle Textures
     */
    Texture floor_textures[] {
        Texture("../resources/planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("../resources/planks_spec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    /**
     * Handle Meshes and other objects
     */
    // Handle Floor Mesh
    Shader shader("../shaders/fragment.glsl", "../shaders/vertex.glsl");
    std::vector <Vertex> floor_verts(floor_v, floor_v + sizeof(floor_v) / sizeof(Vertex));
    std::vector <GLuint> floor_ind(floor_i, floor_i + sizeof(floor_i) / sizeof(GLuint));
    std::vector <Texture> floor_tex(floor_textures, floor_textures + sizeof(floor_textures) / sizeof(Texture));
    Mesh floor(floor_verts, floor_ind, floor_tex);

    /*
    // Handle cube mesh
    Shader cube_shader("../shaders/box_fragment.glsl", "../shaders/box_vertex.glsl");
    std::vector <Vertex> boxVerts(box_vertices, box_vertices + sizeof(box_vertices) / sizeof(Vertex));
    std::vector <GLuint> boxInd(box_indices, box_indices + sizeof(box_indices) / sizeof(GLuint));
    std::vector <Texture> box_tex(box_textures, box_textures + sizeof(box_textures) / sizeof(Texture));
    Mesh cube(boxVerts, boxInd, box_tex);
    */

    // Handle Light Source
    Shader lightshader("../shaders/light_fragment.glsl", "../shaders/light_vertex.glsl");
    std::vector <Vertex> lightVerts(box_vertices, box_vertices + sizeof(box_vertices) / sizeof(Vertex));
    std::vector <GLuint> lightInd(box_indices, box_indices + sizeof(box_indices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInd, floor_tex);


    // Handle Lighting
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.f, 0.75f, 0.f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 objectModel = glm::mat4(1.0f);
    Transform transform;

    glm::mat4 objectTransform = transform.model();
    objectModel = glm::translate(objectModel, objectPos);

    lightshader.use();
    glUniformMatrix4fv(glGetUniformLocation(lightshader.programID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightshader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniformMatrix4fv(glGetUniformLocation(lightshader.programID, "transform"), 1, GL_FALSE, glm::value_ptr(objectTransform));

    shader.use();
    glUniform1i(glGetUniformLocation(shader.programID, "gsel"), 2);
    glUniformMatrix4fv(glGetUniformLocation(shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
    glUniform4f(glGetUniformLocation(shader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.programID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Handle Skybox
    Shader skyboxshader("../shaders/skybox_fragment.glsl", "../shaders/skybox_vertex.glsl");
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    // Creates the cubemap texture object
    unsigned int cubemapTexture;
    if (ENABLE_SKYBOX) {
        // Create VAO, VBO, and EBO for the skybox
        skyboxshader.use();
        glUniform1i(glGetUniformLocation(skyboxshader.programID, "skybox"), 0);
        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glGenBuffers(1, &skyboxEBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skybox_indices), &skybox_indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenTextures(1, &cubemapTexture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        for (unsigned int i = 0; i < 6; i++) {
            int width, height, nrChannels;
            unsigned char *data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
            if (data) {
                stbi_set_flip_vertically_on_load(false);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            } else {
                std::cout << "Failed to load skybox texture: " << facesCubemap[i] << std::endl;
                stbi_image_free(data);
            }
        }
    }

    // Uniforms
    GLuint uniID = glGetUniformLocation(shader.programID, "scale");

    // Camera Initialization
    Camera camera(window_width, window_height, glm::vec3(0.0f, 1.0f, 2.0f)); //, 0.075, 75.f);

    /**
     * Toogle GL Features
     */
    // Enabling DEPTH
    glEnable(GL_DEPTH_TEST);
    // Set GL_LESS as depth function to be used
    glDepthFunc(GL_LESS);
    // Enabling Face culling ot front and setting it to CounterClockWise mode
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    // Enable Multisampling
    glEnable(GL_MULTISAMPLE);
    // Enables Gamma Correction
    // glEnable(GL_FRAMEBUFFER_SRGB);

    // Attributes to store Metrics for fps counter
    double prev = 0.0, curr = 0.0, diff;
    unsigned int ct = 0;

    glfwSwapInterval(VSYNC); // Enable or Disable VSYNC


    /**
     * PREPARE FRAMEBUFFER
     */
    // Handle Shader Part
    Shader framebuffershader("../shaders/framebuffer_fragment.glsl", "../shaders/framebuffer_vertex.glsl");
    framebuffershader.use();
    glUniform1i(glGetUniformLocation(framebuffershader.programID, "screenTexture"), 0);

    // Handle VAO & VBO for rectangle used to display the frames
    unsigned int rectVAO, rectVBO;
    glGenVertexArrays(1, &rectVAO);
    glGenBuffers(1, &rectVBO);
    glBindVertexArray(rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), &rectangle_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Creating a Frame Buffer
    unsigned int FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // Creating a Frame Buffer to be applied on the rectangle
    unsigned int framebufferTexture;
    glGenTextures(1, &framebufferTexture);

    // To take full advantage of framebuffer we can use Multisampling
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, window_width, window_height, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferTexture, 0);

    // Creating Render Buffer
    unsigned int RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, window_width, window_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    // Check Framebuffer
    if (auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Got an error with status : " << status << ", check on framebuffer FBO " << std::endl;

    // Create additional Frame Buffer to copy resulting FrameBuffer from the previous made multisampling framebuffer
    unsigned int FBO2;
    glGenFramebuffers(1, &FBO2);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO2);

    // Create Texture for our rectangle that will display the output of our framebuffer FBO2
    unsigned int rect_texture;
    glGenTextures(1, &rect_texture);
    glBindTexture(GL_TEXTURE_2D, rect_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window_width, window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rect_texture, 0);

    // Check Framebuffer 2
    if (auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Got an error with status : " << status << ", check on framebuffer FBO2 " << std::endl;

    // Run main loop until we terminate the window
    while (!glfwWindowShouldClose(window)) {

        // Get FPS metrics
        curr = glfwGetTime();
        diff = curr - prev;
        ct++;

        // Wait until a few milliseconds to get some frames done in order to estimate the FPS metrics
        if (diff >= 1.0 / 30.0)
        {
            std::string fps = std::to_string((1.0 / diff) * ct);
            std::string ms = std::to_string((diff / ct) * 1000);
            std::string window_title = "ShadeGL at " + fps + " FPS " + " in " + ms + "ms";
            glfwSetWindowTitle(window, window_title.c_str());

            // Reset counter and update previous time to current
            prev = curr;
            ct = 0;

            // Handle case where VSYNC is disabled
            if (!VSYNC) {
                // Check for user inputs
                input();
                if (!light_sel)
                    camera.inputs(window);
                else {
                    lightPos.x = gpos.x;
                    lightPos.y = gpos.y;
                    lightPos.z = gpos.z;
                }
            }
        }

        // Binding FrameBuffer
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        // Clear Window with clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable DEPTH_TEST
        glEnable(GL_DEPTH_TEST);

        // Handle VSYNC CASE
        if (VSYNC) {
            // Check for user inputs for the window as well as the camera
            input();
            if (!light_sel)
                camera.inputs(window);
            else {
                lightPos.x = gpos.x;
                lightPos.y = gpos.y;
                lightPos.z = gpos.z;
            }
        }

        // Scale Factor
        glUniform1f(uniID, 5.f);

        // Update Camera Matrix
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // Draw | Update | Render
        glClearError();
        floor.Draw(shader, camera);
        lightModel = transform.model() * lightModel;
        glUniformMatrix4fv(glGetUniformLocation(lightshader.programID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(glGetUniformLocation(lightshader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniformMatrix4fv(glGetUniformLocation(shader.programID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
        glUniform4f(glGetUniformLocation(shader.programID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shader.programID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform1i(glGetUniformLocation(shader.programID, "gsel"), gsel);
        light.Draw(lightshader, camera);
        glCheckError();


        if (ENABLE_SKYBOX) {
            // For this skybox we want to use GL_LEQUAL for the depth function
            glDepthFunc(GL_LEQUAL);
            // Use of skybox shader
            skyboxshader.use();
            // Handle Skybox projection on cubemap
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
            view = glm::mat4(glm::mat3(glm::lookAt(camera.position, camera.position + camera.orientation, camera.up)));
            projection = glm::perspective(glm::radians(45.0f), (float) window_width / window_height, 0.1f, 100.0f);
            glUniformMatrix4fv(glGetUniformLocation(skyboxshader.programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(skyboxshader.programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glBindVertexArray(skyboxVAO);
        }

        glActiveTexture(GL_TEXTURE0);
        if (ENABLE_SKYBOX) {
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            // Draw 2 triangles for each of the 6 faces = Total 36 Triangles
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        // Switch back to the normal depth function
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

        // Set FBO as READ framebuffer as we want to get the multisampled frame and copy it into FBO2
        glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
        // Setting FBO2 as Draw framebuffer
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO2);
        // Copying FBO multisampled output to Final FBO2, because FBO2 will be displayed on the screen and not FBO
        glBlitFramebuffer(0,0, window_width, window_height, 0, 0, window_width, window_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

        // Bind the default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Draw the framebuffer rectangle
        framebuffershader.use();
        glBindVertexArray(rectVAO);
        // Disable Depth because the rectangleTexture doesn't need depth its only job to to display the output of FBO2
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, rect_texture);
        glDrawArrays(GL_TRIANGLES, 0, 6); // 6 vertices shared between 2 triangles

        // Swap buffers
        glfwSwapBuffers(window);
    }
    // Call Delete()
    shader.Delete();
    if (ENABLE_SKYBOX)
        skyboxshader.Delete();
    framebuffershader.Delete();
    lightshader.Delete();
    glDeleteFramebuffers(1, &FBO);
    glDeleteFramebuffers(1, &FBO2);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

