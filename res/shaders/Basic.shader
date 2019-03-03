#shader vertex
#version 130
in vec4 position;
    
void main()
{
    gl_Position = position;
};

#shader fragment    
#version 130
    
out vec4 color;
uniform vec4 u_Color;

void main()
{
    color = u_Color;
};