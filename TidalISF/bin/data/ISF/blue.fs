/*{
	"CREDIT": "by tado",
	"CATEGORIES": [
		"test"
	],
	"INPUTS": [
		{
			"NAME": "vel",
			"TYPE": "float",
			"DEFAULT": 0.5
		},
		{
			"NAME": "gain",
			"TYPE": "float",
			"DEFAULT": 1.0
		}
	]
}*/



void main() {
	gl_FragColor = vec4(0.0, 0.0, 1.0 * gain, 1.0);
}