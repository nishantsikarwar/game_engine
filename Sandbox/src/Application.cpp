#include "Engine.h"
#include "common.h"

static unsigned int CompileShaders( unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); /* Use to return the pointer 
            to beginning of the string as  (&source[0])*/
            glShaderSource(id, 1, &src, nullptr);
            glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if(result == GL_FALSE) {

            int length; 
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length*sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);

            std::cout << "Failed To Compile Shader!" 
            << (type == GL_VERTEX_SHADER ? "Vertex":"Frament") 
            << endl;
            std::cout << message << endl;
            glDeleteShader(id);
            return 0;
        }
            return id;
}


static unsigned int CreateShader(const std::string& vertexShader, const std::string fragmentShader) {
    /* Take actual Shader Source Code as String to Compile them... */
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShaders(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShaders(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main (void)
{
    GLFWwindow* window;

    /* Initialize the GLFW library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Called glewInit() after a vaild Context*/
      if(glewInit()!= GLEW_OK)
        printf("Error!\n");

        printf("%s\n",glGetString(GL_VERSION));

/* Positions for Triangle Vertices */
         float positions[6] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };


    /* Creating opengl Buffer For Drawing the triangle
    Everything generated needs identifiers in Opengl  */

    unsigned int buffer;
        glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    std::string vertexShader = 
    "#version 130"
    "\n"
    "layout(loaction =0) in vec4 position;\n"
    "\n"
    "void main()\n"
    "{\n"
    "gl_Position = position;\n"
    "\n}";

std::string fragmentShader = 
    "#version 130"
    "\n"
    "layout(loaction =0) out vec4 color;"
    "\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

unsigned int shader = CreateShader(vertexShader, fragmentShader);
glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draws the Triangle With the currently binded Buffer...*/
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}