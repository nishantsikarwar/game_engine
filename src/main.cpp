#include "common.h"
// using namespace std;
// #define For(i,x,y) for (int i = x; i <= y; ++i)
// #define speed ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
// #define endl 
// #define input 3
// #define vlong long long
// #define ONLINE_JUDGE freopen("input", "r",stdin); freopen("output","w",stdout);
// #define M 10000000007
// #define abs(x) x > 0 ? x : -x

int main (void)
{
    GLFWwindow* window;

    /* Initialize the library */
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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}