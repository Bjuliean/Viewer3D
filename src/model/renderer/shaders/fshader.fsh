uniform sampler2D u_texture;
uniform highp vec4 u_lightpos;
uniform highp float u_lightpower;
varying highp vec4 v_position;
varying highp vec2 v_textcoord;
varying highp vec3 v_normal;

void main(void)
{
    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePos = vec4(0.0, 0.0, -5.0, 1.0);
    vec4 diffMatColor = texture2D(u_texture, v_textcoord);
    vec3 eyeVec = normalize(v_position.xyz - eyePos.xyz);
    vec3 lightVec = normalize(v_position.xyz - u_lightpos.xyz);
    vec3 reflectLight = normalize(reflect(lightVec, v_normal));
    float len = length(v_position.xyz - eyePos.xyz);
    float specularFactor = 60.0;
    float ambientFactor = 0.5;

    vec4 diffColor = diffMatColor * u_lightpower * max(0.0, dot(v_normal, -lightVec)) / (1.0 + 0.25 * pow(len, 2.0));
    resultColor += diffColor;
    vec4 ambientColor = ambientFactor * diffMatColor;
    resultColor += ambientColor;
    vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0) * u_lightpower * pow(max(0.0, dot(reflectLight, -eyeVec)), specularFactor) / (1.0 + 0.25 * pow(len, 2.0)) ;
    resultColor += specularColor;

    gl_FragColor = resultColor;
}
