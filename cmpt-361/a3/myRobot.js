var canvas;
var gl;
var vBuffer;
var program;
var mvMatrix;
var pMatrix;
var figure = [ ];
var baseBotVertices = [];
var baseSideVertices = [];
var baseTopVertices = [];

window.onload = function init() {
	canvas = document.getElementById("gl-canvas");
	gl = WebGLUtils.setupWebGL(canvas);
	if (!gl) {alert("WebGL isn't available");}
	gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 0.0 );

	vBuffer = gl.createBuffer();

	var eye = vec3(0.0, 0.0, 10.0);
	var at = vec3(0.0, 0.0, 0.0);
	var up = vec3(0.0, 1.0, 0.0);
	mvMatrix = lookAt(eye, at, up);

	var fovy = 75;
	var aspect = canvas.width/canvas.height;
	var near = 0.01;
	var far = 100;
	pMatrix = perspective(fovy, aspect, near, far);
	gl.enable(gl.DEPTH_TEST);

	var numNodes = 3;
	for (var i=0;i<numNodes; ++i) {
		figure[i] = createNode(null, null, null, null);
	}

	// initNodes(0);
	initBase(20);
	render();
}

function render() {
	program = initShaders( gl, "vertex-shader", "fragment-shader" );
	gl.useProgram( program );
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(baseBotVertices), gl.STATIC_DRAW);

	var vPosition = gl.getAttribLocation(program, "vPosition");
	var modelViewMatrix = gl.getUniformLocation(program, "modelViewMatrix");
	var projectionMatrix = gl.getUniformLocation(program, "projectionMatrix");
	gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0, 0);
	gl.enableVertexAttribArray(vPosition);

	gl.uniformMatrix4fv(modelViewMatrix, false, flatten(mvMatrix));
	gl.uniformMatrix4fv(projectionMatrix, false, flatten(pMatrix));

	gl.drawArrays(gl.TRIANGLE_FAN, 0, baseBotVertices.length);
    
}

function createNode(transform, render, sibling, child) {
	var node = {
		transform: transform,
		render: render,
		sibling: sibling,
		child: child
	};

	return node;
}

function initNodes(id) {
	var m = mat4();
	switch (id) {
		case 0:
			return;
	}
}

function initBase(segments) {
	var y = 0;
	theta = (Math.PI / 180) * (360 / segments);
	for (var i=0; i<segments; i++) {
		var x = Math.cos(theta*i);
		var z = Math.sin(theta*i);

		baseBotVertices.push(x, y, z,);
		baseSideVertices.push(x, y, z,);
		baseSideVertices.push(x, y+2, z);
		baseTopVertices.push(x, y+2, z);
	}
}