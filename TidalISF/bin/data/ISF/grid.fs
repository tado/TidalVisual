/*
{
  "CATEGORIES" : [
    "Automatically Converted"
  ],
  "INPUTS" : [
    {
          }
  ]
}
*/

void main( void ) {

	vec2 position = ( gl_FragCoord.xy / RENDERSIZE.xy ) / 4.0;

	float r, g;
	
	vec4 t = gl_FragCoord;
	
	for (int i = 0; i < 8; i++){
		t.x += sin(t.y/40.0 + TIME) * 10.0;
		t.y += sin(t.x/60.0 - TIME) * 10.0;
	}
	
	if (1.5 > mod(t.x, 10.0))
		r = 1.;
	else
		r = 0.0;
	
	if (1.5 > mod(t.y, 10.0))
		g = 1.;
	else
		g = 0.0;
		
    float a = r+g;

	gl_FragColor = vec4(a, a, a, 1.0);

}