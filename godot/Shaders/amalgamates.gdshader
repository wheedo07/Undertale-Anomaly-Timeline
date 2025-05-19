shader_type canvas_item;

uniform float time = 0.0;
uniform float distortion_strength = 0.015;
uniform float glitch_frequency = 40.0;

void fragment() {
    vec2 uv = UV;

    float offset = sin(uv.y * glitch_frequency + time) * distortion_strength;
    uv.x += offset;

    uv.y += cos(uv.x * glitch_frequency * 1.2 + time * 1.5) * distortion_strength * 0.5;

    COLOR = texture(TEXTURE, uv);
}