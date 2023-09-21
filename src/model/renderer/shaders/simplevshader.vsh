attribute highp vec4 a_position;
uniform highp mat4 u_modelMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_projectionMatrix;
uniform highp float u_pointSize;

void main(void)
{
    mat4 mv_Matrix = u_viewMatrix * u_modelMatrix;
    gl_Position = u_projectionMatrix * mv_Matrix * a_position;
    gl_PointSize = u_pointSize;
}
