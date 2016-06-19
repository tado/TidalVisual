/*{
    "CREDIT": "by tado",
    "CATEGORIES" : [
        
    ],
    "INPUTS" : [
         {
            "NAME":"level",
            "TYPE": "float",
           "DEFAULT": 0.0,
            "MIN": -1.0,
            "MAX": 1.0
        }
  ]
}
*/

float wave(float x, float amount) {
  return (sin(x * amount) + 1.) * .5;
}

void main() {
	float color;
	for(int i = 0; i < 20; i++){
  		vec2 pos = (gl_FragCoord.xy*2.0 -RENDERSIZE) / RENDERSIZE.y;
  		float c = wave(gl_FragCoord.x / float(i ) * 1.7, 1.) - 0.5;  
  		color += c;		
	}
	gl_FragColor = vec4(color, color, color, 1.0);
}