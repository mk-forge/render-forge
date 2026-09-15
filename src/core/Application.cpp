#include "Application.h"

void Application::initialize() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: Couldn't start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(800, 600, "RenderForge", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    GLFWimage icon{};
    icon.pixels = stbi_load("assets/icon.png", &icon.width, &icon.height, nullptr, 4);

    if (icon.pixels)
        glfwSetWindowIcon(window, 1, &icon);
    else
        fprintf(stderr, "ERROR: Couldn't load icon.png\n");

    if (icon.pixels) stbi_image_free(icon.pixels);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: Couldn't start GLEW\n");
        exit(EXIT_FAILURE);
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    glfwSetErrorCallback(Callback::error_callback);
    glfwSetKeyCallback(window, Callback::key_callback);

    scene = std::make_unique<Scene>();
    scene->initialize();
}

void Application::createShaders() {
    scene->createShaders();
}

void Application::run() {
    scene->run(window);
}

[[noreturn]] void Application::destroy() {
    scene->destroy();
    scene.reset();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}