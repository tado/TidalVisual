/*{
	"INPUTS": [
		{
			"NAME": "gain",
			"TYPE": "float",
			"DEFAULT": 1.0
		}
	]
}*/

void main() {
	gl_FragColor = vec4(0.0, 1.0 * gain, 0.0, 1.0);
}