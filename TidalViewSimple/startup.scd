SuperDirt.start;

// foward OSC
var addr = NetAddr.new("127.0.0.1", 3333);
OSCFunc({ |msg, time, tidalAddr|
	var latency = time - Main.elapsedTime;
	msg = msg ++ ["time", time, "latency", latency];
	msg.postln;
	addr.sendBundle(latency, msg)
}, '/play2', ~dirt.senderAddr, recvPort: ~dirt.port).fix;