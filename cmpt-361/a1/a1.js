// Global variables
var canvas;
var gl;
var blockPosition;
 
var program;
var height = 0.0;
var vBuffer;

// Getting the keyboard input
window.addEventListener("keydown", getKey, false);
var pressed = 0;
var goingLeft = 0;
var goingRight = 0;
var rotating = 0;
function getKey(key) {
	if (key.key == "ArrowDown") {
		pressed = 1;
	}
	/*if (key.key == "ArrowLeft") {
		goingLeft = 1;
		render();
	}
	if (key.key == "ArrowRight") {
		goingRight = 1;
		render();
	}
	if (key.key == "ArrowUp") {
		rotating = 1;
		render();
	}*/
}

window.addEventListener("keyup", getKeyUp, false);
function getKeyUp(key) {
	if (key.key == "ArrowDown")
		pressed = 0;
	/*if (key.key == "ArrowLeft")
		goingLeft = 0;
	if (key.key == "ArrowRight")
		goingRight = 0;
	if (key.key == "ArrowUp")
		rotating = 0;*/
}

// Six Vertices
var vertices = [
	vec2(  -0.995, 0.9975),
	vec2(  -0.805, 0.9975),
	vec2(  -0.995, 0.9025),
	vec2(  -0.805, 0.9975),
	vec2(  -0.995, 0.9025),
	vec2(  -0.805, 0.9025)
];

var positions = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

// Line vectors for grid
var horizontal = [
	vec2(-1.00, 0.9975),
	vec2(1.00, 0.9975),
	vec2(-1.00, 0.90),
	vec2(1.00, 0.90),
	vec2(-1.00, 0.80),
	vec2(1.00, 0.80),
	vec2(-1.00, 0.70),
	vec2(1.00, 0.70),
	vec2(-1.00, 0.60),
	vec2(1.00, 0.60),
	vec2(-1.00, 0.50),
	vec2(1.00, 0.50),
	vec2(-1.00, 0.40),
	vec2(1.00, 0.40),
	vec2(-1.00, 0.30),
	vec2(1.00, 0.30),
	vec2(-1.00, 0.20),
	vec2(1.00, 0.20),
	vec2(-1.00, 0.10),
	vec2(1.00, 0.10),
	vec2(-1.00, 0.00),
	vec2(1.00, 0.00),
	vec2(-1.00, -0.10),
	vec2(1.00, -0.10),
	vec2(-1.00, -0.20),
	vec2(1.00, -0.20),
	vec2(-1.00, -0.30),
	vec2(1.00, -0.30),
	vec2(-1.00, -0.40),
	vec2(1.00, -0.40),
	vec2(-1.00, -0.50),
	vec2(1.00, -0.50),
	vec2(-1.00, -0.60),
	vec2(1.00, -0.60),
	vec2(-1.00, -0.70),
	vec2(1.00, -0.70),
	vec2(-1.00, -0.80),
	vec2(1.00, -0.80),
	vec2(-1.00, -0.90),
	vec2(1.00, -0.90),
	vec2(-1.00, -0.995),
	vec2(1.00, -0.995)
];
var vertical = [
	vec2(-0.9975, 0.995),
	vec2(-0.9975, -0.995),
	vec2(-0.80, 0.995),
	vec2(-0.80, -0.995),
	vec2(-0.60, 0.995),
	vec2(-0.60, -0.995),
	vec2(-0.40, 0.995),
	vec2(-0.40, -0.995),
	vec2(-0.20, 0.995),
	vec2(-0.20, -0.995),
	vec2(0.00, 0.995),
	vec2(0.00, -0.995),
	vec2(0.20, 0.995),
	vec2(0.20, -0.995),
	vec2(0.40, 0.995),
	vec2(0.40, -0.995),
	vec2(0.60, 0.995),
	vec2(0.60, -0.995),
	vec2(0.80, 0.995),
	vec2(0.80, -0.995),	
	vec2(0.9975, 0.995),
	vec2(0.9975, -0.995),
];
var verticalOffset = 0.0;
var horizontalOffset = 0.0;

window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 0.5 );
	// Creating the vertex buffer
	
	vBuffer = gl.createBuffer();

	//
    //  Load shaders and initialize attribute buffers
    //
    
	
    randomizeBlockPosition();
	render();
};

function drawGrid() {
	// Associate out shader variables with our data buffer
	program = initShaders( gl, "vertex-shader", "grid-fragment-shader" );
	gl.useProgram( program );
	var vBuffer = gl.createBuffer();
	// Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(horizontal), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );       
	gl.drawArrays(gl.LINES, 0, horizontal.length)

	gl.bufferData(gl.ARRAY_BUFFER, flatten(vertical), gl.STATIC_DRAW);
	vPosition = gl.getAttribLocation(program, "vPosition");
	gl.enableVertexAttribArray(vPosition);
	gl.drawArrays(gl.LINES, 0, vertical.length)
}

function randomizeBlockPosition() {
	vertices = [
		vec2(  -0.995, 0.9975),
		vec2(  -0.805, 0.9975),
		vec2(  -0.995, 0.9025),
		vec2(  -0.805, 0.9975),
		vec2(  -0.995, 0.9025),
		vec2(  -0.805, 0.9025)
	];
	blockPosition = Math.floor(Math.random()*10);
	for (var i=0;i<vertices.length;i++) {
		vertices[i][0] += blockPosition*0.2;
	}
}

function render() {
    // Changing the height value for moving the square
    drawGrid();
    var waitTime = 700;
	if (height > -1.8) {
		height = height - 0.10
		if (pressed == 1)
			waitTime = 200;
	} else {
		height = 0.0;
		randomizeBlockPosition();
	}
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
	gl.useProgram( program );
    // Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );       	
    
	// For debugging 
	console.log(height);
	console.log(blockPosition)
	console.log(vertices)
	document.getElementById("debug").innerHTML = height;
	
	// Sending the height to the vertex shader
	var heightLoc = gl.getUniformLocation(program, "height");
	gl.uniform1f(heightLoc, height);
	
	// Clearing the buffer and drawing the square
	//gl.clear( gl.COLOR_BUFFER_BIT ); 
	gl.drawArrays( gl.TRIANGLES, 0, 6 );
	
	setTimeout(function () {
		window.requestAnimFrame(render);
	}, waitTime);
}
