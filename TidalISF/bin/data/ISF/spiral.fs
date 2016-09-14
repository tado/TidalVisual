/*
{
  "IMPORTED" : [

  ],
  "CATEGORIES" : [

  ],
  "INPUTS" : [
	{
 		"NAME": "distort",
		"LABEL": "distort",
		"TYPE": "float",
		"MIN": 0.0,
		"MAX": 50.0,
		"DEFAULT": 25.0
	 },
	 {
		"NAME": "vel",
		"TYPE": "float",
		"DEFAULT": 1.0
	},
	{
		"NAME": "gain",
		"TYPE": "float",
		"DEFAULT": 1.0
	}	 
  ]
}
*/
float rings(vec2 p, float ring)
{
  return cos(length(p)*ring*1.5);
}

void main() {
  float ttime = TIME * vel;
  float final;
  vec2 pos = (gl_FragCoord.xy*2.0 -RENDERSIZE) / RENDERSIZE.y;
  float px1 = cos(ttime*1.50+0.55)*0.4+pos.x;
  float py1 = sin(ttime*1.10+0.55)*0.4+pos.y;
  float px2 = cos(ttime*0.95+0.65)*0.3+pos.x;
  float py2 = sin(ttime*0.55+0.65)*0.3+pos.y;
  float px3 = cos(ttime*0.75+0.85)*0.5+pos.x;
  float py3 = sin(ttime*0.35+0.85)*0.5+pos.y;
  float colorB = rings(vec2(px1,py1),distort*vel)+1.0*rings(vec2(px2,py2),distort*0.7)+2.0*rings(vec2(px3,py3),distort*vel);
  float colorR = rings(vec2(px1,py1),distort*vel)-2.0*rings(vec2(px2,py2),distort*0.7)+1.0*rings(vec2(px3,py3),distort*vel);
  float colorG = rings(vec2(px1,py1),distort*vel)-3.0*rings(vec2(px2,py2),distort*0.7)-2.0*rings(vec2(px3,py3),distort*vel);
  final = (colorB + colorG + colorR) * 0.2 * gain;
  gl_FragColor = vec4(final, final, final, final);
}
