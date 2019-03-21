var canvas;
var gl;
var vBuffer;
// var cBuffer;
// var cData = [];
var program;
var viewMatrix;
var vData = [];
var wireCube = [
	-.15, -.15, -.15,
     .15, -.15, -.15,
     .15,  .15, -.15,
    -.15,  .15, -.15,
    -.15, -.15,  .15,
     .15, -.15,  .15,
     .15,  .15,  .15,
    -.15,  .15,  .15
];
var cubeIndices = [
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
    0, 4,
    1, 5,
    2, 6,
    3, 7,
  ];
var tMatrix = mat4();
var rMatrix = mat4();
var cubeTMatrix = translate(5, 5, 0);
var cubeRotate = 0;

window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 0.0 );

	// Creating the vertex buffer	
	vBuffer = gl.createBuffer();
	// cBuffer = gl.createBuffer();	

	// Store bunny vertices data
	var vertices = get_vertices();
	var faces = get_faces();
	for (var i=0; i<faces.length; i++) {
		for (var j=0; j<3; j++) {
			vData.push(vertices[faces[i][j]-1]);
			//cData.push(vertices[faces[i][j]-1]);
		}
	}

	// Create mv matrix
	var eye = vec3(0.0, 0.0, 10.0);
	var at = vec3(0.0, 0.0, 0.0);
	var up = vec3(0.0, 1.0, 0.0);
	var mv = lookAt(eye, at, up);

	// Create perspective matrix
	var fovy = 90;
	var aspect = canvas.width/canvas.height;
	var near = 0;
	var far = 100;
	var pMatrix = perspective(fovy, aspect, near, far);
	viewMatrix = mult(pMatrix, mv);

	render();
	renderWireFrames();
};

var leftMouseDown = false;
var rightMouseDown = false;
var rotateCube = true;
var rotateCone = true;

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
		// render();
	}
	if (rightMouseDown) {
		var x = event.movementX;
		var y = event.movementY;
		var newRotXMatrix = rotate(x, vec3(0.0, 1.0, 0.0));
		var newRotYMatrix = rotate(y, vec3(1.0, 0.0, 0.0));
		var newRotMatrix = mult(newRotXMatrix, newRotYMatrix);
		rMatrix = mult(newRotMatrix, rMatrix);
		// render();
	}
});

window.addEventListener("mousewheel", function(event) {
	var z = 0.01 * event.wheelDeltaY;
	var newTMatrix = translate(0, 0, z);
	tMatrix = mult(newTMatrix, tMatrix);
	// render();
});

window.addEventListener("keydown", function(event) {
	if (event.key == "r") {
		tMatrix = mat4();
		rMatrix = mat4();
		// render();
	}
	if (event.key == "p") {
		rotateCube = !rotateCube;
	}
});

function render() {
    program = initShaders( gl, "bunny-vertex-shader", "fragment-shader" );
	gl.useProgram( program );

    // Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vData), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	// var vColor = gl.getAttribLocation( program, "vColor" );
	var mvMatrix = gl.getUniformLocation( program, "mvMatrix" );
	var transMatrix = gl.getUniformLocation( program, "transMatrix");
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );

	// Binding the color buffer
	// gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
	// gl.bufferData( gl.ARRAY_BUFFER, flatten(cData), gl.STATIC_DRAW );
	// gl.vertexAttribPointer( vColor, 3, gl.FLOAT, true, 0, 0);
	// gl.enableVertexAttribArray( vColor );

	// Associate transformation matrix and modelview matrix with uniform attributes
	var transformMatrix = mult(tMatrix, rMatrix);
	gl.uniformMatrix4fv(mvMatrix, false, flatten(viewMatrix));
	gl.uniformMatrix4fv(transMatrix, false, flatten(transformMatrix));

	// Draw the bunny
	gl.drawArrays( gl.TRIANGLES, 0, vData.length);
	requestAnimationFrame(render);
}

function renderWireFrames() {
	program = initShaders( gl, "wireframe-vertex-shader", "fragment-shader" );
	gl.useProgram( program );

    // Binding the vertex buffer
    var wBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, wBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(wireCube), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	// var vColor = gl.getAttribLocation( program, "vColor" );
	var mvMatrix = gl.getUniformLocation( program, "mvMatrix" );
	var transMatrix = gl.getUniformLocation( program, "transMatrix");
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );

	var wBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, wBuffer);
	gl.bufferData( gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeIndices), gl.STATIC_DRAW);

	// Binding the color buffer
	// gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
	// gl.bufferData( gl.ARRAY_BUFFER, flatten(cData), gl.STATIC_DRAW );
	// gl.vertexAttribPointer( vColor, 3, gl.FLOAT, true, 0, 0);
	// gl.enableVertexAttribArray( vColor );

	// Associate transformation matrix and modelview matrix with uniform attributes
	var cubeRMatrix = rotate(cubeRotate, vec3(0.0, 1.0, 0.0));
	var transformMatrix = mult(cubeRMatrix, cubeTMatrix);
	// var scaleMatrix = scalem(0.3, 0.3, 0.3);
	// transformMatrix = mult(scaleMatrix, transformMatrix);
	gl.uniformMatrix4fv(mvMatrix, false, flatten(viewMatrix));
	gl.uniformMatrix4fv(transMatrix, false, flatten(transformMatrix));

	// Draw the cube
	gl.drawElements(gl.LINES, cubeIndices.length, gl.UNSIGNED_SHORT, 0);
	if (rotateCube) {
		cubeRotate += 1;
		if (cubeRotate == 360){ cubeRotate = 0; }
	}
	requestAnimationFrame(renderWireFrames);
}