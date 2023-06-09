#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 10) out;

uniform int Type;

uniform vec2 Scale;
uniform vec2 Center;
uniform ivec2 ScreenSize;
uniform vec2 Julia_Set_C;

void main(void)
{
	vec2 aspect_ratio = vec2(1.0, -1.0);
	
	if(ScreenSize.x > ScreenSize.y)
		aspect_ratio.x *= float(ScreenSize.x) / float(ScreenSize.y);
	else
		aspect_ratio.y *= float(ScreenSize.y) / float(ScreenSize.x);

	vec2 Z = gl_in[0].gl_Position.xy * aspect_ratio / Scale + Center;
	vec2 C = Z;

	switch(Type)
	{
		case 0:
			for(int i = 0; i < 10; i++)
			{
				vec2 V = (Z - Center) * Scale / aspect_ratio;

				gl_Position = vec4(V, 0.0, 1.0);
				EmitVertex();

				Z = vec2(Z.x * Z.x - Z.y * Z.y, 2 * Z.x * Z.y) + Julia_Set_C;
			}
			break;

		case 1:
			for(int i = 0; i < 10; i++)
			{
				vec2 V = (Z - Center) * Scale / aspect_ratio;

				gl_Position = vec4(V, 0.0, 1.0);
				EmitVertex();

				Z = vec2(Z.x * Z.x - Z.y * Z.y, 2 * Z.x * Z.y) + C;
			}
			break;

		case 2:
			for(int i = 0; i < 10; i++)
			{
				vec2 V = (Z - Center) * Scale / aspect_ratio;

				gl_Position = vec4(V, 0.0, 1.0);
				EmitVertex();

				float fx = abs(Z.x);
				float fy = abs(Z.y);

				Z = vec2(fx * fx - fy * fy, 2 * fx * fy) + C;
			}
			break;

		default:
			gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
			EmitVertex();
	}

	EndPrimitive();
}
