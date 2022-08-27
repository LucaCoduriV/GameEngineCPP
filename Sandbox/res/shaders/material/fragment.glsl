#version 330 core
struct Material {
    sampler2D diffuse[8];
    sampler2D specular[8];
    sampler2D normal[8];
    sampler2D height[8];

    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};



out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;

uniform vec3 u_camPos;
uniform SpotLight u_spotLight;
uniform Material u_material;
uniform DirLight u_dirLight;
uniform PointLight u_pointLights[PP_NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(u_camPos - FragPos);

    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    vec3 result = vec3(0.0);

    #if (PP_NR_DIR_LIGHTS > 0)
    CalcDirLight(u_dirLight, norm, viewDir);
    #endif
    // phase 2: point lights
    #if (PP_NR_POINT_LIGHTS > 0)
    for (int i = 0; i < PP_NR_POINT_LIGHTS; i++){
        result += CalcPointLight(u_pointLights[i], norm, FragPos, viewDir);
    }
        #endif

        #if (PP_NR_SPOT_LIGHTS > 0)
    result += CalcSpotLight(u_spotLight, norm, FragPos, viewDir);
    #endif

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // éclairage diffus
    float diff = max(dot(normal, lightDir), 0.0);
    // éclairage spéculaire
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    // assemblage du résultat
    vec3 ambient  = light.ambient  * vec3(texture(u_material.diffuse[1], TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_material.diffuse[1],
    TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular[1], TexCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // éclairage diffus
    float diff = max(dot(normal, lightDir), 0.0);
    // éclairage spéculaire
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    // atténuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));
    // assemblage du résultat
    vec3 ambient  = light.ambient  * vec3(texture(u_material.diffuse[1], TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_material.diffuse[1], TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular[1], TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(u_material.diffuse[1], TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.diffuse[1], TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular[1], TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}