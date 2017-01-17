/*
{
"INPUTS" : [
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
		}
  ]
}
*/

void main( void ) {

	float len = vv_FragNormCoord.x*20.+sin(vv_FragNormCoord.y*20.*sin(TIME)+sin(TIME*0.8)*3.5);
	gl_FragColor = vec4( (vec3(0.5+0.5*sin(TIME*10.-vec3(20.*len/(1.+pow(len,0.8)))+1.0+fract(6.28*sin(len/(1.+pow(vec3(len),vec3(.37,.66,.45)))))))), 1.0 ) * vec4(r, g, b, 1.0);

}