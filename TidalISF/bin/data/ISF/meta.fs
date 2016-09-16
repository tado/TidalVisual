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

float speed = 0.1;

float ball(vec2 p, float fx, float fy, float ax, float ay)
{
	vec2 r = vec2(p.x + sin(TIME*speed / 2.0 * fx) * ax * 4.0, p.y + cos(TIME*speed/ 2.0 * fy) * ay * 4.0);	
	return .027 / length(r / sin(fy * TIME * 0.1));
}

void main(void)
{
	vec2 p = ( gl_FragCoord.xy / RENDERSIZE.xy ) * 1.0- 0.5;
	p.x *= RENDERSIZE.x / RENDERSIZE.y;
	
	float col = 0.0;
	col += ball(p, 31.0, 22.0, 0.03, 0.09);
	col += ball(p, 22.5, 22.5, 0.04, 0.04);
	col += ball(p, 12.0, 23.0, 0.05, 0.03);
	col += ball(p, 32.5, 33.5, 0.06, 0.04);
	col += ball(p, 23.0, 24.0, 0.07, 0.03);	
	col += ball(p, 21.5, 22.5, 0.08, 0.02);
	col += ball(p, 33.1, 21.5, 0.09, 0.07);
	col += ball(p, 23.5, 32.5, 0.09, 0.06);
	col += ball(p, 14.1, 13.5, 0.09, 0.05);
	
	col += ball(p, 22.0, 27.0, 0.03, 0.05);
	col += ball(p, 12.5, 17.5, 0.04, 0.06);
	col += ball(p, 23.0, 17.0, 0.05, 0.02);
	col += ball(p, 19.5, 23.5, 0.06, 0.09);
	col += ball(p, 33.0, 14.0, 0.07, 0.01);	
	col += ball(p, 11.5, 12.5, 0.08, 0.04);
	col += ball(p, 23.1, 11.5, 0.09, 0.07);
	col += ball(p, 13.5, 22.5, 0.09, 0.03);
	col += ball(p, 14.1, 23.5, 0.09, 0.08);
	
	col *= 0.3;
	
	gl_FragColor = vec4(col, col, col, 1.0) * vec4(r, g, b, 1.0);
}