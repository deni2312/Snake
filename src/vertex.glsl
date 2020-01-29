#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
  
 uniform mat4 transform;

void main()
{
    gl_Position = transform*vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    
}
