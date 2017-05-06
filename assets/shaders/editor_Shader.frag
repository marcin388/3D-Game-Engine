#version 330 core

// Ouput data
out vec4 colour;

// Values that stay constant for the whole mesh.
uniform vec4 pickColour;

void main()
{
    colour = pickColour;
}