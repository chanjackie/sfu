var canvas;
var gl;
var vBuffer;
var cBuffer;
var program;
var eye = vec3(0.0, 0.0, 10.0);
var at = vec3(0.0, 0.0, 0.0);
var up = vec3(0.0, 1.0, 0.0);
var fovy = 90;
var aspect;
var near;
var far;
var vData = [];
var cData = [];
var tMatrix = mat4();
var rMatrix = mat4();
var vertices;
var faces;
// var tMatrix = mat4(
// 	vec4(1.0, 0.0, 0.0, 0.0),
// 	vec4(0.0, 1.0, 0.0, 0.0),
// 	vec4(0.0, 0.0, 1.0, 0.0),
// 	vec4(0.0, 0.0, 0.0, 1.0));

window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 0.0 );
	// Creating the vertex buffer
	
	vBuffer = gl.createBuffer();
	cBuffer = gl.createBuffer();

	aspect = canvas.width/canvas.height;
	near = 0;
	far = 100;
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
	gl.useProgram( program );

	vertices = get_vertices();
	faces = get_faces();
	for (var i=0; i<faces.length; i++) {
		for (var j=0; j<3; j++) {
			vData.push(vertices[faces[i][j]-1]);
			cData.push(vertices[faces[i][j]-1]);
		}
	}

	render();
};

var leftMouseDown = false;
var rightMouseDown = false;

window.addEventListener("mousedown", function(event) {
	if (event.which == 1) {
		leftMouseDown = true;
	}
	if (event.which == 3) {
		rightMouseDown = true;
	}
});

window.addEventListener("mouseup", function(event) {
	if (event.which == 1) {
		leftMouseDown = false;
	}
	if (event.which == 3) {
		rightMouseDown = false;
	}
});

window.addEventListener("mousemove", function(event) {
	if (leftMouseDown) {
		var x = 0.02 * event.movementX;
		var y = -0.02 * event.movementY;
		var newTMatrix = translate(x, y, 0);
		tMatrix = mult(newTMatrix, tMatrix);
		render();
	}
	if (rightMouseDown) {
		var x = event.movementX;
		var y = event.movementY;
		var newRotXMatrix = rotate(x, vec3(0.0, 1.0, 0.0));
		var newRotYMatrix = rotate(y, vec3(1.0, 0.0, 0.0));
		var newRotMatrix = mult(newRotXMatrix, newRotYMatrix);
		rMatrix = mult(newRotMatrix, rMatrix);
		render();
	}
});

window.addEventListener("mousewheel", function(event) {
	var z = 0.01 * event.wheelDeltaY;
	var newTMatrix = translate(0, 0, z);
	tMatrix = mult(newTMatrix, tMatrix);
	render();
});

window.addEventListener("keydown", function(event) {
	if (event.key == "r") {
		tMatrix = mat4();
		rMatrix = mat4();
		render();
	}
});

function render() {
	var mv = lookAt(eye, at, up);
	var pMatrix = perspective(fovy, aspect, near, far);

	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    // Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vData), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	var vColor = gl.getAttribLocation( program, "vColor" );
	var mvMatrix = gl.getUniformLocation( program, "mvMatrix" );
	var projMatrix = gl.getUniformLocation( program, "projMatrix");
	var transMatrix = gl.getUniformLocation( program, "transMatrix");
	var rotMatrix = gl.getUniformLocation( program, "rotMatrix");
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );


	// Binding the color buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(cData), gl.STATIC_DRAW );
	gl.vertexAttribPointer( vColor, 3, gl.FLOAT, true, 0, 0);
	gl.enableVertexAttribArray( vColor );

	gl.uniformMatrix4fv(mvMatrix, false, flatten(mv));
	gl.uniformMatrix4fv(projMatrix, false, flatten(pMatrix));
	gl.uniformMatrix4fv(transMatrix, false, flatten(tMatrix));
	gl.uniformMatrix4fv(rotMatrix, false, flatten(rMatrix));

	// Draw the block
	gl.drawArrays( gl.TRIANGLES, 0, vData.length);
}