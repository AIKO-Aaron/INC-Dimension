#version 330 core

uniform sampler2D tex;

struct material {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct lightSource { // normal point light
    vec3 position;
    vec3 attenuation;
    float ambient, diffuse, specular;
};

struct directionalSource { // normal point light
    vec3 direction;
    float ambient, diffuse, specular;
};

uniform material mat;
uniform lightSource light;
uniform directionalSource skyLight;

in vec3 viewpos;
in vec2 uv_coords;
in vec3 vert_coords;
in vec3 normal;
out vec4 color;

vec3 directionalLight(directionalSource ls, material m, vec3 normal, vec3 view_dir) {
    vec3 light_ray = normalize(-ls.direction);
    vec3 refl = reflect(normalize(ls.direction), normal);
    
    vec3 col = vec3(texture(m.diffuse, uv_coords));
    vec3 ambient = vec3(ls.ambient) * col;
    vec3 diffuse = vec3(ls.diffuse) * col * max(dot(normal, light_ray), 0.0);
    vec3 specular = vec3(ls.specular) * pow(max(dot(view_dir, refl), 0.0), m.shininess) * vec3(texture(m.specular, uv_coords));

    return (ambient + diffuse + specular);
}

vec3 pointLight(lightSource ls, material m, vec3 normal, vec3 vert_coords, vec3 view_dir) {
    vec3 light_ray = -normalize(ls.position - vert_coords);
    vec3 refl = reflect(-light_ray, normal);
    
    vec3 col = vec3(texture(m.diffuse, uv_coords));
    vec3 ambient = ls.ambient * col;
    vec3 diffuse = ls.diffuse * col * max(dot(normal, light_ray), 0.0);
    vec3 specular = ls.specular * pow(max(dot(view_dir, refl), 0.0), m.shininess) * vec3(texture(m.specular, uv_coords));
    
    float d = length(ls.position - vert_coords); // Distance to light
    float attenuation = 1.0f / dot(ls.attenuation, vec3(1, d, d * d));
    
    return (ambient + diffuse + specular) * attenuation;
}

void main() {
    vec3 norm = normalize(normal);
    vec3 view = normalize(viewpos - vert_coords);
    
    vec3 result = vec3(0, 0, 0); //texture(tex, uv_coords).rgb;
    result += directionalLight(skyLight, mat, norm, view);
    // for each light:
    result += pointLight(light, mat, norm, vert_coords, view);
    
    color = vec4(result, 1.0);
}
