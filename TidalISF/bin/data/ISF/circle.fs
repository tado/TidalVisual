/*{
	"DESCRIPTION": "Simple Circle",
	"CREDIT": "tado",
	"CATEGORIES": [
		"shape"
	],
	"INPUTS": [
		{
			"NAME": "radius",
			"TYPE": "float",
			"DEFAULT": 0.5,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "x",
			"TYPE": "float",
			"DEFAULT": 0.5,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "y",
			"TYPE": "float",
			"DEFAULT": 0.5,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "smooth",
			"TYPE": "float",
			"DEFAULT": 0.2,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "r",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "g",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "b",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "gain",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 1.0
		}
	]
	}*/

  float circle(in vec2 _st, in float _radius){
    vec2 dist = vec2(_st.x-(RENDERSIZE.x/RENDERSIZE.y/2.0), _st.y-0.5);
    return 1.-smoothstep(_radius-(_radius * smooth), _radius+(_radius * smooth), dot(dist,dist)*4.0);
  }

void main(){
	vec2 st = gl_FragCoord.xy/RENDERSIZE.y;
	st.x = st.x - (x * 2.0 - 1.0);
	st.y = st.y - (y * 2.0 - 1.0);
	vec3 color = vec3(circle(st, radius));
	gl_FragColor = vec4(vec3(color.r * r, color.g*g, color.b*b) * gain, 1.0);
}
