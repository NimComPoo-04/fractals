#include "burning_ship.h"
#include "shader.h"
#include "state.h"

static void gen_uniforms(burning_ship_t *js);
void create_burning_ship(burning_ship_t *js, GLuint vs, GLuint fs, GLuint texture)
{
	js->program = create_shader_program(2, vs, fs);
	gen_uniforms(js);
	js->theme_texture = texture;
}

void use_burning_ship_shader(burning_ship_t *js)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_1D, js->theme_texture);
	glUseProgram(js->program);
}

void update_burning_ship_Scale(burning_ship_t *js, float a, float b)
{
	js->Scale.value_f2[0] = a;
	js->Scale.value_f2[1] = b;
	set_uniform(js->program, &js->Scale);
}

void update_burning_ship_Center(burning_ship_t *js, float a, float b)
{
	js->Center.value_f2[0] = a;
	js->Center.value_f2[1] = b;
	set_uniform(js->program, &js->Center);
}

void update_burning_ship_Size(burning_ship_t *js, int a, int b)
{
	js->ScreenSize.value_i2[0] = a;
	js->ScreenSize.value_i2[1] = b;
	set_uniform(js->program, &js->ScreenSize);
}

void update_burning_ship_MaxIteration(burning_ship_t *js, int a)
{
	js->MaxIteration.value_i1 = a;
	set_uniform(js->program, &js->MaxIteration);
}

void destroy_burning_ship(burning_ship_t *js)
{
	destroy_shader(js->program);
}

static void gen_uniforms(burning_ship_t *js)
{
	js->Scale.name = "Scale";
	js->Scale.type = GL_FLOAT_VEC2;
	js->Scale.value_f2[0] = 1.0;
	js->Scale.value_f2[1] = 1.0;
	create_uniform(js->program, &js->Scale);

	js->Center.name = "Center";
	js->Center.type = GL_FLOAT_VEC2;
	js->Center.value_f2[0] = 0.0;
	js->Center.value_f2[1] = 0.0;
	create_uniform(js->program, &js->Center);

	js->ScreenSize.name = "ScreenSize";
	js->ScreenSize.type = GL_INT_VEC2;
	js->ScreenSize.value_i2[0] = gWidth;
	js->ScreenSize.value_i2[1] = gHeight;
	create_uniform(js->program, &js->ScreenSize);

	js->MaxIteration.name = "MaxIteration";
	js->MaxIteration.type = GL_INT;
	js->MaxIteration.value_i1 = 500;
	create_uniform(js->program, &js->MaxIteration);
}

void key_ui_burning_ship_update(burning_ship_t *js, GLFWwindow *win, int key, int action, int mod)
{
	if(action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch(key)
		{
			// TODO: Use mouse here instaed of keys
			case GLFW_KEY_W:
				{
					float v1 = js->Scale.value_f2[0] * 1.1;
					float v2 = js->Scale.value_f2[1] * 1.1;
					update_burning_ship_Scale(js, v1, v2);
				}
				break;

			case GLFW_KEY_S:
				{
					float v1 = js->Scale.value_f2[0] / 1.1;
					float v2 = js->Scale.value_f2[1] / 1.1;
					update_burning_ship_Scale(js, v1, v2);
				}
				break;

			// TODO: use right click
			case GLFW_KEY_V:
				{
					double xpos;
					double ypos;
					glfwGetCursorPos(win, &xpos, &ypos);

					double gx = (2.0 * xpos / gWidth) - 1;
					double gy = (2.0 * ypos / gHeight) - 1;

					float ratio[2] = {1.0, 1.0};

					if(gWidth > gHeight)
					{
						ratio[0] = 1.0 * gWidth / gHeight;
						ratio[1] = 1.0;
					}
					else
					{
						ratio[0] = 1.0;
						ratio[1] = 1.0 * gHeight / gWidth;
					}

					float x = ratio[0] * (float)gx / js->Scale.value_f2[0] + js->Center.value_f2[0];
					float y = -ratio[1] * (float)gy / js->Scale.value_f2[1] + js->Center.value_f2[1];

					update_burning_ship_Center(js, x, y);
				}
				break;
		}
	}
}
