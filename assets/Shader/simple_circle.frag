    #version 330 core
    out vec4 FragColor;
    uniform vec2 center;
    uniform float radius;
    void main() {
        float distance = length(gl_FragCoord.xy - center);
        if (distance <= radius) {
            FragColor = vec4(1.0, 0.0, 0.0, 1.0); 
        } else {
            discard; 
        }
    }