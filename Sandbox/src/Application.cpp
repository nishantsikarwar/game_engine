#include "Engine.h"
#include "common.h"

struct ShaderSourceProgram 
{
    std::string VertexSource;
    std::string FragmentSouce;
};

static ShaderSourceProgram ParseShader(const std::string& filepath) 
{
    std::ifstream stream(filepath);

enum class ShaderType 
{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)) 
    {
        /* code */
        if(line.find("#shader") != std::string::npos) 
        {
            if(line.find("vertex") != std::string::npos) 
            {
                 type = ShaderType::VERTEX;     
            } else if(line.find("fragment") != std::string::npos )
            {
                type = ShaderType::FRAGMENT;   
            }
        } else 
        {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};  
}

static unsigned int CompileShaders( unsigned int type, const std::string& source) 
{

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); /* Use to return the pointer 
            to beginning of the string as  (&source[0])*/
            glShaderSource(id, 1, &src, nullptr);
            glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if(result == GL_FALSE) 
        {

            int length; 
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length*sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);

            std::cout << "Failed To Compile Shader!" 
            << (type == GL_VERTEX_SHADER ? "Vertex":"Fragment") 
            << endl;
            std::cout << message << endl;
            glDeleteShader(id);
            return 0;
        }
            return id;
}


static unsigned int CreateShader(const std::string& vertexShader, const std::string fragmentShader) 
{
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
        glewExperimental=GL_TRUE; //Needed for core profile
      if(glewInit()!= GLEW_OK)
        printf("Error!\n");

        printf("%s\n",glGetString(GL_VERSION));

/* Positions for Triangle Vertices */
         float positions[] = 
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,

         0.5f,  0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f
    };


    /* Creating opengl Buffer For Drawing the triangle
    Everything generated needs identifiers in Opengl  */

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(float)*2,    // stride
			0                   // array buffer offset
        );


	// Create and compile our GLSL program from the shaders
ShaderSourceProgram source = ParseShader("res/shaders/Basic.shader");
unsigned int shader = CreateShader(source.VertexSource, source.FragmentSouce);
glBindAttribLocation(shader,0,"position");

// Use our shader
glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draws the Triangle With the currently binded Buffer...*/
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}