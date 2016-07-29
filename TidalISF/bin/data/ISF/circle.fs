/*{
	"DESCRIPTION": "Simple Circle",
	"CREDIT": "tado",
	"CATEGORIES": [
		"shape"
	],
	"INPUTS": [
		{
			"NAME": "vel",
			"TYPE": "float",
			"DEFAULT": 0.5,
			"MIN": 0.0,
			"MAX": 1.0
		}
	]	
}*/

float circle(in vec2 _st, in float _radius){
    vec2 dist = vec2(_st.x-(RENDERSIZE.x/RENDERSIZE.y/2.0), _st.y-0.5);
	return 1.-smoothstep(_radius-(_radius*0.03),
                         _radius+(_radius*0.03),
                         dot(dist,dist)*4.0);
}

void main(){
	vec2 st = gl_FragCoord.xy/RENDERSIZE.y;
	vec3 color = vec3(circle(st, vel));
	gl_FragColor = vec4( color, 1.0 );
}