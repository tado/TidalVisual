/*
{
  "CATEGORIES" : [
    "Automatically Converted"
  ],
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

	vec2 position = ( gl_FragCoord.xy / RENDERSIZE.xy ) / 4.0;

	//float r, g;
	float mix1, mix2;
	
	vec4 t = gl_FragCoord;
	
	for (int i = 0; i < 8; i++){
		t.x += sin(t.y/40.0 + TIME) * 10.0;
		t.y += sin(t.x/60.0 - TIME) * 10.0;
	}
	
	if (1.5 > mod(t.x, 20.0))
		mix1 = 1.;
	else
		mix1 = 0.0;
	
	if (1.5 > mod(t.y, 20.0))
		mix2 = 1.;
	else
		mix2 = 0.0;
		
    float a = mix1 + mix2;

	gl_FragColor = vec4(a*r, a*g, a*b, 1.0);

}