#version 400
in vec2 UV;
out vec4 fragment_color;

uniform sampler2D font_bitmap;

void main() {
    vec3 color = vec3(texture(font_bitmap, UV).a);
	fragment_color = vec4(color, 1.f);
}